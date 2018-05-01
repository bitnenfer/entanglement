#include "canvas.h"
#include "opengl.h"
#include "glutils.h"
#include "alloc.h"
#include <assert.h>
#include <string.h>

static const char* kCanvasVS = ""
#if defined(LD_PLATFORM_WINDOWS)
"#version 330\n"
#elif defined(LD_PLATFORM_WEB)
"precision mediump float;\n"
#endif
"uniform mat4 uProjectionMatrix;\n"
"attribute vec2 inPosition;\n"
"attribute vec2 inTexCoord;\n"
"attribute vec4 inTint;\n"
"attribute float inType;\n"
"varying vec2 outTexCoord;\n"
"varying vec4 outTint;\n"
"varying float outType;\n"
"void main() {\n"
"   gl_Position = uProjectionMatrix * vec4(inPosition, 0.0, 1.0);\n"
"   outTexCoord = inTexCoord;\n"
"   outTint = inTint;\n"
"   outType = inType;\n"
"}\n"
;

static const char* kCanvasFS = ""
#if defined(LD_PLATFORM_WINDOWS)
"#version 330\n"
#elif defined(LD_PLATFORM_WEB)
"precision mediump float;\n"
#endif
"uniform sampler2D uMainSampler;\n"
"varying vec2 outTexCoord;\n"
"varying vec4 outTint;\n"
"varying float outType;\n"
"void main() {\n"
"   if (outType == 0.0) gl_FragColor = texture2D(uMainSampler, outTexCoord).a * outTint.bgra;\n"
"   else gl_FragColor = outTint.bgra;\n"
//"   gl_FragColor = outTint.bgra;\n"
"}\n"
;

#define MAX_VERTICES (2000)
#define MAX_BATCHES (2000)
#define MAX_MATRICES (1000)

typedef struct canvas_batch
{
    int32_t texture;
    int32_t start;
    int32_t count;
} canvas_batch_t;

/* GL canvas */
struct canvas
{
    /* Common */
    canvas_vertex_t vertices[MAX_VERTICES];
    canvas_batch_t batches[MAX_BATCHES];
    mat2d_t matrices[MAX_MATRICES];
    mat2d_t matrix;
    enum draw_mode tempDrawMode;
    int32_t vertexCount;
    int32_t batchCount;
    int32_t matrixIndex;
    uint32_t color;
    float32_t alpha;
    float32_t width;
    float32_t height;

    /* GL */
    GLenum drawMode;
    GLuint program;
    GLuint vbo;
    GLuint vao;
    GLuint texture;
};

static GLuint gEmptyTexture = 0;
static canvas_t* pCurrentCanvas = NULL;

canvas_t* ldGfxCreateCanvas(float32_t width, float32_t height)
{
    GLuint program = ldGfxCreateProgram(kCanvasVS, kCanvasFS);
    GLuint vbo = ldGfxCreateVertexBuffer(NULL, sizeof(canvas_vertex_t) * 2000, GL_DYNAMIC_DRAW);
    canvas_t* pCanvas = (canvas_t*)ldPageMalloc(sizeof(canvas_t));
    memset(pCanvas, 0, sizeof(canvas_t));

    glBindAttribLocation(program, 0, "inPosition");
    glBindAttribLocation(program, 1, "inTexCoord");
    glBindAttribLocation(program, 2, "inTint");
    glBindAttribLocation(program, 3, "inType");

    mat4_t proj;

    ldMat4Orthographic(&proj, 0.0f, width, height, 0.0f, -100.0f, 100.0f);
    glUseProgram(program);
    glUniformMatrix4fv(glGetUniformLocation(program, "uProjectionMatrix"), 1, GL_FALSE, proj.data);

    byte_t emptyColor[] = { 0xff,0xff,0xff,0xff };
    gEmptyTexture = ldGfxCreateTexture2D(1, 1, GL_NEAREST, GL_CLAMP_TO_EDGE, emptyColor);


#if defined(LD_PLATFORM_WINDOWS)
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(canvas_vertex_t), (const void*)offsetof(canvas_vertex_t, position));
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(canvas_vertex_t), (const void*)offsetof(canvas_vertex_t, texcoord));
    glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(canvas_vertex_t), (const void*)offsetof(canvas_vertex_t, tint));
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(canvas_vertex_t), (const void*)offsetof(canvas_vertex_t, type));
    pCanvas->vao = vao;
