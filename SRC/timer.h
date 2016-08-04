//include //include guard
#ifndef TIMER_H
#define TIMER_H

//include dependencies
#include <SDL2/SDL.h>

//timer wrapper class to handle functions.
//counts down from start_time then up from 0
//counts up 0 from if start_time is not set
//all time in seconds
class Timer {
  public:
    //constructor
    Timer();

    //set start time to count down
    //TODO:void set_start_time(unsigned int minutes);

    //timer functions
    void start();
    void stop();
    void pause();
    void unpause();

    //get stopwatch time, up from 0
    Uint32 get_stopwatch_time();

    //get timer time, down from start_time in unsigned
    //TODO:Uint32 get_timer_time();

    //timer status
    bool is_started();
    bool is_paused();
    bool is_finished();

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
    bool finished;
};

#endif
