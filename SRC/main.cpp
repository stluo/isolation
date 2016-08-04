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

      //Set text color as black
      SDL_Color textColor = { 0, 0, 0, 255 };

      //The application timer
      Timer timer;

      //In memory text stream
      std::stringstream timeText;

      //while running
      while ( !quit ) {
        //handle events on queue
        while ( SDL_PollEvent( &e ) != 0 ) {
          //user quit
          if ( e.type == SDL_QUIT ) {
            quit = true;
          }
          else if ( e.type == SDL_KEYDOWN ) {
            switch ( e.key.keysym.sym ) {
              case SDLK_q: //quit on q
                quit = true;
                break;

              case SDLK_s:
                if ( !timer.is_started() ) {
                  timer.start();
                }
                else {
                  timer.stop();
                }

              case SDLK_f: //toggle fullscreen on f
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

        //Set text to be rendered
                timeText.str( "" );
                timeText << "Seconds since start time " << ( timer.get_stopwatch_time() ) ;

                //Render text
                if( !gTimeTextTexture.load_from_rendered_text( timeText.str().c_str(), textColor ) )
                {
                    printf( "Unable to render time texture!\n" );
                }

        //clear screen
        SDL_SetRenderDrawColor( g_renderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( g_renderer );

        //render frame
        background_texture.render( 0, 0 );
        g_text_texture.render( ( SCREEN_WIDTH - g_text_texture.get_width() ) / 2, 75 );
        gTimeTextTexture.render( ( SCREEN_WIDTH - gTimeTextTexture.get_width() ) / 2, ( SCREEN_HEIGHT - gTimeTextTexture.get_height() ) / 2 );

        //update screen
        SDL_RenderPresent( g_renderer );
      }
    }
  }

  //free memory and close SDL
  close();

  return 0;
}
