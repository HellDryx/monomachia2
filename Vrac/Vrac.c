
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"


void init_sdl(void) {
  // Init only the video part
  if( SDL_Init(SDL_INIT_VIDEO)==-1 ) {
    // If it fails, die with an error message
    errx(1,"Could not initialize SDL: %s.\n", SDL_GetError());
  }
}

static inline
Uint8* pixelref(SDL_Surface *surf, unsigned x, unsigned y) {
  int bpp = surf->format->BytesPerPixel;
  return (Uint8*)surf->pixels + y * surf->pitch + x * bpp;
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

SDL_Surface* load_image(char *path) {
  SDL_Surface          *img;
  img = IMG_Load(path);
  if (!img)
    return NULL;
  return img;
}

int Set_matrix(char *url, double *mat)
{
	SDL_Surface *img;
	init_sdl();
  SDL_Surface* img = load_image(url);
  if (img == NULL)
		return 0;
		
  Set_matrix(img, mat);
	
	
  Uint8 r, g, b;
  int size = 32;
  for (Uint8 i = 0; i < size; i++)
  {
    for (Uint8 j = 0; j < size; j++)
    {
      Uint32 p = getpixel(img, i, j);
      SDL_GetRGB(p, img->format, &r, &g, &b);

      mat[j + i * size] = r < 127 ? 1.0 : 0.0;
    }
  }
  
  return 1;
}

int main(int argc, char **argv)
{
  int size = 32;
  double *mat = malloc(size * size * sizeof(double));
  init_sdl();
  SDL_Surface* img = load_image(argv[1]);
  Set_matrix(img, mat);

  for (Uint8 i = 0; i < size; i++)
  {
    for (Uint8 j = 0; j < size; j++)
      printf("%.0lf ", mat[j * size + i]);
    printf("\n");
  }

  return 0;
}
