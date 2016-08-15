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
    void start_stopwatch();
    void start_countdown( int minutes );
    void stop();
    void pause();
    void unpause();

    //get stopwatch time, up from 0
    Uint32 get_stopwatch();

    //get count down time, down from count_down
    Uint32 get_countdown();

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

    //countdown start time, seconds;
    Uint32 countdown_start_time;

    //timer status
    bool started;
    bool paused;
    bool finished;
};

#endif
