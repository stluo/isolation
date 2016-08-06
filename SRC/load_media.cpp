#include "isolation.h"

bool load_media() {
  bool success = true;

  //load background img
  if( !background_texture.load_from_file( "img/vancouver.jpg" ) ) {
		printf( "Failed to load background texture!\n" );
		success = false;
	}

  //open font
  g_font = TTF_OpenFont( "font/OpenSans-Regular.ttf", 28 );
  if ( g_font == NULL ) {
    printf( "Failed to load lazy font. SDL_ttf Error: %s\n", TTF_GetError() );
    success = false;
  }
  else {
    //render texture
    SDL_Color text_color = { 255, 255, 255, 255 };
    if ( !g_text_texture.load_from_rendered_text( "hello from the other side ", text_color ) ) {
      printf( "Failed to render text texture\n" );
      success = false;
    }
  }

  return success;
}
