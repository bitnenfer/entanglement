
#include <assert.h>
#include <stddef.h>
#include <stdarg.h>

#include "boot.h"
#include "opengl.h"
#include "alloc.h"

#if defined(PLATFORM_WEB)
#include <emscripten/html5.h>
#include <emscripten.h>
#endif


/* Input */
static const char* k_KeyCodeMap[(int32_t)KEY_LENGTH] = {
    "" /* GK_KEY_ABNT_C1 */ ,
    "" /* GK_KEY_ABNT_C2 */ ,
    "" /* GK_KEY_ADD */ ,
    "" /* GK_KEY_ATTN */ ,
    "Backspace" /* GK_KEY_BACK */ ,
    "" /* GK_KEY_CANCEL */ ,
    "" /* GK_KEY_CLEAR */ ,
    "" /* GK_KEY_CRSEL */ ,
    "" /* GK_KEY_DECIMAL */ ,
    "Slash" /* GK_KEY_DIVIDE */ ,
    "" /* GK_KEY_EREOF */ ,
    "Escape" /* GK_KEY_ESCAPE */ ,
    "" /* GK_KEY_EXECUTE */ ,
    "" /* GK_KEY_EXSEL */ ,
    "" /* GK_KEY_ICO_CLEAR */ ,
    "" /* GK_KEY_ICO_HELP */ ,
    "Digit0" /* GK_KEY_KEY_0 */ ,
    "Digit1" /* GK_KEY_KEY_1 */ ,
    "Digit2" /* GK_KEY_KEY_2 */ ,
    "Digit3" /* GK_KEY_KEY_3 */ ,
    "Digit4" /* GK_KEY_KEY_4 */ ,
    "Digit5" /* GK_KEY_KEY_5 */ ,
    "Digit6" /* GK_KEY_KEY_6 */ ,
    "Digit7" /* GK_KEY_KEY_7 */ ,
    "Digit8" /* GK_KEY_KEY_8 */ ,
    "Digit9" /* GK_KEY_KEY_9 */ ,
    "KeyA" /* GK_KEY_KEY_A */ ,
    "KeyB" /* GK_KEY_KEY_B */ ,
    "KeyC" /* GK_KEY_KEY_C */ ,
    "KeyD" /* GK_KEY_KEY_D */ ,
    "KeyE" /* GK_KEY_KEY_E */ ,
    "KeyF" /* GK_KEY_KEY_F */ ,
    "KeyG" /* GK_KEY_KEY_G */ ,
    "KeyH" /* GK_KEY_KEY_H */ ,
    "KeyI" /* GK_KEY_KEY_I */ ,
    "KeyJ" /* GK_KEY_KEY_J */ ,
    "KeyK" /* GK_KEY_KEY_K */ ,
    "KeyL" /* GK_KEY_KEY_L */ ,
    "KeyM" /* GK_KEY_KEY_M */ ,
    "KeyN" /* GK_KEY_KEY_N */ ,
    "KeyO" /* GK_KEY_KEY_O */ ,
    "KeyP" /* GK_KEY_KEY_P */ ,
    "KeyQ" /* GK_KEY_KEY_Q */ ,
    "KeyR" /* GK_KEY_KEY_R */ ,
    "KeyS" /* GK_KEY_KEY_S */ ,
    "KeyT" /* GK_KEY_KEY_T */ ,
    "KeyU" /* GK_KEY_KEY_U */ ,
    "KeyV" /* GK_KEY_KEY_V */ ,
    "KeyW" /* GK_KEY_KEY_W */ ,
    "KeyX" /* GK_KEY_KEY_X */ ,
    "KeyY" /* GK_KEY_KEY_Y */ ,
    "KeyZ" /* GK_KEY_KEY_Z */ ,
    "" /* GK_KEY_MULTIPLY */ ,
    "" /* GK_KEY_NONAME */ ,
    "Numpad0" /* GK_KEY_NUMPAD0 */ ,
    "Numpad1" /* GK_KEY_NUMPAD1 */ ,
    "Numpad2" /* GK_KEY_NUMPAD2 */ ,
    "Numpad3" /* GK_KEY_NUMPAD3 */ ,
    "Numpad4" /* GK_KEY_NUMPAD4 */ ,
    "Numpad5" /* GK_KEY_NUMPAD5 */ ,
    "Numpad6" /* GK_KEY_NUMPAD6 */ ,
    "Numpad7" /* GK_KEY_NUMPAD7 */ ,
    "Numpad8" /* GK_KEY_NUMPAD8 */ ,
    "Numpad9" /* GK_KEY_NUMPAD9 */ ,
    "" /* GK_KEY_OEM_1 */ ,
    "" /* GK_KEY_OEM_102 */ ,
    "" /* GK_KEY_OEM_2 */ ,
    "" /* GK_KEY_OEM_3 */ ,
    "" /* GK_KEY_OEM_4 */ ,
    "" /* GK_KEY_OEM_5 */ ,
    "" /* GK_KEY_OEM_6 */ ,
    "" /* GK_KEY_OEM_7 */ ,
    "" /* GK_KEY_OEM_8 */ ,
    "" /* GK_KEY_OEM_ATTN */ ,
    "" /* GK_KEY_OEM_AUTO */ ,
    "" /* GK_KEY_OEM_AX */ ,
    "" /* GK_KEY_OEM_BACKTAB */ ,
    "" /* GK_KEY_OEM_CLEAR */ ,
    "" /* GK_KEY_OEM_COMMA */ ,
    "" /* GK_KEY_OEM_COPY */ ,
    "" /* GK_KEY_OEM_CUSEL */ ,
    "" /* GK_KEY_OEM_ENLW */ ,
    "" /* GK_KEY_OEM_FINISH */ ,
    "" /* GK_KEY_OEM_FJ_LOYA */ ,
    "" /* GK_KEY_OEM_FJ_MASSHOU */ ,
    "" /* GK_KEY_OEM_FJ_ROYA */ ,
    "" /* GK_KEY_OEM_FJ_TOUROKU */ ,
    "" /* GK_KEY_OEM_JUMP */ ,
    "" /* GK_KEY_OEM_MINUS */ ,
    "" /* GK_KEY_OEM_PA1 */ ,
    "" /* GK_KEY_OEM_PA2 */ ,
    "" /* GK_KEY_OEM_PA3 */ ,
    "" /* GK_KEY_OEM_PERIOD */ ,
    "" /* GK_KEY_OEM_PLUS */ ,
    "" /* GK_KEY_OEM_RESET */ ,
    "" /* GK_KEY_OEM_WSCTRL */ ,
    "" /* GK_KEY_PA1 */ ,
    "" /* GK_KEY_PACKET */ ,
    "" /* GK_KEY_PLAY */ ,
    "" /* GK_KEY_PROCESSKEY */ ,
    "Enter" /* GK_KEY_RETURN */ ,
    "" /* GK_KEY_SELECT */ ,
    "" /* GK_KEY_SEPARATOR */ ,
    "Space" /* GK_KEY_SPACE */ ,
    "Minus" /* GK_KEY_SUBTRACT */ ,
    "Tab" /* GK_KEY_TAB */ ,
    "" /* GK_KEY_ZOOM */ ,
    "" /* GK_KEY__none_ */ ,
    "" /* GK_KEY_ACCEPT */ ,
    "" /* GK_KEY_APPS */ ,
    "" /* GK_KEY_BROWSER_BACK */ ,
    "" /* GK_KEY_BROWSER_FAVORITES */ ,
    "" /* GK_KEY_BROWSER_FORWARD */ ,
    "" /* GK_KEY_BROWSER_HOME */ ,
    "" /* GK_KEY_BROWSER_REFRESH */ ,
    "" /* GK_KEY_BROWSER_SEARCH */ ,
    "" /* GK_KEY_BROWSER_STOP */ ,
    "CapsLock" /* GK_KEY_CAPITAL */ ,
    "" /* GK_KEY_CONVERT */ ,
    "Delete" /* GK_KEY_DELETE */ ,
    "ArrowDown" /* GK_KEY_DOWN */ ,
    "End" /* GK_KEY_END */ ,
    "F1" /* GK_KEY_F1 */ ,
    "F10" /* GK_KEY_F10 */ ,
    "F11" /* GK_KEY_F11 */ ,
    "F12" /* GK_KEY_F12 */ ,
    "F13" /* GK_KEY_F13 */ ,
    "F14" /* GK_KEY_F14 */ ,
    "F15" /* GK_KEY_F15 */ ,
    "F16" /* GK_KEY_F16 */ ,
    "F17" /* GK_KEY_F17 */ ,
    "F18" /* GK_KEY_F18 */ ,
    "F19" /* GK_KEY_F19 */ ,
    "F2" /* GK_KEY_F2 */ ,
    "F20" /* GK_KEY_F20 */ ,
    "F21" /* GK_KEY_F21 */ ,
    "F22" /* GK_KEY_F22 */ ,
    "F23" /* GK_KEY_F23 */ ,
    "F24" /* GK_KEY_F24 */ ,
    "F3" /* GK_KEY_F3 */ ,
    "F4" /* GK_KEY_F4 */ ,
    "F5" /* GK_KEY_F5 */ ,
    "F6" /* GK_KEY_F6 */ ,
    "F7" /* GK_KEY_F7 */ ,
    "F8" /* GK_KEY_F8 */ ,
    "F9" /* GK_KEY_F9 */ ,
    "" /* GK_KEY_FINAL */ ,
    "" /* GK_KEY_HELP */ ,
    "Home" /* GK_KEY_HOME */ ,
    "" /* GK_KEY_ICO_00 */ ,
    "Insert" /* GK_KEY_INSERT */ ,
    "" /* GK_KEY_JUNJA */ ,
    "" /* GK_KEY_KANA */ ,
    "" /* GK_KEY_KANJI */ ,
    "" /* GK_KEY_LAUNCH_APP1 */ ,
    "" /* GK_KEY_LAUNCH_APP2 */ ,
    "" /* GK_KEY_LAUNCH_MAIL */ ,
    "" /* GK_KEY_LAUNCH_MEDIA_SELECT */ ,
    "" /* GK_KEY_LBUTTON */ ,
    "ControlLeft" /* GK_KEY_LCONTROL */ ,
    "ArrowLeft" /* GK_KEY_LEFT */ ,
    "MetaLeft" /* GK_KEY_LMENU */ ,
    "ShiftLeft" /* GK_KEY_LSHIFT */ ,
    "" /* GK_KEY_LWIN */ ,
    "" /* GK_KEY_MBUTTON */ ,
    "" /* GK_KEY_MEDIA_NEXT_TRACK */ ,
    "" /* GK_KEY_MEDIA_PLAY_PAUSE */ ,
    "" /* GK_KEY_MEDIA_PREV_TRACK */ ,
    "" /* GK_KEY_MEDIA_STOP */ ,
    "" /* GK_KEY_MODECHANGE */ ,
    "" /* GK_KEY_NEXT */ ,
    "" /* GK_KEY_NONCONVERT */ ,
    "" /* GK_KEY_NUMLOCK */ ,
    "" /* GK_KEY_OEM_FJ_JISHO */ ,
    "" /* GK_KEY_PAUSE */ ,
    "" /* GK_KEY_PRINT */ ,
    "" /* GK_KEY_PRIOR */ ,
    "" /* GK_KEY_RBUTTON */ ,
    "ControlRight" /* GK_KEY_RCONTROL */ ,
    "ArrowRight" /* GK_KEY_RIGHT */ ,
    "ContextMenu" /* GK_KEY_RMENU */ ,
    "ShiftRight" /* GK_KEY_RSHIFT */ ,
    "" /* GK_KEY_RWIN */ ,
    "" /* GK_KEY_SCROLL */ ,
    "" /* GK_KEY_SLEEP */ ,
    "" /* GK_KEY_SNAPSHOT */ ,
    "ArrowUp" /* GK_KEY_UP */ ,
    "" /* GK_KEY_VOLUME_DOWN */ ,
    "" /* GK_KEY_VOLUME_MUTE */ ,
    "" /* GK_KEY_VOLUME_UP */ ,
    "" /* GK_KEY_XBUTTON1 */ ,
    "" /* GK_KEY_XBUTTON2 */ ,
    "ControlLeft" /* GK_KEY_CONTROL */ ,
    "ShiftLeft" /* GK_KEY_SHIFT */ ,
    "AltLeft" /* GK_KEY_ALT */
};
int32_t gMouseVisible = 1;
char gLastChar = -1;
int32_t gLastCharAvailable = 0;
int32_t gKeyDown[(int32_t)KEY_LENGTH] = { 0 };
int32_t gKeyHit[(int32_t)KEY_LENGTH] = { 0 };
int32_t gMouseX = 0;
int32_t gMouseY = 0;
float32_t gMouseWheel = 0.0f;
int32_t gMouseButtonDown[3] = { 0 };
int32_t gMouseButtonHit[3] = { 0 };

