#ifndef _BOOT_H_
#define _BOOT_H_

#include "types.h"
#include "config.h"
#include "platform.h"

static void ldGameInit(int argc, const char* p_argv[]);
static void ldGameRun();
static void ldGameStart();
static void ldGameUpdate(float32_t delta);
static void ldGameRender();
static void ldGameShutdown();
static void ldSwapBuffer();
static void ldPollEvents();
static int32_t ldIsKeyDown(enum key_code key);
static int32_t ldIsKeyHit(enum key_code key);
static int32_t ldIsMouseDown(enum mouse_button button);
static int32_t ldIsMouseHit(enum mouse_button button);
static float32_t ldMouseX();
static float32_t ldMouseY();
static float32_t ldMouseWheel();
static void ldGameQuit();

int main(int argc, const char* p_argv[])
{
    ldGameInit(argc, p_argv);
    ldGameRun();
    ldGameShutdown();
    return 0;
}

#endif // !_BOOT_H_
