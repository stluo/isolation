#include "isolation.h"
#include "timer.h"
#include "helper.h"

int main( int argc, char* args[] ) {
  //start up SDL
  if ( !init() ) {
    printf( "Failed to initialize.\n" );
  }
  else {
    //load media
    if ( !load_media() ) {
      printf( "Failed to load media.\n" );
    }
    else{
      //main loop flag
      bool quit = false;
      bool on_break = true;
      bool is_short_break = true;
      bool hardcore = false;

      //event handler
      SDL_Event e;

      //timer for break;
      Timer timer;
      //stopwatch for extra study time;
      Timer stopwatch;

      unsigned study_length = 0;
      unsigned short_break_length = 0;
      unsigned long_break_length = 0;

      //coeffince for finding alpha
      double coefficient = get_coefficient( 10 );

      //load settings
      load_settings( &study_length, &short_break_length, &long_break_length, &hardcore);

      //while running
      while ( !quit ) {
        //handle events on queue
        while ( SDL_PollEvent( &e ) != 0 ) {
          //user quit
          if ( e.type == SDL_QUIT ) {
            quit = true;
          }
          else if ( e.type == SDL_USEREVENT ) {
            printf( "hello\n" );
            //the call back function event
            //TODO: get_alpha && check to see if its the last time and thus remove the timer
          }
          else if ( e.type == SDL_KEYDOWN ) {
            switch ( e.key.keysym.sym ) {

              case SDLK_q: {      //quit on q
                quit = true;
                break;
              }

              case SDLK_SPACE: {      //start timer on space
                if ( e.key.repeat != 0 ) {
                  break;
                }
                if ( on_break ) {
                  on_break = !end_break( is_short_break );
                }
                else {
                  //start break
                  if ( is_short_break ) {
                    on_break = start_break( is_short_break, short_break_length, long_break_length, &timer );
                    is_short_break = false;
                  }
                  else {
                    on_break = start_break( is_short_break, short_break_length, long_break_length, &timer );
                    is_short_break = true;
                  }
                }
                break;
              }

              case SDLK_s: {
                //Mix_PlayChannel( -1, alarm_sound, -1 );
                Mix_HaltChannel(-1);      //stop sound on all channels
                //SDL_TimerID count_down = SDL_AddTimer( 3000 , count_down_callback, NULL);
                timer.start_stopwatch();
                break;
              }

              case SDLK_f: {      //toggle fullscreen on f
                if ( e.key.repeat != 0 ) {
                  break;
                }
                if ( !full_screen ) {
                  SDL_SetWindowFullscreen( g_window, SDL_WINDOW_FULLSCREEN_DESKTOP );
                  full_screen = true;
                }
                else if ( full_screen ) {
                    SDL_SetWindowFullscreen( g_window, 0 );
                    full_screen = false;
                }
                break;
              }
            }
          }
        }

        draw_text( &timer, &stopwatch );

        render_screen();
      }
    }
  }


  //free memory and close SDL
  close();

  return 0;
}
