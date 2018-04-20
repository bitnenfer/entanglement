#ifndef _GLLD_UTILS_H_
#define _GLLD_UTILS_H_

#include "opengl.h"

static LD_FORCEINLINE GLuint ldGfxCreateProgram(const char* pVShader, const char* pFShader)
{
    GLint shaderOk;
    GLuint program = glCreateProgram();
    GLuint vshader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fshader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vshader, 1, &pVShader, NULL);
    glShaderSource(fshader, 1, &pFShader, NULL);
    glCompileShader(vshader);
    glCompileShader(fshader);

    glGetShaderiv(vshader, GL_COMPILE_STATUS, &shaderOk);
    if (shaderOk == GL_FALSE)
    {
        GLsizei length;
        char* pBufferInfoLog = (char*)ldScratchMalloc(1024, 4);
        glGetShaderInfoLog(vshader, 1024, &length, pBufferInfoLog);
        ldDebugPrint("Vertex Shader Error\n\n%s\n\n", pBufferInfoLog);
        ldDebugPrint("Shader Source:\n%s\n", pVShader);
        ldExit(-1);
    }

    glGetShaderiv(fshader, GL_COMPILE_STATUS, &shaderOk);
    if (shaderOk == GL_FALSE)
    {
        GLsizei length;
        char* pBufferInfoLog = (char*)ldScratchMalloc(1024, 4);
        glGetShaderInfoLog(fshader, 1024, &length, pBufferInfoLog);
        ldDebugPrint("Fragment Shader Error\n\n%s\n\n", pBufferInfoLog);
        ldDebugPrint("Shader Source:\n%s\n", pFShader);
        ldExit(-1);
    }

    glAttachShader(program, vshader);
    glAttachShader(program, fshader);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &shaderOk);
    if (shaderOk == GL_FALSE)
    {
        GLsizei length;
        char* pBufferInfoLog = (char*)ldScratchMalloc(1024, 4);
        glGetProgramInfoLog(vshader, 1024, &length, pBufferInfoLog);
        ldDebugPrint("Program Link Error: %s", pBufferInfoLog);
        ldExit(-1);
    }

    return program;
}

static LD_FORCEINLINE GLuint ldGfxCreateVertexBuffer(const void* pData, size_t size, GLenum usage)
{
    GLuint vbo;

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, size, pData, usage);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return vbo;
}

static LD_FORCEINLINE void ldGfxBindVertexBuffer(GLuint vbo)
{
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
}
#endif // !_GL_LD_UTILS_H_