/* Window */
int32_t gWindowExit = 0;
WRITE_EM(EMSCRIPTEN_WEBGL_CONTEXT_HANDLE gOpenGLContext;);

WRITE_EM(static EM_BOOL emscripten_keyboard_input(int event_type, const EmscriptenKeyboardEvent* key_event, void* user_data));
WRITE_EM(static EM_BOOL emscripten_mouse_input(int event_type, const EmscriptenMouseEvent* mouse_event, void* user_data));
WRITE_EM(static EM_BOOL emscripten_mouse_wheel_input(int event_type, const EmscriptenWheelEvent* wheel_event, void* user_data));

void ldGameInit(int argc, const char* p_argv[])
{
    /* Initialize Memory Allocators */
    ldInitMem();

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

#if defined(LD_CONFIG_DEBUG)
                window.outputLog = document.createElement('pre');
                window.outputLog.id = 'gunk_outputlog';
                window.outputLog.style.width = $0 + 'px';
                window.outputLog.style.height = '150px';
                window.outputLog.style.overflow = 'auto';
                window.outputLog.style.backgroundColor = '#000';
                window.outputLog.style.color = '#fff';
                document.body.appendChild(window.outputLog);
#endif
            }, LD_CONFIG_WIDTH, LD_CONFIG_HEIGHT, LD_CONFIG_TITLE);

        gOpenGLContext = emscripten_webgl_create_context(NULL, &attribs);
        assert(emscripten_webgl_make_context_current(gOpenGLContext) == EMSCRIPTEN_RESULT_SUCCESS);

        );

    }

    /* Initialize Input */
    {
        WRITE_EM(
            emscripten_set_keydown_callback("#window", NULL, 0, &emscripten_keyboard_input);
            emscripten_set_keyup_callback("#window", NULL, 0, &emscripten_keyboard_input);
            emscripten_set_mousedown_callback("gunk", NULL, 0, &emscripten_mouse_input);
            emscripten_set_mouseup_callback("gunk", NULL, 0, &emscripten_mouse_input);
            emscripten_set_mousemove_callback("gunk", NULL, 0, &emscripten_mouse_input);
            emscripten_set_click_callback("gunk", NULL, 0, &emscripten_mouse_input);
            emscripten_set_wheel_callback("gunk", NULL, 0, &emscripten_mouse_wheel_input);
        );

    }
}

