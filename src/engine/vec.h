#pragma once

typedef struct vf2 { float x, y; } vf2;

vf2 vf2_new(const float x, const float y) {
  vf2 ret;
  ret.x = x;
  ret.y = y;
  return ret;
}

vf2 vf2_default() {
  return vf2_new(0, 0);
}

vf2 vf2_add(const vf2 a, const vf2 b) {
  return vf2_new(a.x + b.x, a.y + b.y);
}

vf2 vf2_mul(const vf2 a, const vf2 b) {
  return vf2_new(a.x * b.x, a.y * b.y);
}

vf2 vf2_scale(const float c, vf2 v) {
  return vf2_new(c * v.x, c * v.y);
}