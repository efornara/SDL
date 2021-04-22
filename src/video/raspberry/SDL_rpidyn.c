/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2021 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/
#include "../../SDL_internal.h"

#if SDL_VIDEO_DRIVER_RPI

#define DEBUG_DYNAMIC_RPI 0

#include "SDL_rpidyn.h"

#if DEBUG_DYNAMIC_RPI
#include <stdio.h>
#endif

#ifdef SDL_VIDEO_DRIVER_RPI_DYNAMIC

#include "SDL_name.h"
#include "SDL_loadso.h"

typedef struct
{
    void *lib;
    const char *libname;
} rpidynlib;

static rpidynlib rpilibs[] = {
    {NULL, SDL_VIDEO_DRIVER_RPI_DYNAMIC}
};

static void *
RPI_GetSym(const char *fnname, int *pHasModule)
{
    int i;
    void *fn = NULL;
    for (i = 0; i < SDL_TABLESIZE(rpilibs); i++) {
        if (rpilibs[i].lib != NULL) {
            fn = SDL_LoadFunction(rpilibs[i].lib, fnname);
            if (fn != NULL)
                break;
        }
    }

#if DEBUG_DYNAMIC_RPI
    if (fn != NULL)
        printf("RPI: Found '%s' in %s (%p)\n", fnname, rpilibs[i].libname, fn);
    else
        printf("RPI: Symbol '%s' NOT FOUND!\n", fnname);
#endif

    if (fn == NULL)
        *pHasModule = 0;  /* kill this module. */

    return fn;
}

#endif /* SDL_VIDEO_DRIVER_RPI_DYNAMIC */

/* Define all the function pointers and wrappers... */
#define SDL_RPI_SYM(rc,fn,params,args,ret) SDL_DYNRPIFN_##fn RPI_##fn = NULL;
#include "SDL_rpisym.h"

/* These SDL_RPI_HAVE_* flags are here whether you have dynamic RPI or not. */
#define SDL_RPI_MODULE(modname) int SDL_RPI_HAVE_##modname = 0;
#include "SDL_rpisym.h"

static int rpi_load_refcount = 0;

void
SDL_RPI_UnloadSymbols(void)
{
    /* Don't actually unload if more than one module is using the libs... */
    if (rpi_load_refcount > 0) {
        if (--rpi_load_refcount == 0) {
            int i;

            /* set all the function pointers to NULL. */
#define SDL_RPI_MODULE(modname) SDL_RPI_HAVE_##modname = 0;
#define SDL_RPI_SYM(rc,fn,params,args,ret) RPI_##fn = NULL;
#include "SDL_rpisym.h"

#ifdef SDL_VIDEO_DRIVER_RPI_DYNAMIC
            for (i = 0; i < SDL_TABLESIZE(rpilibs); i++) {
                if (rpilibs[i].lib != NULL) {
                    SDL_UnloadObject(rpilibs[i].lib);
                    rpilibs[i].lib = NULL;
                }
            }
#endif
        }
    }
}

/* returns non-zero if all needed symbols were loaded. */
int
SDL_RPI_LoadSymbols(void)
{
    int rc = 1;                 /* always succeed if not using Dynamic RPI stuff. */

    /* deal with multiple modules (dga, rpi, etc) needing these symbols... */
    if (rpi_load_refcount++ == 0) {
#ifdef SDL_VIDEO_DRIVER_RPI_DYNAMIC
        int i;
        int *thismod = NULL;
        for (i = 0; i < SDL_TABLESIZE(rpilibs); i++) {
            if (rpilibs[i].libname != NULL) {
                rpilibs[i].lib = SDL_LoadObject(rpilibs[i].libname);
            }
        }

#define SDL_RPI_MODULE(modname) SDL_RPI_HAVE_##modname = 1; /* default yes */
#include "SDL_rpisym.h"

#define SDL_RPI_MODULE(modname) thismod = &SDL_RPI_HAVE_##modname;
#define SDL_RPI_SYM(a,fn,x,y,z) RPI_##fn = (SDL_DYNRPIFN_##fn) RPI_GetSym(#fn,thismod);
#include "SDL_rpisym.h"

        if (SDL_RPI_HAVE_BCM) {
            /* all required symbols loaded. */
            SDL_ClearError();
        } else {
            /* in case something got loaded... */
            SDL_RPI_UnloadSymbols();
            rc = 0;
        }

#else  /* no dynamic RPI */

#define SDL_RPI_MODULE(modname) SDL_RPI_HAVE_##modname = 1; /* default yes */
#define SDL_RPI_SYM(a,fn,x,y,z) RPI_##fn = (SDL_DYNRPIFN_##fn) fn;
#include "SDL_rpisym.h"

#endif
    }

    return rc;
}

#endif /* SDL_VIDEO_DRIVER_RPI */

/* vi: set ts=4 sw=4 expandtab: */
