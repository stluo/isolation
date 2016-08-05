#include "timer.h"

Timer::Timer() {
  //initialize variables
  start_time = 0;
  start_ticks = 0;
  pause_ticks = 0;

  started = false;
  paused = false;
}

//to start timer, will also restart
void Timer::start() {
  //set status to start
  started = true;
  paused = false;

  //get current ticks
  start_ticks = SDL_GetTicks();
  pause_ticks = 0;
}

//stop timer re-initialize variables
void Timer::stop() {
  start_ticks = 0;
  pause_ticks = 0;

  started = false;
  paused = false;
}

//pause timer only when already started
void Timer::pause() {
  //if timer is started and not paused
  if ( started && !paused ) {
    paused = true;
    pause_ticks = SDL_GetTicks() - start_ticks;      //find stop ticks

    start_ticks = 0;
  }
}

//unpause timer only when started AND paused
void Timer::unpause() {
  if ( started && paused ) {
    paused = false;
    start_ticks = SDL_GetTicks() - pause_ticks;      //reset starting_ticks

    pause_ticks = 0;
  }
}

//if stopped returns 0
Uint32 Timer::get_time() {
  //the actual stopwatch time
  Uint32 time = 0;

  if ( started ) {       //if started
    if ( paused ) {      //if paused
      time = pause_ticks;
    }
    else {
      time = SDL_GetTicks() - start_ticks;      //current time - start time;
    }
  }

  time = time/1000;      //convert to seconds
  return time;
}

bool Timer::is_started() {
  return started;
}

bool Timer::is_paused() {
  return paused && started;
}
