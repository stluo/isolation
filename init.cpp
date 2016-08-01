#include "isolation.h"

//font
TTF_Font* g_font = NULL;
//window
SDL_Window* g_window = NULL;
//renderer
SDL_Renderer* g_renderer = NULL;
//load jpeg + font
Texture background_texture;
//rendered font texture
Texture g_text_texture;

bool init() {
  //initialization flag
  bool success = true;

  //initialize SDL
  if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
    printf( "SDL could not initialized. SDL Error: %s\n", SDL_GetError() );
    success = false;
  }
  else {
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
