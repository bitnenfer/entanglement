#ifndef _OPENGL_H_
#define _OPENGL_H_

#include <stdlib.h>
#include <stdio.h>

#include "platform.h"

#if defined(LD_PLATFORM_WINDOWS)
#include "config.h"
#include "types.h"
#include "glad/glad.h"

static const char kShaderHeader[] = "#version 120\n";
static const size_t kShaderHeaderSize = sizeof(kShaderHeader) - 1;

#elif defined(LD_PLATFORM_WEB)

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#define __debugbreak()

static const char kShaderHeader[] = "precision mediump float;\n";
static const size_t kShaderHeaderSize = sizeof(kShaderHeader) - 1;

#endif

#if defined(LD_CONFIG_DEBUG)
#define LD_OPENGL_ERROR_CHECK() { \
	GLenum error = glGetError();\
	if (error != GL_NO_ERROR)\
    {\
        ldDebugPrint("OpenGL Error. Error Code: 0x%X\n", error);\
        __debugbreak();\
        exit(-1);\
    }\
}

#else
#define LD_OPENGL_ERROR_CHECK()
#endif

#endif // !_OPENGL32_H_
