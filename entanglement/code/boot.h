#ifndef _BOOT_H_
#define _BOOT_H_

#include "types.h"
#include "config.h"
#include "platform.h"

static void initalize_game(int argc, const char* p_argv[]);
static void run_game();
static void start_game();
static void update_game(float32_t delta);
static void render_game();
static void shutdown_game();
static void swap_buffers();
static void poll_events();
static int32_t is_key_down(enum KeyCode key);
static int32_t is_mouse_down(enum MouseButton button);
static float32_t mouse_x();
static float32_t mouse_y();
static float32_t mouse_wheel();
static void quit_game();

int main(int argc, const char* p_argv[])
{
    initalize_game(argc, p_argv);
    run_game();
    shutdown_game();
    return 0;
}

#endif // !_BOOT_H_
