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

/* *INDENT-OFF* */

#ifndef SDL_RPI_MODULE
#define SDL_RPI_MODULE(modname)
#endif

#ifndef SDL_RPI_SYM
#define SDL_RPI_SYM(rc,fn,params,args,ret)
#endif

SDL_RPI_MODULE(BCM)

SDL_RPI_SYM(void,bcm_host_init,(void),(),return)
SDL_RPI_SYM(int,vc_dispmanx_display_close,(DISPMANX_DISPLAY_HANDLE_T display),(display),return)
SDL_RPI_SYM(DISPMANX_DISPLAY_HANDLE_T,vc_dispmanx_display_open,(uint32_t device),(device),return)
SDL_RPI_SYM(DISPMANX_ELEMENT_HANDLE_T,vc_dispmanx_element_add,(DISPMANX_UPDATE_HANDLE_T update, DISPMANX_DISPLAY_HANDLE_T display, int32_t layer, const VC_RECT_T *dest_rect, DISPMANX_RESOURCE_HANDLE_T src, const VC_RECT_T *src_rect, DISPMANX_PROTECTION_T protection, VC_DISPMANX_ALPHA_T *alpha, DISPMANX_CLAMP_T *clamp, DISPMANX_TRANSFORM_T transform),(update,display,layer,dest_rect,src,src_rect,protection,alpha,clamp,transform),return)
SDL_RPI_SYM(int,vc_dispmanx_element_change_attributes,(DISPMANX_UPDATE_HANDLE_T update, DISPMANX_ELEMENT_HANDLE_T element, uint32_t change_flags, int32_t layer, uint8_t opacity, const VC_RECT_T *dest_rect, const VC_RECT_T *src_rect, DISPMANX_RESOURCE_HANDLE_T mask, DISPMANX_TRANSFORM_T transform),(update,element,change_flags,layer,opacity,dest_rect,src_rect,mask,transform),return)
SDL_RPI_SYM(int,vc_dispmanx_element_remove,(DISPMANX_UPDATE_HANDLE_T update, DISPMANX_ELEMENT_HANDLE_T element),(update,element),return)
SDL_RPI_SYM(int,vc_dispmanx_rect_set,(VC_RECT_T *rect, uint32_t x_offset, uint32_t y_offset, uint32_t width, uint32_t height),(rect,x_offset,y_offset,width,height),return)
SDL_RPI_SYM(DISPMANX_RESOURCE_HANDLE_T,vc_dispmanx_resource_create,(VC_IMAGE_TYPE_T type, uint32_t width, uint32_t height, uint32_t *native_image_handle),(type,width,height,native_image_handle),return)
SDL_RPI_SYM(int,vc_dispmanx_resource_delete,(DISPMANX_RESOURCE_HANDLE_T res),(res),return)
SDL_RPI_SYM(int,vc_dispmanx_resource_write_data,(DISPMANX_RESOURCE_HANDLE_T res, VC_IMAGE_TYPE_T src_type, int src_pitch, void * src_address, const VC_RECT_T * rect),(res,src_type,src_pitch,src_address,rect),return)
SDL_RPI_SYM(DISPMANX_UPDATE_HANDLE_T,vc_dispmanx_update_start,(int32_t priority),(priority),return)
SDL_RPI_SYM(int,vc_dispmanx_update_submit,(DISPMANX_UPDATE_HANDLE_T update, DISPMANX_CALLBACK_FUNC_T cb_func, void *cb_arg),(update,cb_func,cb_arg),return)
SDL_RPI_SYM(int,vc_dispmanx_update_submit_sync,(DISPMANX_UPDATE_HANDLE_T update),(update),return)
SDL_RPI_SYM(int,vc_dispmanx_display_get_info,(DISPMANX_DISPLAY_HANDLE_T display, DISPMANX_MODEINFO_T *pinfo),(display,pinfo),return)
SDL_RPI_SYM(int,vc_dispmanx_vsync_callback,(DISPMANX_DISPLAY_HANDLE_T display, DISPMANX_CALLBACK_FUNC_T cb_func, void *cb_arg),(display,cb_func,cb_arg),return)
SDL_RPI_SYM(int,vc_tv_get_display_state,(TV_DISPLAY_STATE_T *tvstate),(tvstate),return)
SDL_RPI_SYM(int,vc_tv_hdmi_get_property,(HDMI_PROPERTY_PARAM_T *property),(property),return)

#undef SDL_RPI_MODULE
#undef SDL_RPI_SYM

/* *INDENT-ON* */

/* vi: set ts=4 sw=4 expandtab: */
