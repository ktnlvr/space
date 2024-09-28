#pragma once

#include <SDL.h>

typedef struct window_c {
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;
} window_c;

void window_c_init(window_c *window) {
  // TODO: assert window is not null
  // TODO: assert SDL initialized
  // TODO: assert display exists

  window->sdl_window =
      SDL_CreateWindow("Space", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       640, 480, SDL_WINDOW_SHOWN);
  window->sdl_renderer = SDL_CreateRenderer(window->sdl_window, -1, SDL_RENDERER_ACCELERATED);
}

void window_c_destroy(const window_c* window) {
  SDL_DestroyWindow(window->sdl_window);
}

void renderer_begin_s(ecs_iter_t *it) {
  // TODO: assert iterator is not null
  const window_c* window = ecs_field(it, window_c, 0);
  // TODO: assert that window exists once

  SDL_SetRenderDrawColor(window->sdl_renderer, 0, 0, 0, 255);
  SDL_RenderClear(window->sdl_renderer);
}

void renderer_end_s(ecs_iter_t *it) {
  // TODO: assert iterator is not null
  const window_c* window = ecs_field(it, window_c, 0);
  // TODO: assert that window exists once

  SDL_RenderPresent(window->sdl_renderer);
}
