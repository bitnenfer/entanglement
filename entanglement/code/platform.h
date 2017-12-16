#ifndef _PLATFORM_H_
#define _PLATFORM_H_

#include "config.h"

enum key_code
{   
    KEYCODE_ABNT_C1,
    KEYCODE_ABNT_C2,
    KEYCODE_ADD,
    KEYCODE_ATTN,
    KEYCODE_BACK,
    KEYCODE_CANCEL,
    KEYCODE_CLEAR,
    KEYCODE_CRSEL,
    KEYCODE_DECIMAL,
    KEYCODE_DIVIDE,
    KEYCODE_EREOF,
    KEYCODE_ESCAPE,
    KEYCODE_EXECUTE,
    KEYCODE_EXSEL,
    KEYCODE_ICO_CLEAR,
    KEYCODE_ICO_HELP,
    KEYCODE__0,
    KEYCODE__1,
    KEYCODE__2,
    KEYCODE__3,
    KEYCODE__4,
    KEYCODE__5,
    KEYCODE__6,
    KEYCODE__7,
    KEYCODE__8,
    KEYCODE__9,
    KEYCODE__A,
    KEYCODE__B,
    KEYCODE__C,
    KEYCODE__D,
    KEYCODE__E,
    KEYCODE__F,
    KEYCODE__G,
    KEYCODE__H,
    KEYCODE__I,
    KEYCODE__J,
    KEYCODE__K,
    KEYCODE__L,
    KEYCODE__M,
    KEYCODE__N,
    KEYCODE__O,
    KEYCODE__P,
    KEYCODE__Q,
    KEYCODE__R,
    KEYCODE__S,
    KEYCODE__T,
    KEYCODE__U,
    KEYCODE__V,
    KEYCODE__W,
    KEYCODE__X,
    KEYCODE__Y,
    KEYCODE__Z,
    KEYCODE_MULTIPLY,
    KEYCODE_NONAME,
    KEYCODE_NUMPAD0,
    KEYCODE_NUMPAD1,
    KEYCODE_NUMPAD2,
    KEYCODE_NUMPAD3,
    KEYCODE_NUMPAD4,
    KEYCODE_NUMPAD5,
    KEYCODE_NUMPAD6,
    KEYCODE_NUMPAD7,
    KEYCODE_NUMPAD8,
    KEYCODE_NUMPAD9,
    KEYCODE_OEM_1,
    KEYCODE_OEM_102,
    KEYCODE_OEM_2,
    KEYCODE_OEM_3,
    KEYCODE_OEM_4,
    KEYCODE_OEM_5,
    KEYCODE_OEM_6,
    KEYCODE_OEM_7,
    KEYCODE_OEM_8,
    KEYCODE_OEM_ATTN,
    KEYCODE_OEM_AUTO,
    KEYCODE_OEM_AX,
    KEYCODE_OEM_BACKTAB,
    KEYCODE_OEM_CLEAR,
    KEYCODE_OEM_COMMA,
    KEYCODE_OEM_COPY,
    KEYCODE_OEM_CUSEL,
    KEYCODE_OEM_ENLW,
    KEYCODE_OEM_FINISH,
    KEYCODE_OEM_FJ_LOYA,
    KEYCODE_OEM_FJ_MASSHOU,
    KEYCODE_OEM_FJ_ROYA,
    KEYCODE_OEM_FJ_TOUROKU,
    KEYCODE_OEM_JUMP,
    KEYCODE_OEM_MINUS,
    KEYCODE_OEM_PA1,
    KEYCODE_OEM_PA2,
    KEYCODE_OEM_PA3,
    KEYCODE_OEM_PERIOD,
    KEYCODE_OEM_PLUS,
    KEYCODE_OEM_RESET,
    KEYCODE_OEM_WSCTRL,
    KEYCODE_PA1,
    KEYCODE_PACKET,
    KEYCODE_PLAY,
    KEYCODE_PROCESSKEY,
    KEYCODE_RETURN,
    KEYCODE_SELECT,
    KEYCODE_SEPARATOR,
    KEYCODE_SPACE,
    KEYCODE_SUBTRACT,
    KEYCODE_TAB,
    KEYCODE_ZOOM,
    KEYCODE__none_,
    KEYCODE_ACCEPT,
    KEYCODE_APPS,
    KEYCODE_BROWSER_BACK,
    KEYCODE_BROWSER_FAVORITES,
    KEYCODE_BROWSER_FORWARD,
    KEYCODE_BROWSER_HOME,
    KEYCODE_BROWSER_REFRESH,
    KEYCODE_BROWSER_SEARCH,
    KEYCODE_BROWSER_STOP,
    KEYCODE_CAPITAL,
    KEYCODE_CONVERT,
    KEYCODE_DELETE,
    KEYCODE_DOWN,
    KEYCODE_END,
    KEYCODE_F1,
    KEYCODE_F10,
    KEYCODE_F11,
    KEYCODE_F12,
    KEYCODE_F13,
    KEYCODE_F14,
    KEYCODE_F15,
    KEYCODE_F16,
    KEYCODE_F17,
    KEYCODE_F18,
    KEYCODE_F19,
    KEYCODE_F2,
    KEYCODE_F20,
    KEYCODE_F21,
    KEYCODE_F22,
    KEYCODE_F23,
    KEYCODE_F24,
    KEYCODE_F3,
    KEYCODE_F4,
    KEYCODE_F5,
    KEYCODE_F6,
    KEYCODE_F7,
    KEYCODE_F8,
    KEYCODE_F9,
    KEYCODE_FINAL,
    KEYCODE_HELP,
    KEYCODE_HOME,
    KEYCODE_ICO_00,
    KEYCODE_INSERT,
    KEYCODE_JUNJA,
    KEYCODE_KANA,
    KEYCODE_KANJI,
    KEYCODE_LAUNCH_APP1,
    KEYCODE_LAUNCH_APP2,
    KEYCODE_LAUNCH_MAIL,
    KEYCODE_LAUNCH_MEDIA_SELECT,
    KEYCODE_LBUTTON,
    KEYCODE_LCONTROL,
    KEYCODE_LEFT,
    KEYCODE_LMENU,
    KEYCODE_LSHIFT,
    KEYCODE_LWIN,
    KEYCODE_MBUTTON,
    KEYCODE_MEDIA_NEXT_TRACK,
    KEYCODE_MEDIA_PLAY_PAUSE,
    KEYCODE_MEDIA_PREV_TRACK,
    KEYCODE_MEDIA_STOP,
    KEYCODE_MODECHANGE,
    KEYCODE_NEXT,
    KEYCODE_NONCONVERT,
    KEYCODE_NUMLOCK,
    KEYCODE_OEM_FJ_JISHO,
    KEYCODE_PAUSE,
    KEYCODE_PRINT,
    KEYCODE_PRIOR,
    KEYCODE_RBUTTON,
    KEYCODE_RCONTROL,
    KEYCODE_RIGHT,
    KEYCODE_RMENU,
    KEYCODE_RSHIFT,
    KEYCODE_RWIN,
    KEYCODE_SCROLL,
    KEYCODE_SLEEP,
    KEYCODE_SNAPSHOT,
    KEYCODE_UP,
    KEYCODE_VOLUME_DOWN,
    KEYCODE_VOLUME_MUTE,
    KEYCODE_VOLUME_UP,
    KEYCODE_XBUTTON1,
    KEYCODE_XBUTTON2,
    KEYCODE_CONTROL,
    KEYCODE_SHIFT,
    KEYCODE_ALT,
    /* How many keycodes */
    KEYCODE_LENGTH
};
enum mouse_button
{
    MOUSE_BUTTON_LEFT = 0,
    MOUSE_BUTTON_MIDDLE = 1,
    MOUSE_BUTTON_RIGHT = 2
};

