#include "init_scene.h"

canvas_t* pCanvas;
image_t copImage;

void InitSceneCreate()
{
    pCanvas = ldGfxCreateCanvas(LD_CONFIG_WIDTH, LD_CONFIG_HEIGHT);
    ldGfxSetCanvas(pCanvas);
    ldGfxCanvasBind();
    ldGfxCanvasSetBlendMode(BLEND_NORMAL_NPM);

    ldLoadImage("data/assets/textures/cop.png", &copImage);
    glClearColor(0, 0, 0, 1);
}
void InitSceneUpdate(float32_t delta)
{}
void InitSceneRender()
{
    glClear(GL_COLOR_BUFFER_BIT);
    ldGfxCanvasFillRect(0, 0, 100, 100);
    ldGfxCanvasDrawImage(&copImage, ldMouseX(), ldMouseY());
    ldGfxCanvasFlush();
}
void InitSceneDestroy()
{
    ldDiscardImage(&copImage);
    ldGfxDestroyCanvas(pCanvas);
}
