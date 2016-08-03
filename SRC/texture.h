//include guard
#ifndef TEXTURE_H
#define TEXTURE_H

//include dependencies
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>

class Texture {
  public:
    //initializes variables
    Texture();

    //deallocates memory
    ~Texture();

    //load image from path
    bool load_from_file( std::string path );

    //create image from font string
    bool load_from_rendered_text( std::string textureText, SDL_Color text_color );

    //deallocates texture
    void free();

    //set color modulation
    void set_color( Uint8 red, Uint8 green, Uint8 blue );

    //set blend mode
    void set_blend_mode( SDL_BlendMode blending );

    //set alpha
    void set_alpha( Uint8 alpha );

    //render texture at point
    void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE ) const;

    //get image dimensions
    int get_width() const;
    int get_height() const;

  private:
    //texture pointer
    SDL_Texture* m_texture;

    //dimensions
    int m_width;
    int m_height;
};

#endif
