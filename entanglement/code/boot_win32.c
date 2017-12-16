
__declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
__declspec(dllexport) unsigned long AmdPowerXpressRequestHighPerformance = 0x00000001;

#include <assert.h>
#include <stddef.h>
#include <stdarg.h>

#include "boot.h"
#include "opengl.h"
#include "alloc.h"
#include <Windows.h>
#include <windowsx.h>

HMODULE g_OpenGL32Lib = NULL;
HMODULE g_GDILib = NULL;

/* Input */
int32_t g_MouseVisible = 1;
char g_LastChar = -1;
uint32_t k_KeyCodeMap[(int32_t)KEYCODE_LENGTH] = {
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
int32_t g_KeyDown[(int32_t)KEYCODE_LENGTH] = { 0 };
int32_t g_KeyHit[(int32_t)KEYCODE_LENGTH] = { 0 };
int32_t g_MouseX = 0;
int32_t g_MouseY = 0;
float32_t g_MouseWheel = 0.0f;
int32_t g_MouseButtonDown[3] = { 0 };
int32_t g_MouseButtonHit[3] = { 0 };

/* Window */
HWND g_WindowHandle = NULL;
HDC g_WindowDeviceContext = NULL;
int g_WindowExit = 0;
HGLRC g_OpenGLContext = NULL;

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
PFNWGLGETSWAPINTERVALEXTPROC wgl_GetSwapIntervalEXT = NULL;
PFNWGLSWAPINTERVALEXTPROC wgl_SwapIntervalEXT = NULL;
PFNWGLCREATECONTEXT wgl_CreateContext = NULL;
PFNWGLDELETECONTEXT wgl_DeleteContext = NULL;
PFNWGLMAKECURRENT wgl_MakeCurrent = NULL;
PFNWGLGETPROCADDRESS wgl_GetProcAddress = NULL;
PFNWGLCREATECONTEXTATTRIBSARBPROC wgl_CreateContextAttribsARB = NULL;
PFNCHOOSEPIXELFORMAT gdi_ChoosePixelFormat = NULL;
PFNSETPIXELFORMAT gdi_SetPixelFormat = NULL;

/* GDI */
typedef HGDIOBJ(WINAPI *PFNGETSTOCKOBJECT)(_In_ int i);
typedef BOOL(WINAPI *PFNSWAPBUFFERS)(HDC);
PFNGETSTOCKOBJECT    gdi_GetStockObject;
PFNSWAPBUFFERS       gdi_SwapBuffers;

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
void initalize_game(int argc, const char* p_argv[])
{
    /* Initialize Memory Allocators */
    initalize_alloc();

    /* Load Libraries */
    {
        g_GDILib = LoadLibraryA("Gdi32.dll");
        assert(g_GDILib != NULL);

        gdi_GetStockObject = (PFNGETSTOCKOBJECT)GetProcAddress(g_GDILib, "GetStockObject");
        gdi_SwapBuffers = (PFNSWAPBUFFERS)GetProcAddress(g_GDILib, "SwapBuffers");
        gdi_ChoosePixelFormat = (PFNCHOOSEPIXELFORMAT)GetProcAddress(g_GDILib, "ChoosePixelFormat");
        gdi_SetPixelFormat = (PFNSETPIXELFORMAT)GetProcAddress(g_GDILib, "SetPixelFormat");

        g_OpenGL32Lib = LoadLibrary("opengl32.dll");
        assert(g_OpenGL32Lib != NULL);

        wgl_CreateContext = (PFNWGLCREATECONTEXT)GetProcAddress(g_OpenGL32Lib, "wglCreateContext");
        wgl_DeleteContext = (PFNWGLDELETECONTEXT)GetProcAddress(g_OpenGL32Lib, "wglDeleteContext");
        wgl_MakeCurrent = (PFNWGLMAKECURRENT)GetProcAddress(g_OpenGL32Lib, "wglMakeCurrent");
        wgl_GetProcAddress = (PFNWGLGETPROCADDRESS)GetProcAddress(g_OpenGL32Lib, "wglGetProcAddress");

    }

    /* Initialize Window */
    {
        WNDCLASS wnd_class;
        HWND wnd_handle;
        HINSTANCE mod_instance;
        DWORD style = WS_VISIBLE | WS_CAPTION | WS_SYSMENU;
        RECT full_screen = { 0, 0, CONFIG_WIDTH, CONFIG_HEIGHT };

        mod_instance = GetModuleHandle(NULL);
        assert(mod_instance != NULL);

        wnd_class.style = CS_OWNDC;
        wnd_class.lpfnWndProc = &window_process;
        wnd_class.cbClsExtra = 0;
        wnd_class.cbWndExtra = 0;
        wnd_class.hInstance = mod_instance;
        wnd_class.hIcon = LoadIcon(NULL, IDI_APPLICATION);
        wnd_class.hCursor = LoadCursor(NULL, IDC_ARROW);
        wnd_class.hbrBackground = (HBRUSH)gdi_GetStockObject(BLACK_BRUSH);
        wnd_class.lpszMenuName = NULL;
        wnd_class.lpszClassName = "WindowClass0";
        RegisterClass(&wnd_class);
        AdjustWindowRect(&full_screen, style, 0);
        wnd_handle = CreateWindow(
            "WindowClass0", CONFIG_TITLE,
            style,
            CW_USEDEFAULT, CW_USEDEFAULT,
            full_screen.right - full_screen.left, full_screen.bottom - full_screen.top,
            NULL, NULL, mod_instance, NULL
        );

        g_WindowHandle = wnd_handle;
        g_WindowDeviceContext = GetDC(wnd_handle);
        g_WindowExit = 0;
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

        int32_t pixel_format = gdi_ChoosePixelFormat(g_WindowDeviceContext, &pixel_format_desc);
        gdi_SetPixelFormat(g_WindowDeviceContext, pixel_format, &pixel_format_desc);
        g_OpenGLContext = wgl_CreateContext(g_WindowDeviceContext);
        wgl_MakeCurrent(g_WindowDeviceContext, g_OpenGLContext);
        assert(g_OpenGLContext);

        wgl_GetSwapIntervalEXT = (PFNWGLGETSWAPINTERVALEXTPROC)wgl_GetProcAddress("wglGetSwapIntervalEXT");
        wgl_SwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wgl_GetProcAddress("wglSwapIntervalEXT");

        /* Load OpenGL Functions */
        glGetError = (PFNGLGETERROR)GetProcAddress(g_OpenGL32Lib, "glGetError");
        glViewport = (PFNGLVIEWPORTPROC)GetProcAddress(g_OpenGL32Lib, "glViewport");
        glEnable = (PFNGLENABLEPROC)GetProcAddress(g_OpenGL32Lib, "glEnable");
        glBlendFunc = (PFNGLBLENDFUNCPROC)GetProcAddress(g_OpenGL32Lib, "glBlendFunc");
        glClear = (PFNGLCLEARPROC)GetProcAddress(g_OpenGL32Lib, "glClear");
        glClearColor = (PFNGLCLEARCOLORPROC)GetProcAddress(g_OpenGL32Lib, "glClearColor");
        glCullFace = (PFNGLCULLFACEPROC)GetProcAddress(g_OpenGL32Lib, "glCullFace");
        glDeleteTextures = (PFNGLDELETETEXTURESPROC)GetProcAddress(g_OpenGL32Lib, "glDeleteTextures");
        glDepthFunc = (PFNGLDEPTHFUNCPROC)GetProcAddress(g_OpenGL32Lib, "glDepthFunc");
        glDepthMask = (PFNGLDEPTHMASKPROC)GetProcAddress(g_OpenGL32Lib, "glDepthMask");
        glDepthRange = (PFNGLDEPTHRANGEPROC)GetProcAddress(g_OpenGL32Lib, "glDepthRange");
        glDisable = (PFNGLDISABLEPROC)GetProcAddress(g_OpenGL32Lib, "glDisable");
        glDrawArrays = (PFNGLDRAWARRAYS)GetProcAddress(g_OpenGL32Lib, "glDrawArrays");
        glDrawElements = (PFNGLDRAWELEMENTS)GetProcAddress(g_OpenGL32Lib, "glDrawElements");
        glGenTextures = (PFNGLGENTEXTURES)GetProcAddress(g_OpenGL32Lib, "glGenTextures");
        glTexEnvf = (PFNGLTEXENVFPROC)GetProcAddress(g_OpenGL32Lib, "glTexEnvf");
        glTexEnvfv = (PFNGLTEXENVFVPROC)GetProcAddress(g_OpenGL32Lib, "glTexEnvfv");
        glTexEnvi = (PFNGLTEXENVIPROC)GetProcAddress(g_OpenGL32Lib, "glTexEnvi");
        glTexEnviv = (PFNGLTEXENVIVPROC)GetProcAddress(g_OpenGL32Lib, "glTexEnviv");
        glTexGend = (PFNGLTEXGENDPROC)GetProcAddress(g_OpenGL32Lib, "glTexGend");
        glTexGendv = (PFNGLTEXGENDVPROC)GetProcAddress(g_OpenGL32Lib, "glTexGendv");
        glTexGenf = (PFNGLTEXGENFPROC)GetProcAddress(g_OpenGL32Lib, "glTexGenf");
        glTexGenfv = (PFNGLTEXGENFVPROC)GetProcAddress(g_OpenGL32Lib, "glTexGenfv");
        glTexGeni = (PFNGLTEXGENIPROC)GetProcAddress(g_OpenGL32Lib, "glTexGeni");
        glTexGeniv = (PFNGLTEXGENIVPROC)GetProcAddress(g_OpenGL32Lib, "glTexGeniv");
        glTexImage1D = (PFNGLTEXIMAGE1DPROC)GetProcAddress(g_OpenGL32Lib, "glTexImage1D");
        glTexImage2D = (PFNGLTEXIMAGE2DPROC)GetProcAddress(g_OpenGL32Lib, "glTexImage2D");
        glTexParameterf = (PFNGLTEXPARAMETERFPROC)GetProcAddress(g_OpenGL32Lib, "glTexParameterf");
        glTexParameterfv = (PFNGLTEXPARAMETERFVPROC)GetProcAddress(g_OpenGL32Lib, "glTexParameterfv");
        glTexParameteri = (PFNGLTEXPARAMETERIPROC)GetProcAddress(g_OpenGL32Lib, "glTexParameteri");
        glTexParameteriv = (PFNGLTEXPARAMETERIVPROC)GetProcAddress(g_OpenGL32Lib, "glTexParameteriv");
        glTexSubImage1D = (PFNGLTEXSUBIMAGE1DPROC)GetProcAddress(g_OpenGL32Lib, "glTexSubImage1D");
        glTexSubImage2D = (PFNGLTEXSUBIMAGE2DPROC)GetProcAddress(g_OpenGL32Lib, "glTexSubImage2D");
        glScissor = (PFNGLSCISSORPROC)GetProcAddress(g_OpenGL32Lib, "glScissor");
        glSelectBuffer = (PFNGLSELECTBUFFERPROC)GetProcAddress(g_OpenGL32Lib, "glSelectBuffer");
        glStencilFunc = (PFNGLSTENCILFUNCPROC)GetProcAddress(g_OpenGL32Lib, "glStencilFunc");
        glStencilMask = (PFNGLSTENCILMASKPROC)GetProcAddress(g_OpenGL32Lib, "glStencilMask");
        glStencilOp = (PFNGLSTENCILOPPROC)GetProcAddress(g_OpenGL32Lib, "glStencilOp");
        glClearDepth = (PFNGLCLEARDEPTHPROC)GetProcAddress(g_OpenGL32Lib, "glClearDepth");
        glClearStencil = (PFNGLCLEARSTENCILPROC)GetProcAddress(g_OpenGL32Lib, "glClearStencil");
        glBindTexture = (PFNGLBINDTEXTUREPROC)GetProcAddress(g_OpenGL32Lib, "glBindTexture");
        glLogicOp = (PFNGLLOGICOP)GetProcAddress(g_OpenGL32Lib, "glLogicOp");

        glCreateShader = (PFNGLCREATESHADERPROC)wgl_GetProcAddress("glCreateShader");
        glShaderSource = (PFNGLSHADERSOURCEPROC)wgl_GetProcAddress("glShaderSource");
        glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC)wgl_GetProcAddress("glBindAttribLocation");
        glCompileShader = (PFNGLCOMPILESHADERPROC)wgl_GetProcAddress("glCompileShader");
        glGetShaderiv = (PFNGLGETSHADERIVPROC)wgl_GetProcAddress("glGetShaderiv");
        glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)wgl_GetProcAddress("glGetShaderInfoLog");
        glCreateProgram = (PFNGLCREATEPROGRAMPROC)wgl_GetProcAddress("glCreateProgram");
        glAttachShader = (PFNGLATTACHSHADERPROC)wgl_GetProcAddress("glAttachShader");
        glLinkProgram = (PFNGLLINKPROGRAMPROC)wgl_GetProcAddress("glLinkProgram");
        glGetProgramiv = (PFNGLGETPROGRAMIVNVPROC)wgl_GetProcAddress("glGetProgramiv");
        glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)wgl_GetProcAddress("glGetProgramInfoLog");
        glUseProgram = (PFNGLUSEPROGRAMPROC)wgl_GetProcAddress("glUseProgram");
        glDeleteProgram = (PFNGLDELETEPROGRAMPROC)wgl_GetProcAddress("glDeleteProgram");
        glDeleteShader = (PFNGLDELETESHADERPROC)wgl_GetProcAddress("glDeleteShader");
        glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC)wgl_GetProcAddress("glGetAttribLocation");
        glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)wgl_GetProcAddress("glGetUniformLocation");
        glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)wgl_GetProcAddress("glEnableVertexAttribArray");
        glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)wgl_GetProcAddress("glVertexAttribPointer");
        glUniform1f = (PFNGLUNIFORM1FPROC)wgl_GetProcAddress("glUniform1f");
        glUniform1fv = (PFNGLUNIFORM1FVPROC)wgl_GetProcAddress("glUniform1fv");
        glUniform1i = (PFNGLUNIFORM1IPROC)wgl_GetProcAddress("glUniform1i");
        glUniform1iv = (PFNGLUNIFORM1IVPROC)wgl_GetProcAddress("glUniform1iv");
        glUniform2f = (PFNGLUNIFORM2FPROC)wgl_GetProcAddress("glUniform2f");
        glUniform2fv = (PFNGLUNIFORM2FVPROC)wgl_GetProcAddress("glUniform2fv");
        glUniform2i = (PFNGLUNIFORM2IPROC)wgl_GetProcAddress("glUniform2i");
        glUniform2iv = (PFNGLUNIFORM2IVPROC)wgl_GetProcAddress("glUniform2iv");
        glUniform3f = (PFNGLUNIFORM3FPROC)wgl_GetProcAddress("glUniform3f");
        glUniform3fv = (PFNGLUNIFORM3FVPROC)wgl_GetProcAddress("glUniform3fv");
        glUniform3i = (PFNGLUNIFORM3IPROC)wgl_GetProcAddress("glUniform3i");
        glUniform3iv = (PFNGLUNIFORM3IVPROC)wgl_GetProcAddress("glUniform3iv");
        glUniform4f = (PFNGLUNIFORM4FPROC)wgl_GetProcAddress("glUniform4f");
        glUniform4fv = (PFNGLUNIFORM4FVPROC)wgl_GetProcAddress("glUniform4fv");
        glUniform4i = (PFNGLUNIFORM4IPROC)wgl_GetProcAddress("glUniform4i");
        glUniform4iv = (PFNGLUNIFORM4IVPROC)wgl_GetProcAddress("glUniform4iv");
        glUniformMatrix2fv = (PFNGLUNIFORMMATRIX2FVPROC)wgl_GetProcAddress("glUniformMatrix2fv");
        glUniformMatrix3fv = (PFNGLUNIFORMMATRIX3FVPROC)wgl_GetProcAddress("glUniformMatrix3fv");
        glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)wgl_GetProcAddress("glUniformMatrix4fv");
        glValidateProgram = (PFNGLVALIDATEPROGRAMPROC)wgl_GetProcAddress("glValidateProgram");
        glIsProgram = (PFNGLISPROGRAMPROC)wgl_GetProcAddress("glIsProgram");
        glIsShader = (PFNGLISSHADERPROC)wgl_GetProcAddress("glIsShader");
        glActiveTexture = (PFNGLACTIVETEXTUREPROC)wgl_GetProcAddress("glActiveTexture");
        glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC)wgl_GetProcAddress("glGenFramebuffers");
        glGenRenderbuffers = (PFNGLGENRENDERBUFFERSPROC)wgl_GetProcAddress("glGenRenderbuffers");
        glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC)wgl_GetProcAddress("glBindFramebuffer");
        glBindRenderbuffer = (PFNGLBINDRENDERBUFFERPROC)wgl_GetProcAddress("glBindRenderbuffer");
        glFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC)wgl_GetProcAddress("glFramebufferTexture2D");
        glDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC)wgl_GetProcAddress("glDeleteFramebuffers");
        glDeleteRenderbuffers = (PFNGLDELETERENDERBUFFERSPROC)wgl_GetProcAddress("glDeleteRenderbuffers");
        glGenBuffers = (PFNGLGENBUFFERSPROC)wgl_GetProcAddress("glGenBuffers");
        glBindBuffer = (PFNGLBINDBUFFERPROC)wgl_GetProcAddress("glBindBuffer");
        glBufferData = (PFNGLBUFFERDATAPROC)wgl_GetProcAddress("glBufferData");
        glBufferSubData = (PFNGLBUFFERSUBDATAPROC)wgl_GetProcAddress("glBufferSubData");
        glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)wgl_GetProcAddress("glDeleteBuffers");
        glDrawElementsBaseVertex = (PFNGLDRAWELEMENTSBASEVERTEXPROC)wgl_GetProcAddress("glDrawElementsBaseVertex");
        glBlendFuncSeparate = (PFNGLBLENDFUNCSEPARATEPROC)wgl_GetProcAddress("glBlendFuncSeparate");
        glBlendEquationSeparate = (PFNGLBLENDEQUATIONSEPARATEPROC)wgl_GetProcAddress("glBlendEquationSeparate");
        glGetUniformBlockIndex = (PFNGLGETUNIFORMBLOCKINDEXPROC)wgl_GetProcAddress("glGetUniformBlockIndex");
        glBindBufferBase = (PFNGLBINDBUFFERBASEPROC)wgl_GetProcAddress("glBindBufferBase");
        glUniformBlockBinding = (PFNGLUNIFORMBLOCKBINDINGPROC)wgl_GetProcAddress("glUniformBlockBinding");
        glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)wgl_GetProcAddress("glGenVertexArrays");
        glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)wgl_GetProcAddress("glDeleteVertexArrays");
        glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)wgl_GetProcAddress("glBindVertexArray");

        if (wgl_SwapIntervalEXT) wgl_SwapIntervalEXT(CONFIG_SWAP_INTERVAL);

    }
}
void run_game()
{
    start_game();
    while (!g_WindowExit)
    {
        poll_events();
        update_game(0.16f);
        render_game();
        swap_buffers();
    }
}
void shutdown_game()
{
    CloseWindow(g_WindowHandle);
    DestroyWindow(g_WindowHandle);
    FreeLibrary(g_GDILib);
    FreeLibrary(g_OpenGL32Lib);
    shutdown_alloc();
}
void swap_buffers()
{
    gdi_SwapBuffers(g_WindowDeviceContext);
}
void poll_events()
{
    MSG msg;

    g_MouseButtonHit[0] = 0;
    g_MouseButtonHit[1] = 0;
    g_MouseButtonHit[2] = 0;

    for (int32_t index = 0; index < KEYCODE_LENGTH; ++index)
    {
        g_KeyHit[index] = 0;
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
            g_LastChar = (char)msg.wParam;
            break;
        }
        case WM_MOUSEMOVE:
        {
            g_MouseX = GET_X_LPARAM(msg.lParam);
            g_MouseY = GET_Y_LPARAM(msg.lParam);
            break;
        }
        case WM_MOUSEWHEEL:
        {
            g_MouseX = GET_X_LPARAM(msg.lParam);
            g_MouseY = GET_Y_LPARAM(msg.lParam);
            g_MouseWheel = GET_WHEEL_DELTA_WPARAM(msg.wParam) > 0 ? +1.0f : -1.0f;
            break;
        }
        case WM_LBUTTONDOWN:
        {
            g_MouseX = GET_X_LPARAM(msg.lParam);
            g_MouseY = GET_Y_LPARAM(msg.lParam);
            if (!g_MouseButtonDown[MOUSE_BUTTON_LEFT])
            {
                g_MouseButtonHit[MOUSE_BUTTON_LEFT] = 1;
            }
            g_MouseButtonDown[MOUSE_BUTTON_LEFT] = 1;
            break;
        }
        case WM_RBUTTONDOWN:
        {
            g_MouseX = GET_X_LPARAM(msg.lParam);
            g_MouseY = GET_Y_LPARAM(msg.lParam);
            if (!g_MouseButtonDown[MOUSE_BUTTON_RIGHT])
            {
                g_MouseButtonHit[MOUSE_BUTTON_RIGHT] = 1;
            }
            g_MouseButtonDown[MOUSE_BUTTON_RIGHT] = 1;
            break;
        }
        case WM_MBUTTONDOWN:
        {
            g_MouseX = GET_X_LPARAM(msg.lParam);
            g_MouseY = GET_Y_LPARAM(msg.lParam);
            if (!g_MouseButtonDown[MOUSE_BUTTON_MIDDLE])
            {
                g_MouseButtonHit[MOUSE_BUTTON_MIDDLE] = 1;
            }
            g_MouseButtonDown[MOUSE_BUTTON_MIDDLE] = 1;
            break;
        }
        case WM_LBUTTONUP:
        {
            g_MouseX = GET_X_LPARAM(msg.lParam);
            g_MouseY = GET_Y_LPARAM(msg.lParam);
            g_MouseButtonDown[MOUSE_BUTTON_LEFT] = 0;
            g_MouseButtonHit[MOUSE_BUTTON_LEFT] = 0;
            break;
        }
        case WM_RBUTTONUP:
        {
            g_MouseX = GET_X_LPARAM(msg.lParam);
            g_MouseY = GET_Y_LPARAM(msg.lParam);
            g_MouseButtonDown[MOUSE_BUTTON_RIGHT] = 0;
            g_MouseButtonHit[MOUSE_BUTTON_RIGHT] = 0;
            break;
        }
        case WM_MBUTTONUP:
        {
            g_MouseX = GET_X_LPARAM(msg.lParam);
            g_MouseY = GET_Y_LPARAM(msg.lParam);
            g_MouseButtonDown[MOUSE_BUTTON_MIDDLE] = 0;
            g_MouseButtonHit[MOUSE_BUTTON_MIDDLE] = 0;
            break;
        }
        case WM_KEYDOWN:
        {
            for (int32_t index = 0; index < KEYCODE_LENGTH; ++index)
            {
                if (k_KeyCodeMap[index] == msg.wParam)
                {
                    if (!g_KeyDown[index])
                    {
                        g_KeyHit[index] = 1;
                    }
                    g_KeyDown[index] = 1;
                    break;
                }
            }
            break;
        }
        case WM_KEYUP:
        {
            for (int32_t index = 0; index < KEYCODE_LENGTH; ++index)
            {
                if (k_KeyCodeMap[index] == msg.wParam)
                {
                    g_KeyDown[index] = 0;
                    g_KeyHit[index] = 0;
                    break;
                }
            }
            break;
        }
        case WM_QUIT:
            g_WindowExit = 1;
            break;
        default:
            DispatchMessage(&msg);
            break;
        }
    }
}
int32_t is_key_down(enum key_code key)
{
    return g_KeyDown[key];
}
int32_t is_key_hit(enum key_code key)
{
    return g_KeyHit[key];
}
int32_t is_mouse_down(enum mouse_button button)
{
    return g_MouseButtonDown[button];
}
int32_t is_mouse_hit(enum mouse_button button)
{
    return g_MouseButtonHit[button];
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
    static char printf_buffer[1024] = { 0 };
    int32_t len;
    va_list args;
    va_start(args, p_fmt);
    len = vsprintf_s(printf_buffer, 1024, p_fmt, args);
    va_end(args);
    OutputDebugStringA(printf_buffer);
}
