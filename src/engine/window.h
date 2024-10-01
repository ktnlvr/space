#pragma once

#include "defs.h"

#include <SDL.h>

typedef struct window_c {
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;
} window_c;

ECS_COMPONENT_DECLARE(window_c);

void window_c_init(window_c *window) {
  ASSERT_NOT_NULL(window);
  ASSERT(SDL_WasInit(0));
  ASSERT_NEQ(SDL_GetNumVideoDrivers(), 0);

  window->sdl_window =
      SDL_CreateWindow("Space", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       640, 480, SDL_WINDOW_SHOWN);
  window->sdl_renderer = SDL_CreateRenderer(window->sdl_window, -1, SDL_RENDERER_ACCELERATED);
}

void window_c_destroy(const window_c* window) {
  ASSERT_NOT_NULL(window);
  SDL_DestroyWindow(window->sdl_window);
}

void renderer_begin_s(ecs_iter_t *it) {
  ASSERT_NOT_NULL(it);

  const window_c* window = ecs_field(it, window_c, 0);
  ASSERT_NOT_NULL(window);

  SDL_SetRenderDrawColor(window->sdl_renderer, 0, 0, 0, 255);
  SDL_RenderClear(window->sdl_renderer);
}

void renderer_end_s(ecs_iter_t *it) {
  ASSERT_NOT_NULL(it);
  const window_c* window = ecs_field(it, window_c, 0);
  ASSERT_NOT_NULL(window);

  SDL_RenderPresent(window->sdl_renderer);
}
