//include //include guard
#ifndef ISOLATION_H
#define ISOLATION_H

//include dependencies
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <sstream>

//include headers
#include "texture.h"

//Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 800;

//forward delcarlation
//class Texture;

//start up SDL create window
bool init();

//load all media
bool load_media();

//free all and shut down SDL
void close();

//find coefficient for exp func depended on user set total minutes
double get_coefficient( int total_minutes );

//find the alpha value at a specific mintue
Uint8 get_alpha( int minutes, double coefficient );

//timer callback func
Uint32 count_down_callback( Uint32 interval, void *param );

//load global front
extern TTF_Font* g_font;

//window
extern SDL_Window* g_window;

//renderer
extern SDL_Renderer* g_renderer;

//load jpeg
extern Texture background_texture;

//rendered font texture
extern Texture g_text_texture;

//timer Texture
extern Texture timer_text_texture;

#endif