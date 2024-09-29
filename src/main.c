#include <stdio.h>

#include <SDL.h>
#include <flecs.h>

#include "engine/collider.h"
#include "engine/event.h"
#include "engine/transform.h"
#include "engine/window.h"

int main(int argc, char *argv[]) {
  SDL_Init(SDL_INIT_VIDEO);

  ecs_world_t *world = ecs_init();

  ECS_COMPONENT(world, window_c);
  ECS_COMPONENT(world, sdl_events_c);
  ECS_COMPONENT(world, collider_c);
  ECS_COMPONENT(world, transform_c);

  ECS_SYSTEM(world, renderer_begin_s, EcsPreFrame, window_c($));
  ECS_SYSTEM(world, renderer_end_s, EcsPostFrame, window_c($));
  ECS_SYSTEM(world, handle_sdl_events_s, EcsPreFrame, sdl_events_c($));
  ECS_SYSTEM(world, debug_draw_colliders_s, EcsPostUpdate, window_c($), collider_c, ?transform_c);

  window_c window;
  window_c_init(&window);
  ecs_singleton_set_ptr(world, window_c, &window);

  sdl_events_c sdl_events;
  sdl_events_c_init(&sdl_events);
  ecs_singleton_set_ptr(world, sdl_events_c, &sdl_events);

  collider_c circle_collider;
  collider_c_init_circle(&circle_collider, 16.);

  transform_c player_transform;
  transform_c_init(&player_transform);
  player_transform.position.x = 100;
  player_transform.position.y = 100;

  ecs_entity_t player = ecs_new(world);
  ecs_set_ptr(world, player, collider_c, &circle_collider);
  ecs_set_ptr(world, player, transform_c, &player_transform);

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
