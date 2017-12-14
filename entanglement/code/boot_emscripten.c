
#include <emscripten/html5.h>
#include <emscripten.h>
#include <assert.h>
#include <stddef.h>
#include <stdarg.h>

#include "boot.h"
#include "opengl32.h"
#include "alloc.h"

/* Input */
int32_t g_MouseVisible = 1;
char g_LastChar = -1;
int32_t g_KeyDown[(int32_t)KEYCODE_LENGTH] = { 0 };
int32_t g_MouseX = 0;
int32_t g_MouseY = 0;
float32_t g_MouseWheel = 0.0f;
int32_t g_MouseButtonDown[3] = { 0 };

/* Window */
int32_t g_WindowExit = 0;
EMSCRIPTEN_WEBGL_CONTEXT_HANDLE g_OpenGLContext;

void initalize_game(int argc, const char* p_argv[])
{
    /* Initialize Memory Allocators */
    initalize_alloc();

    /* Load Libraries */
    {
       

    }

    /* Initialize Window */
    {
        WRITE_EM
        (
            EmscriptenWebGLContextAttributes attribs;
            emscripten_webgl_init_context_attributes(&attribs);
            attribs.depth = 1;
            attribs.stencil = 1;
            attribs.alpha = 0;
            attribs.antialias = 0;
            attribs.preserveDrawingBuffer = 0;
            attribs.premultipliedAlpha = 0;

            EM_ASM_ARGS({

            var canvas = document.createElement('canvas');
            canvas.width = $0;
            canvas.height = $1;
            canvas.id = 'gunk';
            canvas.oncontextmenu = function(e) { e.preventDefault(); };
            document.title = Module.UTF8ArrayToString(HEAP8, $2);
            Module.canvas = canvas;
            document.body.appendChild(canvas);

#if defined(PLATFORM_DEBUG)
            window.outputLog = document.createElement('pre');
            window.outputLog.style.width = $0 + 'px';
            window.outputLog.style.height = '100px';
            window.outputLog.style.overflow = 'auto';
            window.outputLog.style.backgroundColor = '#000';
            window.outputLog.style.color = '#fff';
            document.body.appendChild(window.outputLog);
#endif
        }, CONFIG_WIDTH, CONFIG_HEIGHT, CONFIG_TITLE);

        g_OpenGLContext = emscripten_webgl_create_context(NULL, &attribs);
        assert(emscripten_webgl_make_context_current(g_OpenGLContext) == EMSCRIPTEN_RESULT_SUCCESS);

        );

    }

    /* Initialize OpenGL */
    {
        

    }
}
void run_game()
{
    start_game();
    //while (!g_WindowExit)
    {
        poll_events();
        update_game(0.16f);
        render_game();
        swap_buffers();
    }
}
void shutdown_game()
{
    shutdown_alloc();
}
void swap_buffers()
{
}
void poll_events()
{
}
int32_t is_key_down(enum KeyCode key)
{
    return g_KeyDown[key];
}
int32_t is_mouse_down(enum MouseButton button)
{
    return g_MouseButtonDown[button];
}
float32_t mouse_x()
{
    return (float32_t)g_MouseX;
}
float32_t mouse_y()
{
    return (float32_t)g_MouseY;
}
float32_t mouse_wheel()
{
    return g_MouseWheel;
}
void quit_game()
{
    g_WindowExit = 1;
}
void debug_print(const char* p_fmt, ...)
{
    va_list args;
    va_start(args, p_fmt);
    vprintf(p_fmt, args);
    va_end(args);
}
