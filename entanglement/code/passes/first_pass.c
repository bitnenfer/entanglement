#include "first_pass.h"
#include "../opengl.h"

void first_pass_create()
{
    glClearColor(0, 1, 0, 1);
    debug_print("first pass create\n");
}

void first_pass_update(float32_t delat)
{
    if (is_key_hit(KEYCODE_SPACE))
    {
        game_swap_state(&g_FirstPassState);
    }
}

void first_pass_render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void first_pass_destroy()
{
    debug_print("first pass destroy\n");
}
