//include //include guard
#ifndef HELPER_H
#define HELPER_H

//include dependencies
#include <cmath>
#include <sstream>
#include <iomanip>

//include headers
#include "isolation.h"
#include "timer.h"

//find coefficient for exp func depended on user set total minutes
double get_coefficient( int total_minutes );

//find the alpha value at a specific minute
Uint8 get_alpha( int minutes, double coefficient );

//function to start break
bool start_break( bool short_break, unsigned short_length, unsigned long_length, Timer *timer);

//function to end break
bool end_break( bool short_break );

//function to load settings from settings.txt
void load_settings( unsigned *study_length, unsigned *short_length, unsigned *long_length, bool *hardcore );

//draw and format text then create texture
void draw_text( Timer *timer, Timer *stopwatch, SDL_Color BLACK, SDL_Color WHITE );

//function to clear then render frame then update screen
void render_screen();

//timer callback func
Uint32 count_down_callback( Uint32 interval, void *param );

//alarm callback func
Uint32 alarm_callback( Uint32 interval, void *param );

#endif
