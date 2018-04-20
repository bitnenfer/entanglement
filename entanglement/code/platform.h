#ifndef _PLATFORM_H_
#define _PLATFORM_H_

#include "config.h"

enum key_code
{   
    KEY_ABNT_C1,
    KEY_ABNT_C2,
    KEY_ADD,
    KEY_ATTN,
    KEY_BACK,
    KEY_CANCEL,
    KEY_CLEAR,
    KEY_CRSEL,
    KEY_DECIMAL,
    KEY_DIVIDE,
    KEY_EREOF,
    KEY_ESCAPE,
    KEY_EXECUTE,
    KEY_EXSEL,
    KEY_ICO_CLEAR,
    KEY_ICO_HELP,
    KEY_0,
    KEY_1,
    KEY_2,
    KEY_3,
    KEY_4,
    KEY_5,
    KEY_6,
    KEY_7,
    KEY_8,
    KEY_9,
    KEY_A,
    KEY_B,
    KEY_C,
    KEY_D,
    KEY_E,
    KEY_F,
    KEY_G,
    KEY_H,
    KEY_I,
    KEY_J,
    KEY_K,
    KEY_L,
    KEY_M,
    KEY_N,
    KEY_O,
    KEY_P,
    KEY_Q,
    KEY_R,
    KEY_S,
    KEY_T,
    KEY_U,
    KEY_V,
    KEY_W,
    KEY_X,
    KEY_Y,
    KEY_Z,
    KEY_MULTIPLY,
    KEY_NONAME,
    KEY_NUMPAD0,
    KEY_NUMPAD1,
    KEY_NUMPAD2,
    KEY_NUMPAD3,
    KEY_NUMPAD4,
    KEY_NUMPAD5,
    KEY_NUMPAD6,
    KEY_NUMPAD7,
    KEY_NUMPAD8,
    KEY_NUMPAD9,
    KEY_OEM_1,
    KEY_OEM_102,
    KEY_OEM_2,
    KEY_OEM_3,
    KEY_OEM_4,
    KEY_OEM_5,
    KEY_OEM_6,
    KEY_OEM_7,
    KEY_OEM_8,
    KEY_OEM_ATTN,
    KEY_OEM_AUTO,
    KEY_OEM_AX,
    KEY_OEM_BACKTAB,
    KEY_OEM_CLEAR,
    KEY_OEM_COMMA,
    KEY_OEM_COPY,
    KEY_OEM_CUSEL,
    KEY_OEM_ENLW,
    KEY_OEM_FINISH,
    KEY_OEM_FJ_LOYA,
    KEY_OEM_FJ_MASSHOU,
    KEY_OEM_FJ_ROYA,
    KEY_OEM_FJ_TOUROKU,
    KEY_OEM_JUMP,
    KEY_OEM_MINUS,
    KEY_OEM_PA1,
    KEY_OEM_PA2,
    KEY_OEM_PA3,
    KEY_OEM_PERIOD,
    KEY_OEM_PLUS,
    KEY_OEM_RESET,
    KEY_OEM_WSCTRL,
    KEY_PA1,
    KEY_PACKET,
    KEY_PLAY,
    KEY_PROCESSKEY,
    KEY_RETURN,
    KEY_SELECT,
    KEY_SEPARATOR,
    KEY_SPACE,
    KEY_SUBTRACT,
    KEY_TAB,
    KEY_ZOOM,
    KEY_none_,
    KEY_ACCEPT,
    KEY_APPS,
    KEY_BROWSER_BACK,
    KEY_BROWSER_FAVORITES,
    KEY_BROWSER_FORWARD,
    KEY_BROWSER_HOME,
    KEY_BROWSER_REFRESH,
    KEY_BROWSER_SEARCH,
    KEY_BROWSER_STOP,
    KEY_CAPITAL,
    KEY_CONVERT,
    KEY_DELETE,
    KEY_DOWN,
    KEY_END,
    KEY_F1,
    KEY_F10,
    KEY_F11,
    KEY_F12,
    KEY_F13,
    KEY_F14,
    KEY_F15,
    KEY_F16,
    KEY_F17,
    KEY_F18,
    KEY_F19,
    KEY_F2,
    KEY_F20,
    KEY_F21,
    KEY_F22,
    KEY_F23,
    KEY_F24,
    KEY_F3,
    KEY_F4,
    KEY_F5,
    KEY_F6,
    KEY_F7,
    KEY_F8,
    KEY_F9,
    KEY_FINAL,
    KEY_HELP,
    KEY_HOME,
    KEY_ICO_00,
    KEY_INSERT,
    KEY_JUNJA,
    KEY_KANA,
    KEY_KANJI,
    KEY_LAUNCH_APP1,
    KEY_LAUNCH_APP2,
    KEY_LAUNCH_MAIL,
    KEY_LAUNCH_MEDIA_SELECT,
    KEY_LBUTTON,
    KEY_LCONTROL,
    KEY_LEFT,
    KEY_LMENU,
    KEY_LSHIFT,
    KEY_LWIN,
    KEY_MBUTTON,
    KEY_MEDIA_NEXT_TRACK,
    KEY_MEDIA_PLAY_PAUSE,
    KEY_MEDIA_PREV_TRACK,
    KEY_MEDIA_STOP,
    KEY_MODECHANGE,
    KEY_NEXT,
    KEY_NONCONVERT,
    KEY_NUMLOCK,
    KEY_OEM_FJ_JISHO,
    KEY_PAUSE,
    KEY_PRINT,
    KEY_PRIOR,
    KEY_RBUTTON,
    KEY_RCONTROL,
    KEY_RIGHT,
    KEY_RMENU,
    KEY_RSHIFT,
    KEY_RWIN,
    KEY_SCROLL,
    KEY_SLEEP,
    KEY_SNAPSHOT,
    KEY_UP,
    KEY_VOLUME_DOWN,
    KEY_VOLUME_MUTE,
    KEY_VOLUME_UP,
    KEY_XBUTTON1,
    KEY_XBUTTON2,
    KEY_CONTROL,
    KEY_SHIFT,
    KEY_ALT,
    /* How many keycodes */
    KEY_LENGTH
};
enum mouse_button
{
    MOUSE_BUTTON_LEFT = 0,
    MOUSE_BUTTON_MIDDLE = 1,
    MOUSE_BUTTON_RIGHT = 2
};

