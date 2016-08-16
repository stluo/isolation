#include "isolation.h"

//full screen flag
bool full_screen = false;
//font
TTF_Font* open_sans = NULL;
//font outline
TTF_Font* open_sans_outline = NULL;
//window
SDL_Window* g_window = NULL;
//renderer
SDL_Renderer* g_renderer = NULL;
//alarm_sound
Mix_Chunk *alarm_sound = NULL;
//background texture
Texture background_texture;
//text overlay texture
Texture text_overlay;
//timer text texture
Texture timer_texture;
//timer text outline texture
Texture timer_outline_texture;

bool init() {
  //initialization flag
  bool success = true;

  //initialize SDL
  if ( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO ) < 0 ) {
    printf( "SDL could not initialized. SDL Error: %s\n", SDL_GetError() );
    success = false;
  }
  else {
    //initialize sdl audio with default format + frequency, 2 channel (stereo)
    if( Mix_OpenAudio( MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096 ) < 0 )
      {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
      }

    //set texture filtering linear
    if ( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ) {
      printf( "Warning: Linear filtering not enabled\n" );
    }

    //create window
    g_window = SDL_CreateWindow( "Isolation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if ( g_window == NULL ) {
      printf( "Window could not be created. SDL Error: %s\n", SDL_GetError() );
      success = false;
    }
    else {
      //create vsynced renderer
      g_renderer = SDL_CreateRenderer( g_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
      if ( g_renderer == NULL ) {
        printf( "Renderer could not be created. SDL Error: %s\n", SDL_GetError() );
        success = false;
      }
      else {
        //initialize renderer color
        SDL_SetRenderDrawColor (g_renderer, 0xFF, 0xFF, 0xFF, 0xFF );

        //initialize JPEG loading
        int img_flags = IMG_INIT_JPG;
        if ( !( IMG_Init( img_flags ) & img_flags ) ) {
            printf( "SDL_image could not be initialize. SDL_image Error: %s\n", IMG_GetError() );
            success = false;
        }

        //initialize SDL_ttf
        if (TTF_Init() == -1 ) {
          printf( "SDL_ttf could not be initialize. SDL_ttf Error: %s\n", TTF_GetError() );
        }
      }
    }
  }

  return success;
}
