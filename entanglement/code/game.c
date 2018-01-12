#include "game.h"
#include "types.h"
#include "alloc.h"
#include "config.h"
#include "platform.h"
#include "glutils.h"
#include "boot.h"

#include "passes/first_pass.h"
#include "utils/camera.h"

#include <assert.h>

state_t* g_pCurrentState = NULL;
state_t* g_pNextState = NULL;

void game_swap_state(state_t* p_next_state)
{
    g_pNextState = p_next_state;
}

void start_game()
{
    camera_init();
    game_swap_state(&g_FirstPassState);
}

/* Should update at 0.16ms */
void update_game(float32_t delta)
{
    if (g_pNextState != NULL)
    {
        if (g_pCurrentState != NULL && g_pCurrentState->fp_destroy != NULL)
        {
            g_pCurrentState->fp_destroy();
        }

        g_pNextState->fp_create();
        g_pCurrentState = g_pNextState;
        g_pNextState = NULL;
    }

    if (g_pCurrentState != NULL && g_pCurrentState->fp_update)
    {
        g_pCurrentState->fp_update(delta);
    }

    scratch_clear();
}

void render_game()
{
    if (g_pCurrentState != NULL && g_pCurrentState->fp_render)
    {
        g_pCurrentState->fp_render();
    }
}

