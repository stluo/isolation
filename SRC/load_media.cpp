#include "isolation.h"

bool load_media() {
  bool success = true;

  srand(time(NULL));
  unsigned background_num = rand() % 5 + 1;
  background_file_1280.str( "" );
  background_file_1280 << "img/" << background_num << "_1280.jpg";
  background_file_1920.str( "" );
  background_file_1920 << "img/" << background_num << "_1920.jpg";

  //load background img
  if( !background_texture.load_from_file( background_file_1280.str().c_str() ) ) {
		printf( "Failed to load background texture!\n" );
		success = false;
	}

  //load overlay img
  if( !text_overlay.load_from_file( "img/space_start_1280.png" ) ) {
		printf( "Failed to load background texture!\n" );
		success = false;
	}

  //open font
  open_sans = TTF_OpenFont( "font/OpenSans-Regular.ttf", 28 );
  if ( open_sans == NULL ) {
    printf( "Failed to load OpenSans-Regular font. SDL_ttf Error: %s\n", TTF_GetError() );
    success = false;
  }

  //open same font for outline
  open_sans_outline = TTF_OpenFont( "font/OpenSans-Regular.ttf", 28 );
  TTF_SetFontOutline(open_sans_outline, 1);      //set outline size
  if ( open_sans == NULL ) {
    printf( "Failed to load OpenSans-Regular font. SDL_ttf Error: %s\n", TTF_GetError() );
    success = false;
  }

  //load alarm sound effect
  alarm_sound = Mix_LoadWAV( "sound/vibration.wav" );
  if( alarm_sound == NULL ) {
    printf( "Failed to load vibration sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
    success = false;
  }

  return success;
}
