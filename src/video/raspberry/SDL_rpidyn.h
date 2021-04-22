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

#ifndef SDL_rpidyn_h_
#define SDL_rpidyn_h_

#include <bcm_host.h>

#ifdef __cplusplus
extern "C"
{
#endif

int SDL_RPI_LoadSymbols(void);
void SDL_RPI_UnloadSymbols(void);

/* Declare all the function pointers and wrappers... */
#define SDL_RPI_SYM(rc,fn,params,args,ret) \
    typedef rc (*SDL_DYNRPIFN_##fn) params; \
    extern SDL_DYNRPIFN_##fn RPI_##fn;
#include "SDL_rpisym.h"

/* These SDL_RPI_HAVE_* flags are here whether you have dynamic RPI or not. */
#define SDL_RPI_MODULE(modname) extern int SDL_RPI_HAVE_##modname;
#include "SDL_rpisym.h"

#ifdef __cplusplus
}
#endif

#endif                          /* !defined SDL_rpidyn_h_ */
/* vi: set ts=4 sw=4 expandtab: */
