#ifndef _GLLD_UTILS_H_
#define _GLLD_UTILS_H_

#include "opengl.h"

typedef struct gl_blend_struct
{
    GLenum srcRGB;
    GLenum dstRGB;
    GLenum equRGB;
    GLenum srcAlpha;
    GLenum dstAlpha;
    GLenum equAlpha;
} gl_blend_struct_t;

static const gl_blend_struct_t kGunkBlendModeMap[8] = {
    { GL_ONE, GL_ONE_MINUS_SRC_ALPHA, GL_FUNC_ADD, GL_ONE, GL_ONE_MINUS_SRC_ALPHA, GL_FUNC_ADD },
    { GL_ONE, GL_DST_ALPHA, GL_FUNC_ADD, GL_ONE, GL_DST_ALPHA, GL_FUNC_ADD },
    { GL_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA, GL_FUNC_ADD, GL_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA, GL_FUNC_ADD },
    { GL_ONE, GL_ONE_MINUS_SRC_COLOR, GL_FUNC_ADD, GL_ONE, GL_ONE_MINUS_SRC_COLOR, GL_FUNC_ADD },
    { GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_FUNC_ADD, GL_ONE, GL_DST_ALPHA, GL_FUNC_ADD },
    { GL_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA, GL_FUNC_ADD, GL_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA, GL_FUNC_ADD },
    { GL_SRC_ALPHA, GL_ONE_MINUS_SRC_COLOR, GL_FUNC_ADD, GL_ONE, GL_ONE_MINUS_SRC_COLOR, GL_FUNC_ADD }
};

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
        ldExit(-1);
    }

    glGetShaderiv(fshader, GL_COMPILE_STATUS, &shaderOk);
    if (shaderOk == GL_FALSE)
    {
        GLsizei length;
        char* pBufferInfoLog = (char*)ldScratchMalloc(1024, 4);
        glGetShaderInfoLog(fshader, 1024, &length, pBufferInfoLog);
        ldDebugPrint("Fragment Shader Error\n\n%s\n\n", pBufferInfoLog);
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

static LD_FORCEINLINE GLuint ldGfxCreateTexture2D(int32_t width, int32_t height, GLenum filter, GLenum wrap, const void* pPixels)
{
    GLuint texture;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pPixels);
    glBindTexture(GL_TEXTURE_2D, 0);
    return texture;
}

LD_FORCEINLINE int32_t ldGfxCreateTexture2DNearestClamp(int32_t width, int32_t height, const void* pPixels)
{
    GLuint texture;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pPixels);
    glBindTexture(GL_TEXTURE_2D, 0);
    return texture;
}

LD_FORCEINLINE void ldGfxDiscardTexture(int32_t texture)
{
    GLuint tex = texture;
    glDeleteTextures(1, &tex);
}

static LD_FORCEINLINE void ldGfxSetBlendMode(enum blend_mode blendMode)
{
    gl_blend_struct_t blend = kGunkBlendModeMap[(int32_t)blendMode];
    glBlendFuncSeparate(blend.srcRGB, blend.dstRGB, blend.srcAlpha, blend.dstAlpha);
    glBlendEquationSeparate(blend.equRGB, blend.equAlpha);
}

#endif // !_GL_LD_UTILS_H_
