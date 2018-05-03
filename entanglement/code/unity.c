#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

/* =============================================== */
/* ===== ORDER MATTERS. DON'T MESS WITH THIS ===== */
/* =============================================== */

#include "config.h"

/* ======================== */
/* Common Compilation Units */
/* ======================== */

#include "loader.c"
#include "alloc.c"
#include "game.c"

/* Passes */
#include "game/init_scene.c"

/* ======================== */

/* =================================== */
/* Platform Specific Compilation Units */
/* =================================== */
#if defined(LD_PLATFORM_WINDOWS)

// Force Dedicated GPU usage
__declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
__declspec(dllexport) unsigned long AmdPowerXpressRequestHighPerformance = 0x00000001;

/* =================================== */
/* Windows Platform                    */
/* =================================== */

#include "thirdparty/glad/glad.c"
#include "boot_win32.c"
#include "alloc_win32.c"
#include "canvas_gl.c"

/* =================================== */
#elif defined(LD_PLATFORM_WEB)

/* =================================== */
/* Web Platform                        */
/* =================================== */

#include "boot_emscripten.c"
#include "alloc_emscripten.c"
#include "canvas_gl.c"

/* =================================== */
#elif defined(LD_PLATFORM_OSX)
/* =================================== */
/* OSX (Apple) Platform                */
/* =================================== */


#else
/* =================================== */
/* NULL Platform                       */
/* =================================== */

#include "boot_null.c"
#include "alloc_null.c"
#include "canvas_null.c"

/* =================================== */
#endif
/* =================================== */

#include "canvas.c"


