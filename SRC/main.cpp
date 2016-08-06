#include "isolation.h"
#include "timer.h"

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
      bool full_screen = false;

      //event handler
      SDL_Event e;

      //Set stop watch text color as white
      SDL_Color textColor = { 255, 255, 255, 255 };

      timer_text_texture.set_blend_mode( SDL_BLENDMODE_BLEND );

      //The application timer
      Timer timer;

      //coeffince for finding alpha
      double coefficient = get_coefficient( 10 );

      //In memory text stream
      std::stringstream time_text;

      //while running
      while ( !quit ) {
        //handle events on queue
        while ( SDL_PollEvent( &e ) != 0 ) {
          //user quit
          if ( e.type == SDL_QUIT ) {
            quit = true;
          }
          else if ( e.type == SDL_USEREVENT ) {
            //the call back function event
            //TODO: get_alpha && check to see if its the last time and thus remove the timer 
          }
          else if ( e.type == SDL_KEYDOWN ) {
            switch ( e.key.keysym.sym ) {
              case SDLK_q: {//quit on q
                quit = true;
                break;
              }

              case SDLK_s: {
                if ( !timer.is_started() ) {
                  timer.start();
                }
                else {
                  timer.stop();
                }
                break;
              }

              case SDLK_SPACE: { //start timer on space
                SDL_TimerID count_down = SDL_AddTimer( 60000 , count_down_callback, NULL); //start a timer for a mintue
                break;
              }

              case SDLK_f: {//toggle fullscreen on f
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

        //Set text to be rendered
        time_text.str( "" );
        time_text << "Seconds since start time " << ( timer.get_time() ) ;

        //Render text
        if( !timer_text_texture.load_from_rendered_text( time_text.str().c_str(), textColor ) )
        {
          printf( "Unable to render time texture!\n" );
        }

        //clear screen
        SDL_SetRenderDrawColor( g_renderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( g_renderer );

        //render frame
        background_texture.render( 0, 0 );
        g_text_texture.render( ( SCREEN_WIDTH - g_text_texture.get_width() ) / 2, 75 );
        timer_text_texture.render( ( SCREEN_WIDTH - timer_text_texture.get_width() ) / 2, ( SCREEN_HEIGHT - timer_text_texture.get_height() ) / 2 );

        //update screen
        SDL_RenderPresent( g_renderer );
      }
    }
  }

  //free memory and close SDL
  close();

  return 0;
}
