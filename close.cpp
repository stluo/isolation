#include "isolation.h"


void close() {
    //free loaded text
    g_text_texture.free();

    //free font
    TTF_CloseFont( g_font );
    g_font = NULL;

    //destroy window
    SDL_DestroyWindow( g_window );
    SDL_DestroyRenderer( g_renderer );
    g_window = NULL;
    g_renderer = NULL;

    //quit SDL subsystems
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
