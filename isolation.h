//include //include guard
#ifndef ISOLATION_H
#define ISOLATION_H

//include dependencies
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>

//include headers
#include "texture.h"

//Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 800;

//forward delcarlation
class Texture;

//start up SDL create window
bool init();

//load all media
bool load_media();

//free all and shut down SDL
void close();

//load global front
TTF_Font* g_font = NULL;

//window
SDL_Window* g_window = NULL;

//renderer
SDL_Renderer* g_renderer = NULL;

//load jpeg + font
//Texture background_texture;

//rendered font texture
Texture g_text_texture;

#endif
