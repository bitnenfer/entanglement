#include "game.h"
#include "types.h"
#include "alloc.h"
#include "config.h"
#include "platform.h"
#include "glutils.h"
#include "boot.h"

#include "game/init_scene.h"

#include <assert.h>

state_t* pCurrentState = NULL;
state_t* pNextState = NULL;

void ldGameSwapState(state_t* pNext)
{
    pNextState = pNext;
}

void ldGameStart()
{
    // Change the initial state here
    ldGameSwapState(&gInitScene);
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

