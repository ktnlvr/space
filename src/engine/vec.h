#pragma once

#include <math.h>

typedef struct vf2 {
  float x, y;
} vf2;

vf2 vf2_new(const float x, const float y) {
  vf2 ret;
  ret.x = x;
  ret.y = y;
  return ret;
}

vf2 vf2_new_y(const float y) {
  return vf2_new(0, y);
}

vf2 vf2_new_x(const float x) {
  return vf2_new(x, 0);
}

vf2 vf2_zero() { return vf2_new(0, 0); }

vf2 vf2_default() { return vf2_zero(); }

vf2 vf2_add(const vf2 a, const vf2 b) { return vf2_new(a.x + b.x, a.y + b.y); }

vf2 vf2_mul(const vf2 a, const vf2 b) { return vf2_new(a.x * b.x, a.y * b.y); }

vf2 vf2_scale(const float c, const vf2 v) { return vf2_new(c * v.x, c * v.y); }

float vf2_magnitude2(const vf2 v) { return v.x * v.x + v.y * v.y; }

float vf2_magnitude(const vf2 v) { return sqrtf(vf2_magnitude2(v)); }

vf2 vf2_norm_unchecked(const vf2 v) {
  return vf2_scale(1. / vf2_magnitude(v), v);
}

vf2 vf2_norm(const vf2 v) {
  vf2 ret = vf2_norm_unchecked(v);
  if (isnan(ret.x) || isnan(ret.y))
    return vf2_zero();
  return ret;
}
