#include "isolation.h"

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

        //clear screen
        SDL_SetRenderDrawColor( g_renderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( g_renderer );

        //render frame
        background_texture.render( 0, 0 );
        g_text_texture.render( ( SCREEN_WIDTH - g_text_texture.get_width() ) / 2, 75 );

        //update screen
        SDL_RenderPresent( g_renderer );
      }
    }
  }

  //free memory and close SDL
  close();

  return 0;
}