#endif

    ldMat2dIdent(&pCanvas->matrix);
    pCanvas->program = program;
    pCanvas->vbo = vbo;
    pCanvas->texture = 0;
    pCanvas->alpha = 1.0f;
    pCanvas->color = 0xFFFFFF;
    pCanvas->width = width;
    pCanvas->height = height;
    pCanvas->drawMode = GL_TRIANGLES;

    glBindTexture(GL_TEXTURE_2D, gEmptyTexture);

    return pCanvas;
}

void ldGfxDestroyCanvas(canvas_t* pCanvas)
{
    assert(pCanvas != NULL);
    ldPageFree(pCanvas);
}

void ldGfxCanvasBind()
{
    glUseProgram(pCurrentCanvas->program);
#if defined(LD_PLATFORM_WEB)
    glBindBuffer(GL_ARRAY_BUFFER, pCurrentCanvas->vbo);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(canvas_vertex_t), (const void*)offsetof(canvas_vertex_t, position));
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(canvas_vertex_t), (const void*)offsetof(canvas_vertex_t, texcoord));
    glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(canvas_vertex_t), (const void*)offsetof(canvas_vertex_t, tint));
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(canvas_vertex_t), (const void*)offsetof(canvas_vertex_t, type));
#else
    glBindVertexArray(pCurrentCanvas->vao);
#endif
    glEnable(GL_BLEND);
}

void ldGfxCanvasFlush()
{
#if defined(LD_CONFIG_DEBUG)
    assert(pCurrentCanvas != NULL);
#endif

    if (pCurrentCanvas->vertexCount == 0) return;

    glBufferSubData(GL_ARRAY_BUFFER, 0, pCurrentCanvas->vertexCount * sizeof(canvas_vertex_t), pCurrentCanvas->vertices);

    int32_t batchCount = pCurrentCanvas->batchCount;
    int32_t lastTexture = pCurrentCanvas->texture;
    canvas_batch_t* pBatches = pCurrentCanvas->batches;
    GLenum drawMode = pCurrentCanvas->drawMode;

    for (int32_t index = 0; index < batchCount; ++index)
    {
        canvas_batch_t batch = pBatches[index];
        if (batch.texture != lastTexture)
        {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, batch.texture);
        }
        if (batch.count > 0)
            glDrawArrays(drawMode, batch.start, batch.count);
    }

    pCurrentCanvas->texture = lastTexture;
    pCurrentCanvas->vertexCount = 0;
    pCurrentCanvas->batchCount = 1;
    pCurrentCanvas->batches[0].texture = 0;
    pCurrentCanvas->batches[0].start = 0;
    pCurrentCanvas->batches[0].count = 0;
}

void ldGfxCanvasSetDrawMode(enum draw_mode drawMode)
{
#if defined(LD_CONFIG_DEBUG)
    assert(pCurrentCanvas != NULL);
#endif
    if (pCurrentCanvas->tempDrawMode != drawMode)
    {
        ldGfxCanvasFlush();
        pCurrentCanvas->tempDrawMode = drawMode;

        switch (drawMode)
        {
        case DRAW_TRIANGLES:
            pCurrentCanvas->drawMode = GL_TRIANGLES;
            break;
        case DRAW_LINE_LOOP:
            pCurrentCanvas->drawMode = GL_LINE_LOOP;
            break;
        case DRAW_LINE_STRIP:
            pCurrentCanvas->drawMode = GL_LINE_STRIP;
            break;
        case DRAW_POINTS:
            pCurrentCanvas->drawMode = GL_POINTS;
            break;
        default:
            pCurrentCanvas->drawMode = GL_TRIANGLES;
            break;
        }
    }
}
