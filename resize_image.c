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

/*static inline
Uint8* pixelref(SDL_Surface *surf, unsigned x, unsigned y) {
  int bpp = surf->format->BytesPerPixel;
  return (Uint8*)surf->pixels + y * surf->pitch + x * bpp;
}

void init_sdl(void) {
  // Init only the video part
  if( SDL_Init(SDL_INIT_VIDEO)==-1 ) {
    // If it fails, die with an error message
    errx(1,"Could not initialize SDL: %s.\n", SDL_GetError());
  }
  // We don't really need a function for that ...
}

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

  // Blit onto the screen surface
  if(SDL_BlitSurface(img, NULL, screen, NULL) < 0)
    warnx("BlitSurface error: %s\n", SDL_GetError());

  // Update the screen
  SDL_UpdateRect(screen, 0, 0, img->w, img->h);

  // wait for a key
  wait_for_keypressed();

  // return the screen for further uses
  return screen;
}

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
  SDL_Surface
            *img;
  img = IMG_Load(path);
  if (!img)
    errx(3, "can't load %s: %s", path, IMG_GetError());
  return img;
}*/

/*
SDL_Surface* resize(SDL_Surface* img, int newH, int newW){

  int height = img->h;
  int width = img->w;

  int facth = (int)((width<<16)/newW) + 1;
  int factw = (int)((height<<16)/newH) + 1;

  int h2, w2 = 0;
  int* newmat = malloc(sizeof(int) * newH * newW);
  int* oldmat = malloc(sizeof(int) * height * width);
  Uint8 r;
  Uint8 g;
  Uint8 b;

  Uint32 p;

  printf("\n");////////////////////
  for(int i = 0; i < height; i++)
  {
    for(int j = 0; j < width; j++)
    {
      p = getpixel(img, j, i);
      SDL_GetRGB(p, img->format, &r, &g, &b);
      oldmat[j + i * width] = r < 127 ? 1 : 0;
      printf("%d", oldmat[j + i * width]);////////
    }
    printf("\n");//////
  }


  printf("\n");////////////////////
  for(int i = 0; i < newH; i++){
    for(int j = 0; j < newW; j++){
      w2 = ((j * factw)>>16);
      h2 = ((i * facth)>>16);
      newmat[(i * newW) + j] = oldmat[(h2 * width) + w2];

      printf("%d", newmat[j + i * newW]);////////
    }
    printf("\n");//////
  }

#region
  SDL_Surface* partition;// = malloc(sizeof(SDL_Surface));
  Uint32 rmask, gmask, bmask, amask;
  //printf("apres surface\n");//#################
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
  partition = SDL_CreateRGBSurface(0, newW, newH, 32,
                                   rmask, gmask, bmask, amask);

  for (int i = 0; i < newH; i++){
    for (int j = 0; j < newW; j++){
      putpixel(partition, j, i, newmat[j + i * w2] != 0 ? 0x00000000 : 0xFFFFFFFF);
    }
  }
  display_image(partition);
#end
  return partition;
}
*/

SDL_Surface* resize_float(SDL_Surface* img){

  int w1 = img->w;
  int h1 = img->h;

  SDL_Surface* partition;// = malloc(sizeof(SDL_Surface));
  Uint32 rmask, gmask, bmask, amask;
  //printf("apres surface\n");//#################
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
  partition = SDL_CreateRGBSurface(0, 32, 32, 32,
                                   rmask, gmask, bmask, amask);

  Uint8 r;
  Uint8 g;
  Uint8 b;

  Uint32 p;

  int* oldmat = malloc(sizeof(int) * h1 * w1);
  for(int i = 0; i < h1; i++)
  {
    for(int j = 0; j < w1; j++)
    {
      p = getpixel(img, j, i);
      SDL_GetRGB(p, img->format, &r, &g, &b);
      oldmat[j + i * w1] = r < 127 ? 1 : 0;
    }
  }


  double x_ratio = w1/(double)32;
  double y_ratio = h1/(double)32;

  double px, py;
  for(int i = 0; i < 32; i++){
    for(int j = 0; j < 32; j++){
      px = floor(j * x_ratio);
      py = floor(i * y_ratio);
      putpixel(partition, j, i, oldmat[(int)((py * w1) + px)] ? 0x00000000 : 0xFFFFFFFF);
    }
  }
  display_image(partition);

  free(oldmat);
  return partition;
}

/*
int main(int argc, char *argv[]){

    if(argc < 2)
    {
      errx(1, "nombre d'arguments trop faible");
    }

    init_sdl();

    SDL_Surface* img = load_image(argv[1]);
    printf("h = %d, w = %d\n", img->h, img->w);
    img = resize_float(img);
    SDL_SaveBMP(img, "cu2.bmp");
    printf("h = %d, w = %d\n", img->h, img->w);
    free(img);
    return 0;
}
*/
