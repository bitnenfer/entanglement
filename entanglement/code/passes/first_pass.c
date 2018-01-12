#include "first_pass.h"
#include "../opengl.h"

void first_pass_create()
{
    vec3_t camera_pos = { 0, 0, -7 };
    glClearColor(0, 1, 0, 1);
    camera_set_perspective(3.14f / 4.0f, CONFIG_ASPECT, 0.01f, 1000.0f);
    camera_set_position(&camera_pos);
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
