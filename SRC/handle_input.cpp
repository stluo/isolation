#include "isolation.h"
#include "timer.h"

void handle_input( bool *quit, bool *on_break, bool *short_break, Timer *timer) {
  if ( KEYS[SDLK_q] ) {
    *quit = true;
  }

}
