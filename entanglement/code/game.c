
#include "types.h"
#include "alloc.h"
#include "config.h"
#include "platform.h"
#include "opengl32.h"
#include "boot.h"

void start_game()
{
    float32_t vertices[] = { -1, 1, -1, -7, 7, 1 };
    GLuint program = glCreateProgram();
    GLuint vshader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fshader = glCreateShader(GL_FRAGMENT_SHADER);
    GLuint vbo;

    const char* v_shader_source =
#if defined(PLATFORM_WEB)
        "precision mediump float;\n"
#else
        "#version 120\n"
#endif
        "attribute vec2 vert_position;\n"
        "void main() {\n"
        "    gl_Position = vec4(vert_position, 0.0, 1.0);"
        "}";

    const char* f_shader_source =
#if defined(PLATFORM_WEB)
        "precision mediump float;\n"
#else
        "#version 120\n"
#endif
        "float circle(vec2 position, vec2 origin, float radius)\n"
        "{\n"
        "    return length(position - origin) - radius;\n"
        "}\n"
        "\n"
        "void main()\n"
        "{\n"
        "    vec2 texcoord = gl_FragCoord.xy / vec2(512.0);\n"
        "    gl_FragColor = vec4(circle(texcoord, vec2(0.5), 0.25));\n"
        "}\n"
        ;

    glShaderSource(vshader, 1, &v_shader_source, NULL);
    glShaderSource(fshader, 1, &f_shader_source, NULL);
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
        exit(-1);
    }

    glGetShaderiv(fshader, GL_COMPILE_STATUS, &shader_ok);
    if (shader_ok == GL_FALSE)
    {
        GLsizei length;
        char* p_buffer_info_log = (char*)scratch_alloc(1024, 4);
        glGetShaderInfoLog(fshader, 1024, &length, p_buffer_info_log);
        debug_print("Fragment Shader Error\n\n%s\n\n", p_buffer_info_log);
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
}

/* Should update at 0.16ms */
void update_game(float32_t delta)
{
    if (is_key_down(KEYCODE_ESCAPE))
    {
        quit_game();
    }
}

void render_game()
{
    glClearColor(mouse_x() / CONFIG_WIDTH, mouse_y() / CONFIG_HEIGHT, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

