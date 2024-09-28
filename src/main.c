#include <stdio.h>

#include <SDL.h>
#include <flecs.h>

#include "engine/window.h"
#include "engine/event.h"

int main(int argc, char *argv[]) {
  SDL_Init(SDL_INIT_VIDEO);

  ecs_world_t* world = ecs_init();

  ECS_COMPONENT(world, window_c);
  ECS_COMPONENT(world, sdl_events_c);

  ECS_SYSTEM(world, renderer_begin_s, EcsPreFrame, window_c);
  ECS_SYSTEM(world, renderer_end_s, EcsPostFrame, window_c);
  ECS_SYSTEM(world, handle_sdl_events_s, EcsPreFrame, sdl_events_c);

  window_c window;
  window_c_init(&window);
  ecs_singleton_set_ptr(world, window_c, &window);

  sdl_events_c sdl_events;
  sdl_events_c_init(&sdl_events);
  ecs_singleton_set_ptr(world, sdl_events_c, &sdl_events);

  bool running = true;
  while (running) {
    if (ecs_singleton_get(world, sdl_events_c)->shutdown_requested)
      running = false;

    ecs_progress(world, 0);
  }

  window_c_destroy(&window);

  SDL_Quit();
  ecs_fini(world);

  return 0;
}
