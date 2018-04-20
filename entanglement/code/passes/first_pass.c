#include "first_pass.h"
#include "../math.h"
#include "../opengl.h"

static GLuint program;
static GLuint vbo;

void first_pass_create()
{
    float32_t vertices[] = {
        -1.0f, -1.0f,
        -1.0f, +7.0f,
        +7.0f, -1.0f
    };

    file_binary_t* pPlasmaVs = ldFileBinaryLoadWithHeader("data/assets/shaders/plasma.vs", LOAD_SCRATCH, kShaderHeader, kShaderHeaderSize);
    file_binary_t* pPlasmaFs = ldFileBinaryLoadWithHeader("data/assets/shaders/plasma.fs", LOAD_SCRATCH, kShaderHeader, kShaderHeaderSize);
    program = ldGfxCreateProgram(ldFileBinaryGetData(pPlasmaVs), ldFileBinaryGetData(pPlasmaFs));
    vbo = ldGfxCreateVertexBuffer(vertices, sizeof(vertices), GL_STATIC_DRAW);
    glUseProgram(program);
    ldGfxBindVertexBuffer(vbo);
    glBindAttribLocation(program, 0, "inPosition");

    glClearColor(0, 1, 0, 1);
    ldDebugPrint("first pass create\n");
}

void first_pass_update(float32_t delta)
{
    if (ldIsKeyHit(KEY_SPACE))
    {
        ldGameSwapState(&gFirstPassState);
    }
}

void first_pass_render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glUseProgram(program);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    GLuint loc = glGetAttribLocation(program, "inPosition");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 8, NULL);
    glUniform2f(glGetUniformLocation(program, "uRes"), LD_CONFIG_WIDTH, LD_CONFIG_HEIGHT);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void first_pass_destroy()
{
    ldDebugPrint("first pass destroy\n");
}