void debug_print(const char* p_fmt, ...);

#if defined(_WIN32)
#define PLATFORM_WINDOWS 1
#define WRITE_EM(...)
#define EM_ASM(x)
#define EM_ASM_ARGS(x, ...)
#define EM_ASM_INT(x, ...) 0
#define EM_ASM_DOUBLE(x, ...) 0.0

#elif defined(__EMSCRIPTEN__)
#define PLATFORM_WEB 1
#define WRITE_EM(...) __VA_ARGS__ 
#endif

#if (defined(UINTPTR_MAX) && UINTPTR_MAX == UINT32_MAX) || (PLATFORM_WEB)
#define PLATFORM_ARCH_X86 1
#elif defined(UINTPTR_MAX) && UINTPTR_MAX == UINT64_MAX
#define PLATFORM_ARCH_X64 1
#else
#error "Invalid Platform Architecture"
#endif

#if defined(_DEBUG) || defined(DEBUG)
#define PLATFORM_DEBUG 1
#else
#define PLATFORM_RELEASE 1
#endif

#if defined(PLATFORM_WINDOWS) || defined(_MSC_VER)
#define FORCEINLINE __forceinline
#define NOINLINE __declspec(noinline)
#define ALIGN(x) __declspec(align(x))
#elif defined(__GNUC__) || defined(PLATFORM_WEB)
#define FORCEINLINE inline __attribute__((always_inline))
#define NOINLINE __attribute__((noinline))
#define ALIGN(x) __attribute__((aligned(x))
#endif

#endif // !_PLATFORM_H_
