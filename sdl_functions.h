
#ifndef _SDL_FUNCTIONS_H_
#define _SDL_FUNCTIONS_H_

struct sdlist{
    struct sdlist* next;
    SDL_Surface* surface;
};

static inline
Uint8* pixelref(SDL_Surface *surf, unsigned x, unsigned y) {
  int bpp = surf->format->BytesPerPixel;
  return (Uint8*)surf->pixels + y * surf->pitch + x * bpp;
}

void init_sdl(void) ;
void wait_for_keypressed(void) ;
SDL_Surface* display_image(SDL_Surface *img);
Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y);
void putpixel(SDL_Surface *surface,unsigned x,unsigned y,Uint32 pixel);
SDL_Surface* load_image(char *path);
SDL_Surface* image_partition(SDL_Surface *image, int padding_left,
                             int padding_top, int width, int height,
                             int display);

#endif
