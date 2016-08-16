#include "isolation.h"

void close() {
    //free textures
    timer_outline_texture.free();
    background_texture.free();
    text_overlay.free();
    timer_texture.free();

    //free sounds
    Mix_FreeChunk( alarm_sound );
    alarm_sound = NULL;

    //free font
    TTF_CloseFont( open_sans );
    open_sans = NULL;
    TTF_CloseFont( open_sans_outline );
    open_sans_outline = NULL;

    //destroy window
    SDL_DestroyWindow( g_window );
    SDL_DestroyRenderer( g_renderer );
    g_window = NULL;
    g_renderer = NULL;

    //quit SDL subsystems
    TTF_Quit();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}
