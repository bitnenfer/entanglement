#include <assert.h>
#include <stddef.h>
#include <stdarg.h>

#include "boot.h"
#include "opengl.h"
#include "alloc.h"
#include <Windows.h>
#include <windowsx.h>

HMODULE gOpenGL32Lib = NULL;
HMODULE gGDILib = NULL;

/* Input */
int32_t gMouseVisible = 1;
char gLastChar = -1;
uint32_t kKeyCodeMap[(int32_t)KEY_LENGTH] = {
    0xC1, 0xC2, 0x6B, 0xF6, 0x08, 0x03, 0x0C, 0xF7, 0x6E, 0x6F, 0xF9, 0x1B, 0x2B, 0xF8, 0xE6, 0xE3,
    0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46,
    0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56,
    0x57, 0x58, 0x59, 0x5A, 0x6A, 0xFC, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69,
    0xBA, 0xE2, 0xBF, 0xC0, 0xDB, 0xDC, 0xDD, 0xDE, 0xDF, 0xF0, 0xF3, 0xE1, 0xF5, 0xFE, 0xBC, 0xF2,
    0xEF, 0xF4, 0xF1, 0x95, 0x93, 0x96, 0x94, 0xEA, 0xBD, 0xEB, 0xEC, 0xED, 0xBE, 0xBB, 0xE9, 0xEE,
    0xFD, 0xE7, 0xFA, 0xE5, 0x0D, 0x29, 0x6C, 0x20, 0x6D, 0x09, 0xFB, 0xFF, 0x1E, 0x5D, 0xA6, 0xAB,
    0xA7, 0xAC, 0xA8, 0xAA, 0xA9, 0x14, 0x1C, 0x2E, 0x28, 0x23, 0x70, 0x79, 0x7A, 0x7B, 0x7C, 0x7D,
    0x7E, 0x7F, 0x80, 0x81, 0x82, 0x71, 0x83, 0x84, 0x85, 0x86, 0x87, 0x72, 0x73, 0x74, 0x75, 0x76,
    0x77, 0x78, 0x18, 0x2F, 0x24, 0xE4, 0x2D, 0x17, 0x15, 0x19, 0xB6, 0xB7, 0xB4, 0xB5, 0x01, 0xA2,
    0x25, 0xA4, 0xA0, 0x5B, 0x04, 0xB0, 0xB3, 0xB1, 0xB2, 0x1F, 0x22, 0x1D, 0x90, 0x92, 0x13, 0x2A,
    0x21, 0x02, 0xA3, 0x27, 0xA5, 0xA1, 0x5C, 0x91, 0x5F, 0x2C, 0x26, 0xAE, 0xAD, 0xAF, 0x05, 0x06,
    0x11, 0x10, 0x12
};
int32_t gKeyDown[(int32_t)KEY_LENGTH] = { 0 };
int32_t gKeyHit[(int32_t)KEY_LENGTH] = { 0 };
int32_t gMouseX = 0;
int32_t gMouseY = 0;
float32_t gMouseWheel = 0.0f;
int32_t gMouseButtonDown[3] = { 0 };
int32_t gMouseButtonHit[3] = { 0 };

/* Window */
HWND gWindowHandle = NULL;
HDC gWindowDeviceContext = NULL;
int gWindowExit = 0;
HGLRC gOpenGLContext = NULL;

/* WGL typedefs */
typedef BOOL(APIENTRY *PFNWGLCOPYCONTEXT)(HGLRC, HGLRC, UINT);
typedef HGLRC(APIENTRY *PFNWGLCREATECONTEXT)(HDC);
typedef HGLRC(APIENTRY *PFNWGLCREATELAYERCONTEXT)(HDC, int);
typedef BOOL(APIENTRY *PFNWGLDELETECONTEXT)(HGLRC);
typedef HGLRC(APIENTRY *PFNWGLGETCURRENTCONTEXT)(VOID);
typedef HDC(APIENTRY *PFNWGLGETCURRENTDC)(VOID);
typedef PROC(APIENTRY *PFNWGLGETPROCADDRESS)(LPCSTR);
typedef BOOL(APIENTRY *PFNWGLMAKECURRENT)(HDC, HGLRC);
typedef BOOL(APIENTRY *PFNWGLSHARELISTS)(HGLRC, HGLRC);
typedef BOOL(APIENTRY *PFNWGLUSEFONTBITMAPSA)(HDC, DWORD, DWORD, DWORD);
typedef BOOL(APIENTRY *PFNWGLUSEFONTBITMAPSW)(HDC, DWORD, DWORD, DWORD);
typedef int     (APIENTRY *PFNWGLGETSWAPINTERVALEXTPROC)(void);
typedef BOOL(APIENTRY *PFNWGLSWAPINTERVALEXTPROC)(int interval);
typedef HGLRC(APIENTRY *PFNWGLCREATECONTEXTATTRIBSARBPROC)(HDC hDC, HGLRC hShareContext, const int *attribList);
typedef int     (APIENTRY *PFNCHOOSEPIXELFORMAT)(HDC hdc, const PIXELFORMATDESCRIPTOR *ppfd);
typedef BOOL(APIENTRY *PFNSETPIXELFORMAT)(HDC hdc, int iPixelFormat, const PIXELFORMATDESCRIPTOR *ppfd);

