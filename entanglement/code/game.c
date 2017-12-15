
#include "types.h"
#include "alloc.h"
#include "config.h"
#include "platform.h"
#include "opengl32.h"
#include "boot.h"

#include <assert.h>

GLuint u_time_location = 0;
float32_t time = 0.0;

void start_game()
{
    float32_t vertices[] = { -1, 1, -1, -7, 7, 1 };
    GLuint program = glCreateProgram();
    GLuint vshader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fshader = glCreateShader(GL_FRAGMENT_SHADER);
    GLuint vbo;

    file_binary_t* p_vshader_file = file_binary_load_with_header("data/shaders/flat.vert", LOAD_SCRATCH, k_ShaderHeader, k_ShaderHeaderSize);
    file_binary_t* p_fshader_file = file_binary_load_with_header("data/shaders/flat.frag", LOAD_SCRATCH, k_ShaderHeader, k_ShaderHeaderSize);

    assert(p_vshader_file != NULL && p_fshader_file != NULL);

    const char* p_vshader_code = (const char*)file_binary_get_data(p_vshader_file);
    const char* p_fshader_code = (const char*)file_binary_get_data(p_fshader_file);

    glShaderSource(vshader, 1, &p_vshader_code, NULL);
    glShaderSource(fshader, 1, &p_fshader_code, NULL);
    glCompileShader(vshader);
    glCompileShader(fshader);

    GLint shader_ok;
    glGetShaderiv(vshader, GL_COMPILE_STATUS, &shader_ok);
    if (shader_ok == GL_FALSE)
    {
        GLsizei length;
        char* p_buffer_info_log = (char*)scratch_alloc(1024, 4);
        glGetShaderInfoLog(vshader, 1024, &length, p_buffer_info_log);
        debug_print("Vertex Shader Error\n\n%s\n\n", p_buffer_info_log);
        debug_print("Shader Source:\n%s\n", p_vshader_code);
        exit(-1);
    }

    glGetShaderiv(fshader, GL_COMPILE_STATUS, &shader_ok);
    if (shader_ok == GL_FALSE)
    {
        GLsizei length;
        char* p_buffer_info_log = (char*)scratch_alloc(1024, 4);
        glGetShaderInfoLog(fshader, 1024, &length, p_buffer_info_log);
        debug_print("Fragment Shader Error\n\n%s\n\n", p_buffer_info_log);
        debug_print("Shader Source:\n%s\n", p_fshader_code);
        exit(-1);
    }

    glAttachShader(program, vshader);
    glAttachShader(program, fshader);
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &shader_ok);
    if (shader_ok == GL_FALSE)
    {
        GLsizei length;
        char* p_buffer_info_log = (char*)scratch_alloc(1024, 4);
        glGetProgramInfoLog(vshader, 1024, &length, p_buffer_info_log);
        debug_print("Program Link Error: %s", p_buffer_info_log);
        exit(-1);
    }

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glUseProgram(program);
    glBindAttribLocation(program, 0, "vert_position");
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 8, NULL);
    OPENGL_ERROR_CHECK();
    scratch_clear();

    u_time_location = glGetUniformLocation(program, "u_time");
    glUniform2f(glGetUniformLocation(program, "u_resolution"), CONFIG_WIDTH, CONFIG_HEIGHT);
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

