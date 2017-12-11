
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <math.h>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#include "sdl_functions.h"


/*
struct sdlist{
    struct sdlist* next;
    SDL_Surface* surface;
};
*/
/*
static inline
Uint8* pixelref(SDL_Surface *surf, unsigned x, unsigned y) {
  int bpp = surf->format->BytesPerPixel;
  return (Uint8*)surf->pixels + y * surf->pitch + x * bpp;
}
*/
/*init_sdl(void) {
  // Init only the video part
  if( SDL_Init(SDL_INIT_VIDEO)==-1 ) {
    // If it fails, die with an error message
    errx(1,"Could not initialize SDL: %s.\n", SDL_GetError());
  }
  // We don't really need a function for that ...
}*/

void wait_for_keypressed(void) {
  SDL_Event             event;
  // Infinite loop, waiting for event
  for (;;) {
    // Take an event
    SDL_PollEvent( &event );
    // Switch on event type
    switch (event.type) {
    // Someone pressed a key -> leave the function
    case SDL_KEYDOWN: return;
    default: break;
    }
  // Loop until we got the expected event
  }
}

SDL_Surface* display_image(SDL_Surface *img) {
  SDL_Surface          *screen;
  // Set the window to the same size as the image
  screen = SDL_SetVideoMode(img->w, img->h, 0, SDL_SWSURFACE|SDL_ANYFORMAT);
  if ( screen == NULL ) {
    // error management
    errx(1, "Couldn't set %dx%d video mode: %s\n",
         img->w, img->h, SDL_GetError());
  }

  /* Blit onto the screen surface */
  if(SDL_BlitSurface(img, NULL, screen, NULL) < 0)
    warnx("BlitSurface error: %s\n", SDL_GetError());

  // Update the screen
  SDL_UpdateRect(screen, 0, 0, img->w, img->h);

  // wait for a key
  wait_for_keypressed();

  // return the screen for further uses
  return screen;
}
/*
Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y) {
  Uint8 *p = pixelref(surface, x, y);
  switch(surface->format->BytesPerPixel) {
  case 1:
    return *p;
  case 2:
    return *(Uint16 *)p;
  case 3:
    if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
      return p[0] << 16 | p[1] << 8 | p[2];
    else
      return p[0] | p[1] << 8 | p[2] << 16;
  case 4:
    return *(Uint32 *)p;
  }
  return 0;
}
*/
void putpixel(SDL_Surface *surface,unsigned x,unsigned y,Uint32 pixel){

    Uint8 *p = pixelref(surface, x, y);
    switch(surface->format->BytesPerPixel) {
    case 1:
    *p = pixel;
    break;
    case 2:
    *(Uint16 *)p = pixel;
    break;
    case 3:
    if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
      p[0] = (pixel >> 16) & 0xff;
      p[1] = (pixel >> 8) & 0xff;
      p[2] = pixel & 0xff;
    } else {
      p[0] = pixel & 0xff;
      p[1] = (pixel >> 8) & 0xff;
      p[2] = (pixel >> 16) & 0xff;
    }
    break;
    case 4:
    *(Uint32 *)p = pixel;
    break;
    }
}

/*SDL_Surface* load_(char *path){

    SDL_Surface *img = NULL;
    img = IMG_Load(path);

    if (img == NULL)
        errx(3, "can't load %s: %s", path, IMG_GetError());

    return img;
}*/
/*
SDL_Surface* load_image(char *path) {
  SDL_Surface          *img;
  img = IMG_Load(path);
  if (!img)
    errx(3, "can't load %s: %s", path, IMG_GetError());
  return img;
}*/

SDL_Surface* image_partition(SDL_Surface *image, int padding_left,
                             int padding_top, int width, int height,
                             int display)
{
    //printf("debut\n");//##################
    //Variables definition
    SDL_Surface* partition;// = malloc(sizeof(SDL_Surface));
    Uint32 rmask, gmask, bmask, amask;
    //printf("apres surface\n");//##################
    //Variables init
    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
        rmask = 0xff000000;
        gmask = 0x00ff0000;
        bmask = 0x0000ff00;
        amask = 0x00000000;
    #else
        rmask = 0x000000ff;
        gmask = 0x0000ff00;
        bmask = 0x00ff0000;
        amask = 0x00000000;
    #endif
    //printf("apres truc bizare\n");//##################
    partition = SDL_CreateRGBSurface(0, width, height, 32,
                                     rmask, gmask, bmask, amask);
    //printf("apres tres triste 2\n");//##################
    //Partition
    for (int i = 0; i < partition->w; i++)
    {
        for (int j = 0; j < partition->h; j++)
        {
            putpixel(partition, i, j, getpixel(image, padding_left + i,
                                               padding_top + j));
        }
    }
    //printf("apres forfor\n");//##################
    //if display == 1 then display partition before return
    if (display)
    {
        display_image(partition);
    }
    //printf("fin\n");//##################
    return partition;
}
