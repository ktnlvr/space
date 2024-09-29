#pragma once

#include "vec.h"

typedef struct transform_c {
  vf2 position;
  float rotation;
} transform_c;

ECS_COMPONENT_DECLARE(transform_c);

void transform_c_init(transform_c *transform) {
  transform->position = vf2_new(0, 0);
  transform->rotation = 0;
}