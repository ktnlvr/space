#pragma once

#include <flecs.h>

#include "transform.h"
#include "vec.h"

typedef struct rigidbody_c {
  float mass;
  float damping;
  vf2 accumulated_force;
  vf2 velocity, acceleration;
} rigidbody_c;

void rigidbody_c_init(rigidbody_c *rigidbody, const float mass) {
  rigidbody->mass = mass;
  rigidbody->damping = 0.;
  rigidbody->velocity = vf2_zero();
  rigidbody->acceleration = vf2_zero();
  rigidbody->accumulated_force = vf2_zero();
}

void rigidbody_c_apply_force(rigidbody_c *rigidbody, const vf2 force) {
  rigidbody->accumulated_force = vf2_add(force, rigidbody->accumulated_force);
}

float rigidbody_c_inv_mass(rigidbody_c* rigidbody) {
  if (rigidbody->mass == 0.0f)
    return 0.;
  return 1. / rigidbody->mass;
}

void clear_forces_s(ecs_iter_t* it) {
  rigidbody_c* rbs = ecs_field(it, rigidbody_c, 0);
  for (int i = 0; i < it->count; i += 1)
    rbs[i].accumulated_force = vf2_zero();
}

void integrate_physics_s(ecs_iter_t *it) {
  const float dt = it->delta_time;

  transform_c *transforms = ecs_field(it, transform_c, 0);
  rigidbody_c *rigidbodies = ecs_field(it, rigidbody_c, 1);

  for (size_t i = 0; i < it->count; i += 1) {
    rigidbody_c *rb = &rigidbodies[i];
    transform_c *tr = &transforms[i];

    rigidbody_c_apply_force(rb, vf2_new_y(19600));

    vf2 resulting_acceleration = rb->acceleration;
    const vf2 acceleration_from_forces = vf2_scale(rigidbody_c_inv_mass(rb), rb->accumulated_force);
    resulting_acceleration = vf2_add(acceleration_from_forces, resulting_acceleration);

    tr->position = vf2_add(tr->position, vf2_scale(dt, rb->velocity));
    rb->velocity = vf2_add(rb->velocity, vf2_scale(dt, resulting_acceleration));
  }
}
