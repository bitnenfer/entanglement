#ifndef _CANVAS_H_
#define _CANVAS_H_

#include "types.h"
#include "math.h"

struct canvas_vertex
{
    vec2_t position;
    vec2_t texcoord;
    uint32_t tint;
    float32_t type; // type 0 = texture 1 = flat
};
struct image
{
    int32_t textureId;
    int32_t width;
    int32_t height;
    float32_t fwidth;
    float32_t fheight;
};
enum draw_mode
{
    DRAW_TRIANGLES,
    DRAW_LINE_LOOP,
    DRAW_LINE_STRIP,
    DRAW_POINTS
};

struct canvas;

typedef struct canvas_vertex canvas_vertex_t;
typedef struct canvas canvas_t;
typedef struct image image_t;

canvas_t* ldGfxCreateCanvas(float32_t width, float32_t height);
void ldGfxDestroyCanvas(canvas_t* pCanvas);
void ldGfxSetCanvas(canvas_t* pCanvas);
void ldGfxCanvasBind();
void ldGfxCanvasPushMatrix();
void ldGfxCanvasPopMatrix();
void ldGfxCanvasIdentity();
void ldGfxCanvasTranslate(float32_t x, float32_t y);
void ldGfxCanvasScale(float32_t x, float32_t y);
void ldGfxCanvasRotate(float32_t r);
void ldGfxCanvasFlush();
void ldGfxCanvasSetColor(uint32_t rgb);
void ldGfxCanvasSetAlpha(float32_t alpha);
void ldGfxCanvasFillRect(float32_t x, float32_t y, float32_t width, float32_t height);
void ldGfxCanvasDrawImage(image_t* pImage, float32_t x, float32_t y);
void ldGfxCanvasDrawImageFrame(image_t* pImage, float32_t x, float32_t y, float32_t fx, float32_t fy, float32_t fw, float32_t fh);
void ldGfxCanvasSetBlendMode(enum blend_mode blendMode);
void ldGfxCanvasSetDrawMode(enum draw_mode drawMode);
void ldGfxCanvasAddFillPoint(float32_t x, float32_t y);
void ldGfxCanvasAddTexPoint(float32_t x, float32_t y, float32_t u, float32_t v);
void ldGfxCanvasStrokeCircle(float32_t x, float32_t y, float32_t radius);
void ldGfxCanvasStrokeRect(float32_t x, float32_t y, float32_t width, float32_t height);
uint32_t ldGfxCanvasGetColor();
float32_t ldGfxCanvasGetAlpha();
float32_t ldGfxCanvasGetWidth();
float32_t ldGfxCanvasGetHeight();

#endif // !_CANVAS_H_
