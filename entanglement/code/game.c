#include "game.h"
#include "types.h"
#include "alloc.h"
#include "config.h"
#include "platform.h"
#include "glutils.h"
#include "boot.h"

#include "game/init_scene.h"

#include <assert.h>
#include <stdlib.h>
#include <time.h>

state_t* pCurrentState = NULL;
state_t* pNextState = NULL;
canvas_t* pCanvas;

// Assets
image_t tamaBodyImage;
image_t tamaHeadParts[4] = { 0 };
image_t tamaEyeParts[4] = { 0 };
image_t tamaMouthParts[4] = { 0 };
image_t bgImage;

void ldGameSwapState(state_t* pNext)
{
    pNextState = pNext;
}

void ldGameStart()
{
    // Change the initial state here
    srand((uint32_t)time(NULL));
    pCanvas = ldGfxCreateCanvas(LD_CONFIG_WIDTH, LD_CONFIG_HEIGHT);
    ldGfxSetCanvas(pCanvas);
    ldGfxCanvasBind();
    ldGfxCanvasSetBlendMode(BLEND_NORMAL_NPM);
    ldGameSwapState(&gInitScene);

    // Load assets here

}

/* Should update at 0.16ms */
void ldGameUpdate(float32_t delta)
{
    if (pNextState != NULL)
    {
        if (pCurrentState != NULL && pCurrentState->fpDestroy != NULL)
        {
            pCurrentState->fpDestroy();
        }

        pNextState->fpCreate();
        pCurrentState = pNextState;
        pNextState = NULL;
    }

    if (pCurrentState != NULL && pCurrentState->fpUpdate)
    {
        pCurrentState->fpUpdate(delta);
    }

    ldScratchReset();
}

void ldGameRender()
{
    if (pCurrentState != NULL && pCurrentState->fpRender)
    {
        pCurrentState->fpRender();
    }
}

