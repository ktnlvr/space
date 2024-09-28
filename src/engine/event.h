#pragma once

#include <stdbool.h>

#include <SDL.h>
#include <flecs.h>

#define MAX_SDL_EVENTS 16

typedef struct sdl_events_c {
  bool shutdown_requested;

  SDL_Event events[MAX_SDL_EVENTS];
  uint32_t event_count;
} sdl_events_c;

void sdl_events_c_init(sdl_events_c *events) {
  events->shutdown_requested = false;
  events->event_count = 0;
  memset(events->events, 0xDEAD, sizeof(SDL_Event) * MAX_SDL_EVENTS);
}

void sdl_events_c_append(sdl_events_c* self, const SDL_Event event) {
  self->event_count = (self->event_count + 1) % MAX_SDL_EVENTS;
  self->events[self->event_count] = event;
}

void handle_sdl_events_s(ecs_iter_t* it) {
  // TODO: assert iterator is not null
  sdl_events_c* events = ecs_field(it, sdl_events_c, 0);
  // TODO: assert that window exists once

  sdl_events_c_init(events);

  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT)
      events->shutdown_requested = true;
    sdl_events_c_append(events, event);
  }
}