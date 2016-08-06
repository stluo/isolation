#include "isolation.h"
#include <cmath>

//find the coefficient using the user set timer mintues
double get_coefficient( int total_minutes ) {
  double coefficient = 0.0;
  coefficient = 255 / pow( (double)total_minutes, 2.0 );
  return coefficient;
}

//find alpha value at specific mintues using coefficient
Uint8 get_alpha( int minutes, double coefficient ) {
  Uint8 alpha = 0;
  alpha = ceil( coefficient * pow( minutes, 2 ) );
  if ( alpha <= 255 ) {
    return alpha;   //make sure that alpha is 255 or lower
  }
  else {
    return alpha = 255;
  }
}

//call backfunction for timer, pushing ONE_MINUTE into event queue
//also cause callback to be called again at one mintue
Uint32 count_down_callback( Uint32 interval, void *param ) {
  SDL_Event event;
  SDL_UserEvent userevent;

  userevent.type = SDL_USEREVENT;
  userevent.code = 0;
  userevent.data1 = NULL;
  userevent.data2 = NULL;

  event.type = SDL_USEREVENT;
  event.user = userevent;

  SDL_PushEvent(&event);
  return(interval);
}
