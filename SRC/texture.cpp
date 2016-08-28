#include "texture.h"
#include "isolation.h"

Texture::Texture() {
  //initialize object
  m_texture = NULL;
  m_width = 0;
  m_height = 0;
}

Texture::~Texture() {
  //deallocates
  free();
}

bool Texture::load_from_file( std::string path ) {
  //deallocate preexisiting texture
  free();

  //final texture
  SDL_Texture* new_texture = NULL;

  //load image at path
  SDL_Surface* loaded_surface = IMG_Load( path.c_str() );
  if ( loaded_surface == NULL ) {
    printf("Unable to load image %s. SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
  }
  else {
    //set key image
    SDL_SetColorKey ( loaded_surface, SDL_TRUE, SDL_MapRGB( loaded_surface->format, 0, 0xFF, 0xFF ) );

    //create texture from pixels
    new_texture = SDL_CreateTextureFromSurface( g_renderer, loaded_surface );
    if ( new_texture == NULL ) {
      printf("Unable to create texture from %s. SDL Error: %s\n", path.c_str(), SDL_GetError() );
    }
    else {
      //get dimensions
      m_width = loaded_surface->w;
      m_height = loaded_surface->h;
    }

    //deallocate old SDL_Surface
    SDL_FreeSurface( loaded_surface );
  }

  m_texture = new_texture;
  return m_texture != NULL;
}

bool Texture::load_from_rendered_text( std::string texture_text, SDL_Color text_color, TTF_Font* font ) {
  //deallocate preexisting texture
  free();

  //render text surface
  SDL_Surface* text_surface = TTF_RenderText_Blended_Wrapped( font, texture_text.c_str(), text_color, SCREEN_WIDTH );
  if ( text_surface == NULL ) {
    printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
  }
  else {
    //create texture from SDL_FreeSurface
    m_texture = SDL_CreateTextureFromSurface( g_renderer, text_surface );
    if ( m_texture == NULL ) {
      printf("Unable to create texture from rendered text. SDL Error: %s\n", SDL_GetError() );
    }
    else {
      //get dimensions
      m_width = text_surface->w;
      m_height = text_surface->h;
    }

    //deallocate old surface
    SDL_FreeSurface( text_surface );

    //return bool
    return m_texture != NULL;
  }
}

void Texture::free() {
  //free if texture exists
  if ( m_texture != NULL ) {
    SDL_DestroyTexture( m_texture );
    m_texture = NULL;
    m_width = 0;
    m_height = 0;
  }
}

void Texture::set_color( Uint8 red, Uint8 green, Uint8 blue ) {
  //modulate rgb
  SDL_SetTextureColorMod( m_texture, red, green, blue );
}

void Texture::set_blend_mode( SDL_BlendMode blending ){
  SDL_SetTextureBlendMode( m_texture, blending );
}

void Texture::set_alpha( Uint8 alpha ) {
  //modulate alpha
  SDL_SetTextureAlphaMod( m_texture, alpha );
}

void Texture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip ) const {
  //set rendering space and render to screen
  SDL_Rect render_quad = { x, y, m_width, m_height };

  //set clip dimensions
  if ( clip != NULL ) {
    render_quad.w = clip->w;
    render_quad.h = clip->h;
  }

  //render to screen
  SDL_RenderCopy( g_renderer, m_texture, clip, &render_quad );
}

int Texture::get_width() const {
  return m_width;
}

int Texture::get_height() const {
  return m_height;
}
