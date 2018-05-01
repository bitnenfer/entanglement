#define TINYC2_IMPLEMENTATION

#include "../thirdparty/tinyc2.h"
#include "init_scene.h"

c2AABB b0, b1;
c2Circle c0;

void StrokeAABB(c2AABB AABB)
{
    float32_t x = AABB.min.x;
    float32_t y = AABB.min.y;
    float32_t xw = AABB.max.x;
    float32_t yh = AABB.max.y;

    ldGfxCanvasSetDrawMode(DRAW_LINE_LOOP);
    ldGfxCanvasAddFillPoint(x, y);
    ldGfxCanvasAddFillPoint(xw, y);
    ldGfxCanvasAddFillPoint(xw, yh);
    ldGfxCanvasAddFillPoint(x, yh);
    ldGfxCanvasFlush();
}

void StrokeCircle(c2Circle circle)
{
    ldGfxCanvasSetDrawMode(DRAW_LINE_LOOP);
    for (int32_t i = 0; i < 360; ++i)
    {
        float32_t r = ldDegToRad((float32_t)i);
        float32_t x = cosf(r) * circle.r;
        float32_t y = sinf(r) * circle.r;
        ldGfxCanvasAddFillPoint(circle.p.x + x, circle.p.y + y);
    }
    ldGfxCanvasFlush();
}

void InitSceneCreate()
{
    b0.min.x = 100.0f;
    b0.min.y = 100.0f;
    b0.max.x = b0.min.x + 200.0f;
    b0.max.y = b0.min.y + 100.0f;

    b1.min.x = 0.0f;
    b1.min.y = 0.0f;
    b1.max.x = b1.min.x + 50.0f;
    b1.max.y = b1.min.y + 50.0f;

    c0.p.x = 300.0f;
    c0.p.y = 300.0f;
    c0.r = 60.0f;

    glClearColor(0, 0, 0, 1);
    glLineWidth(2.0f);
}
void InitSceneUpdate(float32_t delta)
{
    b1.min.x = ldMouseX();
    b1.min.y = ldMouseY();
    b1.max.x = b1.min.x + 50.0f;
    b1.max.y = b1.min.y + 50.0f;

    {
        c2Manifold colInfo = { 0 };
        c2AABBtoAABBManifold(b0, b1, &colInfo);

        if (colInfo.count > 0)
        {
            float32_t px = colInfo.depths[0] * colInfo.n.x;
            float32_t py = colInfo.depths[0] * colInfo.n.y;

            b0.min.x -= px;
            b0.min.y -= py;
            b0.max.x -= px;
            b0.max.y -= py;
        }
    }

    {
        c2Manifold colInfo = { 0 };
        
        c2CircletoAABBManifold(c0, b1, &colInfo);

        if (colInfo.count > 0)
        {
            float32_t px = colInfo.depths[0] * colInfo.n.x;
            float32_t py = colInfo.depths[0] * colInfo.n.y;

            c0.p.x -= px;
            c0.p.y -= py;
        }
    }

    {
        c2Manifold colInfo = { 0 };

        c2CircletoAABBManifold(c0, b0, &colInfo);

        if (colInfo.count > 0)
        {
            float32_t px = colInfo.depths[0] * colInfo.n.x;
            float32_t py = colInfo.depths[0] * colInfo.n.y;

            b0.min.x += px;
            b0.min.y += py;
            b0.max.x += px;
            b0.max.y += py;

            c0.p.x -= px;
            c0.p.y -= py;
        }
    }

    {
        c2Manifold colInfo = { 0 };

        c2CircletoAABBManifold(c0, b1, &colInfo);

        if (colInfo.count > 0)
        {
            float32_t px = colInfo.depths[0] * colInfo.n.x;
            float32_t py = colInfo.depths[0] * colInfo.n.y;

            c0.p.x -= px;
            c0.p.y -= py;
        }
    }

    {
        c2Manifold colInfo = { 0 };
        c2AABBtoAABBManifold(b0, b1, &colInfo);

        if (colInfo.count > 0)
        {
            float32_t px = colInfo.depths[0] * colInfo.n.x;
            float32_t py = colInfo.depths[0] * colInfo.n.y;

            b0.min.x -= px;
            b0.min.y -= py;
            b0.max.x -= px;
            b0.max.y -= py;
        }
    }
}
void InitSceneRender()
{
    glClear(GL_COLOR_BUFFER_BIT);
    StrokeAABB(b0);
    StrokeAABB(b1);
    StrokeCircle(c0);
    ldGfxCanvasFlush();
}
void InitSceneDestroy()
{
}