WRITE_EM(EM_BOOL emscripten_keyboard_input(int event_type, const EmscriptenKeyboardEvent* key_event, void* user_data)
{
    const char* code = key_event->code;
    int32_t backspace = 0;
    switch (event_type)
    {
    case EMSCRIPTEN_EVENT_KEYDOWN:
        if (key_event->key[1] == (char)0 || (backspace = strcmp(key_event->key, "Backspace") == 0))
        {
            gLastCharAvailable = 1;
            if (!backspace)
                gLastChar = (uint8_t)key_event->key[0];
            else
                gLastChar = 8;
        }
        for (uint32_t index = 0; index < KEY_LENGTH; ++index)
        {
            if (strcmp(k_KeyCodeMap[index], code) == 0)
            {
                if (!gKeyDown[index])
                {
                    gKeyHit[index] = 1;
                }
                gKeyDown[index] = 1;
                break;
            }
        }
        break;
    case EMSCRIPTEN_EVENT_KEYUP:
        for (uint32_t index = 0; index < KEY_LENGTH; ++index)
        {
            if (strcmp(k_KeyCodeMap[index], code) == 0)
            {
                gKeyDown[index] = 0;
                gKeyHit[index] = 0;
                break;
            }
        }
        break;
    }
    return 1;
})
WRITE_EM(EM_BOOL emscripten_mouse_input(int event_type, const EmscriptenMouseEvent* mouse_event, void* user_data)
{
    gMouseX = (float32_t)mouse_event->canvasX;
    gMouseY = (float32_t)mouse_event->canvasY;

    switch (event_type)
    {
    case EMSCRIPTEN_EVENT_MOUSEDOWN:
        if (!gMouseButtonDown[mouse_event->button])
        {
            gMouseButtonHit[mouse_event->button] = 1;
        }
        gMouseButtonDown[mouse_event->button] = 1;
        break;
    case EMSCRIPTEN_EVENT_MOUSEUP:
        gMouseButtonDown[mouse_event->button] = 0;
        gMouseButtonHit[mouse_event->button] = 0;
        break;
    }

    return 1;
});
WRITE_EM(EM_BOOL emscripten_mouse_wheel_input(int event_type, const EmscriptenWheelEvent* wheel_event, void* user_data)
{
    gMouseWheel = wheel_event->deltaY < 0 ? +1.0f : -1.0f;
    return 1;
});

