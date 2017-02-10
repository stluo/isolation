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

      //counter for force quit when hardcore is off
      unsigned force_quit_counter = 0;

      //assign RGB colors
      SDL_Color WHITE = { 255, 255, 255, 255 };
      SDL_Color BLACK = { 0, 0, 0, 255 };

      //event handler
      SDL_Event e;

      //timer for break;
      Timer timer;
      //stopwatch for extra study time;
      Timer stopwatch;

      unsigned minute_counter = 0;
      unsigned study_length = 0;
      unsigned short_break_length = 0;
      unsigned long_break_length = 0;

      //load settings
      load_settings( &study_length, &short_break_length, &long_break_length, &hardcore);

      //coeffince for finding alpha
      double coefficient = get_coefficient( study_length );

      //while running
      while ( !quit ) {
        //handle events on queue
        while ( SDL_PollEvent( &e ) != 0 ) {
          //user quit
          if ( e.type == SDL_QUIT ) {
            quit = true;
          }
          else if ( e.type == SDL_USEREVENT ) {
            minute_counter++;

            //reset forcequit counter ever minute
            force_quit_counter = 0;


            if ( minute_counter < study_length ) {
              //set the text_overlay alpha using exp graph
              text_overlay.set_alpha( get_alpha( minute_counter, coefficient) );
            }
            else if ( minute_counter == study_length ) {
              //reset minute_counter
              minute_counter = 0;
              //set text_overlay alpha to be fully opaque
              text_overlay.set_alpha( 255 );
              //remove count_down SDL_Timer
              SDL_RemoveTimer( count_down );
              //start stopwatch to count extra study time
              stopwatch.start_stopwatch();
            }
          }
          else if ( e.type == SDL_KEYDOWN ) {
            switch ( e.key.keysym.sym ) {

              case SDLK_q: {      //quit on q

                //detect force quit on softcore
                if ( e.key.repeat == 1 && hardcore == false) {
                  force_quit_counter++;
                }

                //quit = true;
                if ( on_break ) {
                  quit = true;
                }
                break;
              }

              case SDLK_SPACE: {      //start timer on space
                if ( e.key.repeat != 0 ) {
                  break;
                }
                if ( on_break ) {
                  //start studyhing stop timer
                  timer.stop();
                  stopwatch.stop();
                  on_break = !end_break( is_short_break );
                }
                else if ( stopwatch.is_started() ) {
                  //start break, stop stopwatch
                  timer.stop();
                  stopwatch.stop();

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
                Mix_HaltChannel(-1);      //stop sound on all channel
                //timer.start_stopwatch();
                stopwatch.start_stopwatch();
                quit = true;
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

        //force quit detection
        if ( force_quit_counter > 333 ) {
          quit = true;
        }

        //prevents alt-tab
        if ( !on_break ) {
          SDL_RaiseWindow( g_window );
        }

        draw_text( &timer, &stopwatch, BLACK, WHITE );

        render_screen();
      }
    }
  }

  //free memory and close SDL
  close();

  return 0;
}
