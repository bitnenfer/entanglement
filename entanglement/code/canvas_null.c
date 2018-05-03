#include "canvas.h"

#define MAX_VERTICES (2000)
#define MAX_BATCHES (2000)
#define MAX_MATRICES (1000)

typedef struct canvas_batch
{
    int32_t texture;
    int32_t start;
    int32_t count;
} canvas_batch_t;

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
};

static canvas_t* pCurrentCanvas = NULL;

canvas_t* ldGfxCreateCanvas(float32_t width, float32_t height)
{
	return NULL;
}

void ldGfxDestroyCanvas(canvas_t* pCanvas)
{
    assert(pCanvas != NULL);
}

void ldGfxCanvasBind()
{
#if defined(LD_CONFIG_DEBUG)
    assert(pCurrentCanvas != NULL);
#endif
}

void ldGfxCanvasFlush()
{
#if defined(LD_CONFIG_DEBUG)
    assert(pCurrentCanvas != NULL);
#endif
}

void ldGfxCanvasSetDrawMode(enum draw_mode drawMode)
{
#if defined(LD_CONFIG_DEBUG)
    assert(pCurrentCanvas != NULL);
#endif
}

void ldGfxSetBlendMode(enum blend_mode blendMode)
{
}

int32_t ldGfxCreateTexture2DNearestClamp(int32_t width, int32_t height, const void* pPixels)
{
    return 0;
}

void ldGfxDiscardTexture(int32_t texture)
{
}
