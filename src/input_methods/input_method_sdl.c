﻿/**
 * File:   input_method_sdl.c
 * Author: AWTK Develop Team
 * Brief:  input method sdl
 *
 * Copyright (c) 2018 - 2018  Guangzhou ZHIYUAN Electronics Co.,Ltd.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * License file for more details.
 *
 */

/**
 * History:
 * ================================================================
 * 2018-06-21 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include <SDL2/SDL.h>
#include "base/mem.h"
#include "base/input_method.h"

static ret_t input_method_sdl_request(input_method_t* im, widget_t* widget) {
  im->widget = widget;

  if (widget != NULL) {
    SDL_Rect r;
    point_t p = {0, 0};
    widget_to_global(widget, &p);

    r.x = p.x;
    r.y = p.y;
    r.w = widget->w;
    r.h = widget->h;

    SDL_SetTextInputRect(&r);
    SDL_StartTextInput();
  } else {
    SDL_StopTextInput();
  }

  return RET_OK;
}

input_method_t* input_method_create(void) {
  input_method_t* im = TKMEM_ZALLOC(input_method_t);
  return_value_if_fail(im != NULL, NULL);

  im->request = input_method_sdl_request;
  emitter_init(&(im->emitter));

  return im;
}

ret_t input_method_destroy(input_method_t* im) {
  return_value_if_fail(im != NULL, RET_BAD_PARAMS);

  emitter_deinit(&(im->emitter));
  TKMEM_FREE(im);

  return RET_OK;
}
