#ifndef _GLUTILS_H_
#define _GLUTILS_H_

#include "opengl.h"

static FORCEINLINE GLuint glu_create_program(const char* p_vshader, const char* p_fshader)
{
    GLint shader_ok;
    GLuint program = glCreateProgram();
    GLuint vshader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fshader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vshader, 1, &p_vshader, NULL);
    glShaderSource(fshader, 1, &p_fshader, NULL);
    glCompileShader(vshader);
    glCompileShader(fshader);

    glGetShaderiv(vshader, GL_COMPILE_STATUS, &shader_ok);
    if (shader_ok == GL_FALSE)
    {
        GLsizei length;
        char* p_buffer_info_log = (char*)scratch_alloc(1024, 4);
        glGetShaderInfoLog(vshader, 1024, &length, p_buffer_info_log);
        debug_print("Vertex Shader Error\n\n%s\n\n", p_buffer_info_log);
        debug_print("Shader Source:\n%s\n", p_vshader);
        exit(-1);
    }

    glGetShaderiv(fshader, GL_COMPILE_STATUS, &shader_ok);
    if (shader_ok == GL_FALSE)
    {
        GLsizei length;
        char* p_buffer_info_log = (char*)scratch_alloc(1024, 4);
        glGetShaderInfoLog(fshader, 1024, &length, p_buffer_info_log);
        debug_print("Fragment Shader Error\n\n%s\n\n", p_buffer_info_log);
        debug_print("Shader Source:\n%s\n", p_fshader);
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

    return program;
}

static FORCEINLINE GLuint glu_create_vertex_buffer(const void* p_data, size_t size, GLenum usage)
{
    GLuint vbo;

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, size, p_data, usage);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return vbo;
}

static FORCEINLINE void glu_bind_vertex_buffer(GLuint vbo)
{
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
}
#endif // !_GL_UTILS_H_
