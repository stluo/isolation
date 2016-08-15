#include "isolation.h"

void close() {
    //free loaded text
    timer_outline_texture.free();

    //free font
    TTF_CloseFont( open_sans );
    open_sans = NULL;

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