/* WGL functions */
PFNWGLGETSWAPINTERVALEXTPROC fpWglGetSwapIntervalEXT = NULL;
PFNWGLSWAPINTERVALEXTPROC fpWglSwapIntervalEXT = NULL;
PFNWGLCREATECONTEXT fpWglCreateContext = NULL;
PFNWGLDELETECONTEXT fpWglDeleteContext = NULL;
PFNWGLMAKECURRENT fpWglMakeCurrent = NULL;
PFNWGLGETPROCADDRESS fpWglGetProcAddress = NULL;
PFNWGLCREATECONTEXTATTRIBSARBPROC fpWglCreateContextAttribsARB = NULL;
PFNCHOOSEPIXELFORMAT fpGdiChoosePixelFormat = NULL;
PFNSETPIXELFORMAT fpGdiSetPixelFormat = NULL;

/* GDI */
typedef HGDIOBJ(WINAPI *PFNGETSTOCKOBJECT)(_In_ int i);
typedef BOOL(WINAPI *PFNSWAPBUFFERS)(HDC);
PFNGETSTOCKOBJECT    fpGdiGetStockObject;
PFNSWAPBUFFERS       fpGdiSwapBuffers;

static LRESULT CALLBACK window_process(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        return 0;
    case WM_CLOSE:
        PostQuitMessage(0);
        return 0;
    case WM_DESTROY:
        return 0;
    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_ESCAPE:
            PostQuitMessage(0);
            return 0;
        }
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
}
void* GLCoreGetProcAddress(const char* pFuncName)
{
    void* pProcAddress = fpWglGetProcAddress(pFuncName);
    if (pProcAddress == NULL)
    {
        pProcAddress = GetProcAddress(gOpenGL32Lib, pFuncName);
    }
    if (pProcAddress == NULL)
    {
        ldDebugPrint("Failed to load OpenGL function %s\n", pFuncName);
    }
    return pProcAddress;
}
void ldGameInit(int argc, const char* p_argv[])
{
    /* Initialize Memory Allocators */
    ldInitMem();

    /* Load Libraries */
    {
        gGDILib = LoadLibraryA("Gdi32.dll");
        assert(gGDILib != NULL);

        fpGdiGetStockObject = (PFNGETSTOCKOBJECT)GetProcAddress(gGDILib, "GetStockObject");
        fpGdiSwapBuffers = (PFNSWAPBUFFERS)GetProcAddress(gGDILib, "SwapBuffers");
        fpGdiChoosePixelFormat = (PFNCHOOSEPIXELFORMAT)GetProcAddress(gGDILib, "ChoosePixelFormat");
        fpGdiSetPixelFormat = (PFNSETPIXELFORMAT)GetProcAddress(gGDILib, "SetPixelFormat");

        gOpenGL32Lib = LoadLibrary("opengl32.dll");
        assert(gOpenGL32Lib != NULL);

        fpWglCreateContext = (PFNWGLCREATECONTEXT)GetProcAddress(gOpenGL32Lib, "wglCreateContext");
        fpWglDeleteContext = (PFNWGLDELETECONTEXT)GetProcAddress(gOpenGL32Lib, "wglDeleteContext");
        fpWglMakeCurrent = (PFNWGLMAKECURRENT)GetProcAddress(gOpenGL32Lib, "wglMakeCurrent");
        fpWglGetProcAddress = (PFNWGLGETPROCADDRESS)GetProcAddress(gOpenGL32Lib, "wglGetProcAddress");

    }

    /* Initialize Window */
    {
        WNDCLASS wnd_class;
        HWND wnd_handle;
        HINSTANCE mod_instance;
        DWORD style = WS_VISIBLE | WS_CAPTION | WS_SYSMENU;
        RECT full_screen = { 0, 0, LD_CONFIG_WIDTH, LD_CONFIG_HEIGHT };

        mod_instance = GetModuleHandle(NULL);
        assert(mod_instance != NULL);

        wnd_class.style = CS_OWNDC;
        wnd_class.lpfnWndProc = &window_process;
        wnd_class.cbClsExtra = 0;
        wnd_class.cbWndExtra = 0;
        wnd_class.hInstance = mod_instance;
        wnd_class.hIcon = LoadIcon(NULL, IDI_APPLICATION);
        wnd_class.hCursor = LoadCursor(NULL, IDC_ARROW);
        wnd_class.hbrBackground = (HBRUSH)fpGdiGetStockObject(BLACK_BRUSH);
        wnd_class.lpszMenuName = NULL;
        wnd_class.lpszClassName = "WindowClass0";
        RegisterClass(&wnd_class);
        AdjustWindowRect(&full_screen, style, 0);
        wnd_handle = CreateWindow(
            "WindowClass0", LD_CONFIG_TITLE,
            style,
            CW_USEDEFAULT, CW_USEDEFAULT,
            full_screen.right - full_screen.left, full_screen.bottom - full_screen.top,
            NULL, NULL, mod_instance, NULL
        );

        gWindowHandle = wnd_handle;
        gWindowDeviceContext = GetDC(wnd_handle);
        gWindowExit = 0;
    }

    /* Initialize OpenGL */
    {
        PIXELFORMATDESCRIPTOR pixel_format_desc;
        pixel_format_desc.nSize = sizeof(PIXELFORMATDESCRIPTOR);
        pixel_format_desc.nVersion = 1;
        pixel_format_desc.dwFlags = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER;
        pixel_format_desc.iPixelType = PFD_TYPE_RGBA;
        pixel_format_desc.cColorBits = 24;
        pixel_format_desc.cDepthBits = 16;

        int32_t pixel_format = fpGdiChoosePixelFormat(gWindowDeviceContext, &pixel_format_desc);
        fpGdiSetPixelFormat(gWindowDeviceContext, pixel_format, &pixel_format_desc);
        gOpenGLContext = fpWglCreateContext(gWindowDeviceContext);
        fpWglMakeCurrent(gWindowDeviceContext, gOpenGLContext);
        assert(gOpenGLContext);

        fpWglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)fpWglGetProcAddress("wglCreateContextAttribsARB");

        if (fpWglCreateContextAttribsARB != NULL)
        {
            const int32_t contextAttribList[] = {
                0x2091, 4,
                0x2092, 0,
                0
            };
            HGLRC openglCore = fpWglCreateContextAttribsARB(gWindowDeviceContext, gOpenGLContext, contextAttribList);
            if (!openglCore)
            {
                ldDebugPrint("Failed to create OpenGL Core Context\n");
            }
            else
            {
                ldDebugPrint("Loaded OpenGL Core Context Successfully\n");
                fpWglMakeCurrent(gWindowDeviceContext, openglCore);
                fpWglDeleteContext(gOpenGLContext);
                gOpenGLContext = openglCore;
            }
        }
        else
        {
            ldDebugPrint("Failed to create OpenGL Core Context. wglCreateContextAttribsARB = NULL\n");
        }

        fpWglGetSwapIntervalEXT = (PFNWGLGETSWAPINTERVALEXTPROC)fpWglGetProcAddress("wglGetSwapIntervalEXT");
        fpWglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)fpWglGetProcAddress("wglSwapIntervalEXT");

        /* Load OpenGL Functions */
        gladLoadGLLoader((GLADloadproc)&GLCoreGetProcAddress);
        if (fpWglSwapIntervalEXT) fpWglSwapIntervalEXT(LD_CONFIG_SWAP_INTERVAL);

    }
}
void ldGameRun()
{
    ldGameStart();
    while (!gWindowExit)
    {
        ldPollEvents();
        ldGameUpdate(0.16f);
        ldGameRender();
        ldSwapBuffer();
    }
}
void ldGameShutdown()
{
    CloseWindow(gWindowHandle);
    DestroyWindow(gWindowHandle);
    FreeLibrary(gGDILib);
    FreeLibrary(gOpenGL32Lib);
    ldShutdownMem();
}
void ldSwapBuffer()
{
    fpGdiSwapBuffers(gWindowDeviceContext);
}
void ldPollEvents()
{
    MSG msg;

    gMouseButtonHit[0] = 0;
    gMouseButtonHit[1] = 0;
    gMouseButtonHit[2] = 0;

    for (int32_t index = 0; index < KEY_LENGTH; ++index)
    {
        gKeyHit[index] = 0;
    }

    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        switch (msg.message)
        {
        case WM_UNICHAR:
        case WM_CHAR:
        case WM_SYSCHAR:
        {
            if (msg.message == WM_UNICHAR && msg.wParam == UNICODE_NOCHAR)
            {
                break;
            }
            gLastChar = (char)msg.wParam;
            break;
        }
        case WM_MOUSEMOVE:
        {
            gMouseX = GET_X_LPARAM(msg.lParam);
            gMouseY = GET_Y_LPARAM(msg.lParam);
            break;
        }
        case WM_MOUSEWHEEL:
        {
            gMouseX = GET_X_LPARAM(msg.lParam);
            gMouseY = GET_Y_LPARAM(msg.lParam);
            gMouseWheel = GET_WHEEL_DELTA_WPARAM(msg.wParam) > 0 ? +1.0f : -1.0f;
            break;
        }
        case WM_LBUTTONDOWN:
        {
            gMouseX = GET_X_LPARAM(msg.lParam);
            gMouseY = GET_Y_LPARAM(msg.lParam);
            if (!gMouseButtonDown[MOUSE_BUTTON_LEFT])
            {
                gMouseButtonHit[MOUSE_BUTTON_LEFT] = 1;
            }
            gMouseButtonDown[MOUSE_BUTTON_LEFT] = 1;
            break;
        }
        case WM_RBUTTONDOWN:
        {
            gMouseX = GET_X_LPARAM(msg.lParam);
            gMouseY = GET_Y_LPARAM(msg.lParam);
            if (!gMouseButtonDown[MOUSE_BUTTON_RIGHT])
            {
                gMouseButtonHit[MOUSE_BUTTON_RIGHT] = 1;
            }
            gMouseButtonDown[MOUSE_BUTTON_RIGHT] = 1;
            break;
        }
        case WM_MBUTTONDOWN:
        {
            gMouseX = GET_X_LPARAM(msg.lParam);
            gMouseY = GET_Y_LPARAM(msg.lParam);
            if (!gMouseButtonDown[MOUSE_BUTTON_MIDDLE])
            {
                gMouseButtonHit[MOUSE_BUTTON_MIDDLE] = 1;
            }
            gMouseButtonDown[MOUSE_BUTTON_MIDDLE] = 1;
            break;
        }
        case WM_LBUTTONUP:
        {
            gMouseX = GET_X_LPARAM(msg.lParam);
            gMouseY = GET_Y_LPARAM(msg.lParam);
            gMouseButtonDown[MOUSE_BUTTON_LEFT] = 0;
            gMouseButtonHit[MOUSE_BUTTON_LEFT] = 0;
            break;
        }
        case WM_RBUTTONUP:
        {
            gMouseX = GET_X_LPARAM(msg.lParam);
            gMouseY = GET_Y_LPARAM(msg.lParam);
            gMouseButtonDown[MOUSE_BUTTON_RIGHT] = 0;
            gMouseButtonHit[MOUSE_BUTTON_RIGHT] = 0;
            break;
        }
        case WM_MBUTTONUP:
        {
            gMouseX = GET_X_LPARAM(msg.lParam);
            gMouseY = GET_Y_LPARAM(msg.lParam);
            gMouseButtonDown[MOUSE_BUTTON_MIDDLE] = 0;
            gMouseButtonHit[MOUSE_BUTTON_MIDDLE] = 0;
            break;
        }
        case WM_KEYDOWN:
        {
            for (int32_t index = 0; index < KEY_LENGTH; ++index)
            {
                if (kKeyCodeMap[index] == msg.wParam)
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
        }
        case WM_KEYUP:
        {
            for (int32_t index = 0; index < KEY_LENGTH; ++index)
            {
                if (kKeyCodeMap[index] == msg.wParam)
                {
                    gKeyDown[index] = 0;
                    gKeyHit[index] = 0;
                    break;
                }
            }
            break;
        }
        case WM_QUIT:
            gWindowExit = 1;
            break;
        default:
            DispatchMessage(&msg);
            break;
        }
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
#define BUFFER_SIZE (1024 * 4)
    static char printfBuffer[BUFFER_SIZE] = { 0 };
    int32_t len;
    va_list args;
    va_start(args, p_fmt);
    len = vsprintf_s(printfBuffer, BUFFER_SIZE, p_fmt, args);
    va_end(args);
    OutputDebugStringA(printfBuffer);
#undef BUFFER_SIZE
}

void ldExit(int result)
{
    exit(result);
}
