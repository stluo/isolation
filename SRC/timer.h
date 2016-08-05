//include //include guard
#ifndef TIMER_H
#define TIMER_H

//include dependencies
#include <SDL2/SDL.h>

//timer wrapper class to handle functions.
//acts as a stopwatch
class Timer {
  public:
    //constructor
    Timer();

    //timer functions
    void start();
    void stop();
    void pause();
    void unpause();

    //get stopwatch time, up from 0
    Uint32 get_time();

    //timer status
    bool is_started();
    bool is_paused();

  private:
    //start time of timer
    Uint32 start_time;

    //clock ticks since start
    Uint32 start_ticks;

    //clock ticks at pause
    Uint32 pause_ticks;

    //timer status
    bool started;
    bool paused;
};

#endif
