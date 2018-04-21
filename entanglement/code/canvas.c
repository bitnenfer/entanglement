#include "canvas.h"

#if defined(LD_CONFIG_DEBUG)
#define LD_CANVAS_CHECK assert(pCurrentCanvas != NULL)
#else
#define LD_CANVAS_CHECK
#endif

extern canvas_t* pCurrentCanvas;

void ldGfxSetCanvas(canvas_t* pCanvas)
{
    pCurrentCanvas = pCanvas;
}
void ldGfxCanvasPushMatrix()
{
    LD_CANVAS_CHECK;
    assert(pCurrentCanvas->matrixIndex + 1 < MAX_MATRICES);
    pCurrentCanvas->matrices[pCurrentCanvas->matrixIndex++] = pCurrentCanvas->matrix;
}
void ldGfxCanvasPopMatrix()
{
    LD_CANVAS_CHECK;
    assert(pCurrentCanvas->matrixIndex - 1 >= 0);
    pCurrentCanvas->matrix = pCurrentCanvas->matrices[--pCurrentCanvas->matrixIndex];
}
void ldGfxCanvasIdentity()
{
    LD_CANVAS_CHECK;
    ldMat2dIdent(&pCurrentCanvas->matrix);
}
void ldGfxCanvasTranslate(float32_t x, float32_t y)
{
    LD_CANVAS_CHECK;
    mat2d_t temp = pCurrentCanvas->matrix;
    ldMat2DTranslate(&temp, &pCurrentCanvas->matrix, x, y);
    pCurrentCanvas->matrix = temp;
}
void ldGfxCanvasScale(float32_t x, float32_t y)
{
    LD_CANVAS_CHECK;
    mat2d_t temp = pCurrentCanvas->matrix;
    ldMat2DScale(&temp, &pCurrentCanvas->matrix, x, y);
    pCurrentCanvas->matrix = temp;
}
void ldGfxCanvasRotate(float32_t r)
{
    LD_CANVAS_CHECK;
    mat2d_t temp = pCurrentCanvas->matrix;
    ldMat2DRotate(&temp, &pCurrentCanvas->matrix, r);
    pCurrentCanvas->matrix = temp;
}
void ldGfxCanvasSetColor(uint32_t rgb)
{
    LD_CANVAS_CHECK;
    pCurrentCanvas->color = rgb;
}
void ldGfxCanvasSetAlpha(float32_t alpha)
{
    LD_CANVAS_CHECK;
    pCurrentCanvas->alpha = alpha;
}
void ldGfxCanvasFillRect(float32_t x, float32_t y, float32_t width, float32_t height)
{
    LD_CANVAS_CHECK;
    if (pCurrentCanvas->vertexCount > MAX_VERTICES)
    {
        ldGfxCanvasFlush();
    }
    canvas_vertex_t* pVertices = &pCurrentCanvas->vertices[pCurrentCanvas->vertexCount];
    float32_t xw = x + width;
    float32_t yh = y + height;
    vec2_t p0 = { x, y };
    vec2_t p1 = { x, yh };
    vec2_t p2 = { xw, yh };
    vec2_t p3 = { xw, y };
    vec2_t t0, t1, t2, t3;
    mat2d_t matrix = pCurrentCanvas->matrix;
    uint32_t tint = 0xffffffff;

    ldMat2DVec2Mul(&t0, &matrix, &p0);
    ldMat2DVec2Mul(&t1, &matrix, &p1);
    ldMat2DVec2Mul(&t2, &matrix, &p2);
    ldMat2DVec2Mul(&t3, &matrix, &p3);

    pVertices[0].position = t0;
    pVertices[0].tint = tint;
    pVertices[0].type = 1.0f;
    pVertices[1].position = t1;
    pVertices[1].tint = tint;
    pVertices[1].type = 1.0f;
    pVertices[2].position = t2;
    pVertices[2].tint = tint;
    pVertices[2].type = 1.0f;
    pVertices[3].position = t0;
    pVertices[3].tint = tint;
    pVertices[3].type = 1.0f;
    pVertices[4].position = t2;
    pVertices[4].tint = tint;
    pVertices[4].type = 1.0f;
    pVertices[5].position = t3;
    pVertices[5].tint = tint;
    pVertices[5].type = 1.0f;

    pCurrentCanvas->batches[pCurrentCanvas->batchCount - 1].count += 6;
    pCurrentCanvas->vertexCount += 6;
}
void ldGfxCanvasDrawImage(image_t* pImage, float32_t x, float32_t y)
{
    LD_CANVAS_CHECK;
    if (pCurrentCanvas->vertexCount > MAX_VERTICES ||
        pCurrentCanvas->batchCount > MAX_BATCHES)
    {
        ldGfxCanvasFlush();
    }

    canvas_batch_t* pBatch = &pCurrentCanvas->batches[pCurrentCanvas->batchCount-1];

    if (pBatch->texture != pImage->textureId)
    {
        canvas_batch_t* pNextBatch = pBatch + 1;
        pNextBatch->start = pCurrentCanvas->vertexCount;
        pNextBatch->count = 0;
        pNextBatch->texture = pImage->textureId;
        pBatch = pNextBatch;
        pCurrentCanvas->batchCount += 1;
    }

    canvas_vertex_t* pVertices = &pCurrentCanvas->vertices[pCurrentCanvas->vertexCount];
    float32_t xw = x + pImage->fwidth;
    float32_t yh = y + pImage->fheight;
    vec2_t p0 = { x, y };
    vec2_t p1 = { x, yh };
    vec2_t p2 = { xw, yh };
    vec2_t p3 = { xw, y };
    vec2_t t0, t1, t2, t3;
    mat2d_t matrix = pCurrentCanvas->matrix;
    uint32_t tint = 0xffffffff;
    vec2_t uv0 = { 0.0f, 0.0f };
    vec2_t uv1 = { 0.0f, 1.0f };
    vec2_t uv2 = { 1.0f, 1.0f };
    vec2_t uv3 = { 1.0f, 0.0f };

    ldMat2DVec2Mul(&t0, &matrix, &p0);
    ldMat2DVec2Mul(&t1, &matrix, &p1);
    ldMat2DVec2Mul(&t2, &matrix, &p2);
    ldMat2DVec2Mul(&t3, &matrix, &p3);

    pVertices[0].position = t0;
    pVertices[0].texcoord = uv0;
    pVertices[0].tint = tint;
    pVertices[0].type = 0.0f;
    pVertices[1].position = t1;
    pVertices[1].texcoord = uv1;
    pVertices[1].tint = tint;
    pVertices[1].type = 0.0f;
    pVertices[2].position = t2;
    pVertices[2].texcoord = uv2;
    pVertices[2].tint = tint;
    pVertices[2].type = 0.0f;
    pVertices[3].position = t0;
    pVertices[3].texcoord = uv0;
    pVertices[3].tint = tint;
    pVertices[3].type = 0.0f;
    pVertices[4].position = t2;
    pVertices[4].texcoord = uv2;
    pVertices[4].tint = tint;
    pVertices[4].type = 0.0f;
    pVertices[5].position = t3;
    pVertices[5].texcoord = uv3;
    pVertices[5].tint = tint;
    pVertices[5].type = 0.0f;

    pBatch->count += 6;
    pCurrentCanvas->vertexCount += 6;
}
void ldGfxCanvasDrawImageFrame(image_t* pImage, float32_t x, float32_t y, float32_t fx, float32_t fy, float32_t fw, float32_t fh)
{
    LD_CANVAS_CHECK;
    if (pCurrentCanvas->vertexCount > MAX_VERTICES ||
        pCurrentCanvas->batchCount > MAX_BATCHES)
    {
        ldGfxCanvasFlush();
    }

    canvas_batch_t* pBatch = &pCurrentCanvas->batches[pCurrentCanvas->batchCount - 1];

    if (pBatch->texture != pImage->textureId)
    {
        canvas_batch_t* pNextBatch = pBatch + 1;
        pNextBatch->start = pCurrentCanvas->vertexCount;
        pNextBatch->count = 0;
        pNextBatch->texture = pImage->textureId;
        pBatch = pNextBatch;
        pCurrentCanvas->batchCount += 1;
    }

    canvas_vertex_t* pVertices = &pCurrentCanvas->vertices[pCurrentCanvas->vertexCount];
    float32_t xw = x + fw;
    float32_t yh = y + fh;
    vec2_t p0 = { x, y };
    vec2_t p1 = { x, yh };
    vec2_t p2 = { xw, yh };
    vec2_t p3 = { xw, y };
    vec2_t t0, t1, t2, t3;
    mat2d_t matrix = pCurrentCanvas->matrix;
    uint32_t tint = 0xffffffff;
    float32_t u0 = fx / pImage->fwidth;
    float32_t v0 = fy / pImage->fheight;
    float32_t u1 = (fx + fw) / pImage->fwidth;
    float32_t v1 = (fy + fh) / pImage->fheight;
    vec2_t uv0 = { u0, v0 };
    vec2_t uv1 = { u0, v1 };
    vec2_t uv2 = { u1, v1 };
    vec2_t uv3 = { u1, v0 };

    ldMat2DVec2Mul(&t0, &matrix, &p0);
    ldMat2DVec2Mul(&t1, &matrix, &p1);
    ldMat2DVec2Mul(&t2, &matrix, &p2);
    ldMat2DVec2Mul(&t3, &matrix, &p3);

    pVertices[0].position = t0;
    pVertices[0].texcoord = uv0;
    pVertices[0].tint = tint;
    pVertices[0].type = 0.0f;
    pVertices[1].position = t1;
    pVertices[1].texcoord = uv1;
    pVertices[1].tint = tint;
    pVertices[1].type = 0.0f;
    pVertices[2].position = t2;
    pVertices[2].texcoord = uv2;
    pVertices[2].tint = tint;
    pVertices[2].type = 0.0f;
    pVertices[3].position = t0;
    pVertices[3].texcoord = uv0;
    pVertices[3].tint = tint;
    pVertices[3].type = 0.0f;
    pVertices[4].position = t2;
    pVertices[4].texcoord = uv2;
    pVertices[4].tint = tint;
    pVertices[4].type = 0.0f;
    pVertices[5].position = t3;
    pVertices[5].texcoord = uv3;
    pVertices[5].tint = tint;
    pVertices[5].type = 0.0f;

    pBatch->count += 6;
    pCurrentCanvas->vertexCount += 6;
}

void ldGfxCanvasSetBlendMode(enum blend_mode blendMode)
{
    ldGfxCanvasFlush();
    ldGfxSetBlendMode(blendMode);
}

uint32_t ldGfxCanvasGetColor()
{
    LD_CANVAS_CHECK;
    return pCurrentCanvas->color;
}
float32_t ldGfxCanvasGetAlpha()
{
    LD_CANVAS_CHECK;
    return pCurrentCanvas->alpha;
}
float32_t ldGfxCanvasGetWidth()
{
    LD_CANVAS_CHECK;
    return pCurrentCanvas->width;
}
float32_t ldGfxCanvasGetHeight()
{
    LD_CANVAS_CHECK;
    return pCurrentCanvas->height;
}