void emscripten_loop()
{
    ldGameUpdate(0.16f);
    ldGameRender();

    if (gWindowExit)
    {
        ldShutdownMem();
        WRITE_EM(emscripten_cancel_main_loop(););
    }

    ldPollEvents();
    gLastCharAvailable = 0;
}

void ldGameRun()
{
    ldGameStart();
    WRITE_EM(emscripten_set_main_loop(&emscripten_loop, 0, 1););
}
void ldGameShutdown()
{
}
void ldSwapBuffer()
{
}
void ldPollEvents()
{
    gMouseButtonHit[0] = 0;
    gMouseButtonHit[1] = 0;
    gMouseButtonHit[2] = 0;

    for (int32_t index = 0; index < KEY_LENGTH; ++index)
    {
        gKeyHit[index] = 0;
    }
}
int32_t ldIsKeyDown(enum key_code key)
{
    return gKeyDown[key];
}
int32_t ldIsKeyHit(enum key_code key)
{
    return gKeyHit[key];
}
int32_t ldIsMouseDown(enum mouse_button button)
{
    return gMouseButtonDown[button];
}
int32_t ldIsMouseHit(enum mouse_button button)
{
    return gMouseButtonHit[button];
}

float32_t ldMouseX()
{
    return (float32_t)gMouseX;
}
float32_t ldMouseY()
{
    return (float32_t)gMouseY;
}
float32_t ldMouseWheel()
{
    return gMouseWheel;
}
void ldGameQuit()
{
    gWindowExit = 1;
}
void ldDebugPrint(const char* p_fmt, ...)
{
    va_list args;
    va_start(args, p_fmt);
    vprintf(p_fmt, args);
    va_end(args);
}

void ldExit(int result)
{
    WRITE_EM(emscripten_force_exit(-1));
}
