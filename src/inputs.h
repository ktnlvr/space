#pragma once

#include "engine/vec.h"
#include "defs.h"

typedef struct inputs_c {
  int horizontal_input;
  int vertical_input;
} inputs_c;

ECS_COMPONENT_DECLARE(inputs_c);

vf2 inputs_c_get_movement_vector(inputs_c *inputs) {
  ASSERT_NOT_NULL(inputs);

  const vf2 input = vf2_new(inputs->horizontal_input, inputs->vertical_input);
  return vf2_norm(input);
}

void handle_inputs_s(ecs_iter_t *it) {
  ASSERT_NOT_NULL(it);

  inputs_c *inputs = ecs_field(it, inputs_c, 0);
  ASSERT_NOT_NULL(inputs);

  const Uint8* key_states = SDL_GetKeyboardState(NULL);
  ASSERT_NOT_NULL(key_states);

  inputs->horizontal_input = key_states[SDL_SCANCODE_D] - key_states[SDL_SCANCODE_A];
  inputs->vertical_input = key_states[SDL_SCANCODE_S] - key_states[SDL_SCANCODE_W];
}

void inputs_c_init(inputs_c* inputs) {
  ASSERT_NOT_NULL(inputs);

  inputs->horizontal_input = 0;
  inputs->vertical_input = 0;
}
