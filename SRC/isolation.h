//include //include guard
#ifndef ISOLATION_H
#define ISOLATION_H

//include dependencies
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <time.h>

//include headers
#include "texture.h"

//Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int FULL_SCREEN_WIDTH = 1920;
const int FULL_SCREEN_HEIGHT = 1080;

//start up SDL create window
bool init();

//load all media
bool load_media();

//free all and shut down SDL
void close();

//for background
extern std::stringstream background_file_1280;
extern std::stringstream background_file_1920;

//TimerID count_down
extern SDL_TimerID count_down;

//full screen flag
extern bool full_screen;

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
