
#include "types.h"
#include "alloc.h"
#include "config.h"
#include "platform.h"
#include "glutils.h"
#include "boot.h"

#include <assert.h>

GLuint u_time_location = 0;
float32_t time = 0.0;

void start_game()
{
    float32_t vertices[] = { -1, 1, -1, -7, 7, 1 };
    GLuint program;
    GLuint vbo;

    file_binary_t* p_vshader_file = file_binary_load_with_header("data/shaders/flat.vert", LOAD_SCRATCH, k_ShaderHeader, k_ShaderHeaderSize);
    file_binary_t* p_fshader_file = file_binary_load_with_header("data/shaders/flat.frag", LOAD_SCRATCH, k_ShaderHeader, k_ShaderHeaderSize);

    assert(p_vshader_file != NULL && p_fshader_file != NULL);

    program = glu_create_program(file_binary_get_data(p_vshader_file), file_binary_get_data(p_fshader_file));
    vbo = glu_create_vertex_buffer(vertices, sizeof(vertices), GL_STATIC_DRAW);
    glu_bind_vertex_buffer(vbo);

    glUseProgram(program);
    glBindAttribLocation(program, 0, "vert_position");
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 8, NULL);
    
    OPENGL_ERROR_CHECK();

    u_time_location = glGetUniformLocation(program, "u_time");
    glUniform2f(glGetUniformLocation(program, "u_resolution"), CONFIG_WIDTH, CONFIG_HEIGHT);
 
    scratch_clear();
}

/* Should update at 0.16ms */
void update_game(float32_t delta)
{
    if (is_key_down(KEYCODE_ESCAPE))
    {
        quit_game();
    }

    if (is_key_hit(KEYCODE_SPACE))
    {
        debug_print("key hit\n");
    }

    if (is_mouse_hit(MOUSE_BUTTON_LEFT))
    {
        debug_print("mouse hit\n");
    }

    if (is_mouse_down(MOUSE_BUTTON_LEFT))
    {
        debug_print("mouse down\n");
    }

    time += 0.01f;
}

void render_game()
{
    glUniform1f(u_time_location, time);
    glClearColor(mouse_x() / CONFIG_WIDTH, mouse_y() / CONFIG_HEIGHT, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

