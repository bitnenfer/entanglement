/* =============================================== */
/* ===== ORDER MATTERS. DON'T MESS WITH THIS ===== */
/* =============================================== */

#include "config.h"

/* ======================== */
/* Common Compilation Units */
/* ======================== */

#include "game.c"
#include "alloc.c"

/* ======================== */

/* =================================== */
/* Platform Specific Compilation Units */
/* =================================== */
#if defined(PLATFORM_WINDOWS)

/* =================================== */
/* Windows Platform                    */
/* =================================== */

#include "boot_win32.c"
#include "alloc_win32.c"

/* =================================== */
#elif defined(PLATFORM_WEB)

/* =================================== */
/* Web Platform                        */
/* =================================== */

#include "boot_emscripten.c"
#include "alloc_emscripten.c"

/* =================================== */
#endif
/* =================================== */

