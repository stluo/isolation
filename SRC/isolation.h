//include //include guard
#ifndef ISOLATION_H
#define ISOLATION_H

//include dependencies
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <string>

//include headers
#include "texture.h"

//Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

//start up SDL create window
bool init();

//load all media
bool load_media();

//free all and shut down SDL
void close();

//full screen flag
extern  bool full_screen;

//load global front
extern TTF_Font* open_sans;

//load global font outline
extern TTF_Font* open_sans_outline;

//window
extern SDL_Window* g_window;

//renderer
extern SDL_Renderer* g_renderer;

//background texture
extern Texture background_texture;

//text overlay texture
extern Texture text_overlay;

//rendered font texture
extern Texture timer_outline_texture;

//timer Texture
extern Texture timer_texture;

//alarm sound effect
extern Mix_Chunk *alarm_sound;

#endif
