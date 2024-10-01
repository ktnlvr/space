#pragma once

#include "transform.h"
#include "window.h"

#include <flecs.h>

typedef enum collider_kind_e {
  COLLIDER_KIND_E_CIRCLE,
} collider_kind_e;

typedef struct collider_c {
  collider_kind_e kind;
  union {
    float radius;
  } circle;
} collider_c;

ECS_COMPONENT_DECLARE(collider_c);

void collider_c_init_circle(collider_c *collider, const float radius) {
  ASSERT_NOT_NULL(collider);

  collider->kind = COLLIDER_KIND_E_CIRCLE;
  collider->circle.radius = radius;
}

vf2 get_circle_points(const char idx) {
  const float sqrt2 = 1.414213562f;
  const float sqrt3 = 1.73205080757;
  const vf2 circle_points[16] = {
      {2, 0},  {sqrt3, 1},   {sqrt2, sqrt2},   {1, sqrt3},
      {0, 2},  {-1, sqrt3},  {-sqrt2, sqrt2},  {-sqrt3, 1},
      {-2, 0}, {-sqrt3, -1}, {-sqrt2, -sqrt2}, {-1, -sqrt3},
      {0, -2}, {1, -sqrt3},  {sqrt2, -sqrt2},  {sqrt3, -1}};

  return vf2_scale(0.5, circle_points[idx % 16]);
}

void debug_draw_colliders_s(ecs_iter_t *it) {
  ASSERT_NOT_NULL(it);

  const window_c *window = ecs_field(it, window_c, 0);
  const collider_c *colliders = ecs_field(it, collider_c, 1);
  const transform_c *transforms = ecs_field(it, transform_c, 2);

  SDL_SetRenderDrawColor(window->sdl_renderer, 255, 0, 0, 255);
  for (size_t i = 0; i < it->count; i++) {
    vf2 center = vf2_default();
    if (transforms != NULL) {
      center.x = transforms[i].position.x;
      center.y = transforms[i].position.y;
    }

    switch (colliders[i].kind) {
    case COLLIDER_KIND_E_CIRCLE:
      SDL_RenderDrawPoint(window->sdl_renderer, center.x, center.y);
      for (char j = 0; j < 16; j++) {
        const char k = (j + 1) % 16;
        const float r = colliders[i].circle.radius;

        const vf2 start = vf2_add(vf2_scale(r, get_circle_points(j)), center);
        const vf2 end = vf2_add(vf2_scale(r, get_circle_points(k)), center);

        SDL_RenderDrawLine(window->sdl_renderer, start.x, start.y, end.x,
                           end.y);
      }
    }
  }
}