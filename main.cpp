#include "isolation.h"
//#include "texture.h"

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
        }

        //clear screen
        SDL_SetRenderDrawColor( g_renderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( g_renderer );

        //render frame
        g_text_texture.render( ( SCREEN_WIDTH - g_text_texture.get_width() ) / 2, ( SCREEN_HEIGHT - g_text_texture.get_height() ) / 2 );

        //update screen
        SDL_RenderPresent( g_renderer );
      }
    }
  }

  //free memory and close SDL
  close();

  return 0;
}