void ldDebugPrint(const char* p_fmt, ...);
void ldExit(int result);

#if defined(_WIN32)
#define LD_PLATFORM_WINDOWS 1
#define WRITE_EM(...)
#define EM_ASM(x)
#define EM_ASM_ARGS(x, ...)
#define EM_ASM_INT(x, ...) 0
#define EM_ASM_DOUBLE(x, ...) 0.0

#elif defined(__EMSCRIPTEN__)
#define LD_PLATFORM_WEB 1
#define WRITE_EM(...) __VA_ARGS__ 
#endif

#if (defined(UINTPTR_MAX) && UINTPTR_MAX == UINT32_MAX) || (LD_PLATFORM_WEB)
#define LD_PLATFORM_ARCH_X86 1
#elif defined(UINTPTR_MAX) && UINTPTR_MAX == UINT64_MAX
#define LD_PLATFORM_ARCH_X64 1
#else
#error "Invalid Platform Architecture"
#endif

#if defined(_DEBUG) || defined(DEBUG)
#define LD_PLATFORM_DEBUG 1
#else
#define LD_PLATFORM_RELEASE 1
#endif

#if defined(LD_PLATFORM_WINDOWS) || defined(_MSC_VER)
#define LD_FORCEINLINE __forceinline
#define LD_NOINLINE __declspec(LD_NOINLINE)
#define LD_ALIGN(x) __declspec(LD_ALIGN(x))
#elif defined(__GNUC__) || defined(LD_PLATFORM_WEB)
#define LD_FORCEINLINE inline __attribute__((always_inline))
#define LD_NOINLINE __attribute__((LD_NOINLINE))
#define LD_ALIGN(x) __attribute__((LD_ALIGNed(x))
#endif

#endif // !_PLATFORM_H_
