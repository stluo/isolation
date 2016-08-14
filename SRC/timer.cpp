#include "timer.h"

Timer::Timer() {
  //initialize variables
  start_time = 0;
  start_ticks = 0;
  pause_ticks = 0;
  countdown_start_time = 0;

  started = false;
  paused = false;
  finished = true;
}

//to start timer, will also restart
void Timer::start_stopwatch() {
  //set status to start
  started = true;
  paused = false;
  finished = true;

  //get current ticks
  start_ticks = SDL_GetTicks();
  pause_ticks = 0;
}

void Timer::start_countdown( int minutes ) {
  //set status to start set finished to false
  started = true;
  paused = false;
  finished = false;

  start_ticks = SDL_GetTicks();
  pause_ticks = 0;
  countdown_start_time = minutes * 60000;     //convert to milliseconds and set
}

//stop timer re-initialize variables
void Timer::stop() {
  start_ticks = 0;
  pause_ticks = 0;
  countdown_start_time = 0;

  finished = true;
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
Uint32 Timer::get_stopwatch() {
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

//if stopped returns current time at count down, start a
Uint32 Timer::get_countdown() {
  Uint32 time = 0;

  if ( !finished ) {      //if the timer is not finished
    Uint32 x = get_stopwatch();
    time = (countdown_start_time - x);
    //time = ceil(time/1000);      //convert to Seconds
    printf("%i\n", time );
    return time;
    }
  else {
    return get_stopwatch();      //behave as stopwatch if timer completed
  }
}

bool Timer::is_started() {
  return started;
}

bool Timer::is_paused() {
  return paused && started;
}

bool Timer::is_finished() {
  return finished;
}
