
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
#include "matrix_creation.h"
#include "XOR_propre.h"

/*
struct sdlist{
    struct sdlist* next;
    SDL_Surface* surface;
};

static inline
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

SDL_Surface* load_(char *path){

    SDL_Surface *img = NULL;
    img = IMG_Load(path);

    if (img == NULL)
        errx(3, "can't load %s: %s", path, IMG_GetError());

    return img;
}

SDL_Surface* load_image(char *path) {
  SDL_Surface          *img;
  img = IMG_Load(path);
  if (!img)
    errx(3, "can't load %s: %s", path, IMG_GetError());
  return img;
}

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
    printf("apres truc bizare\n");//##################
    partition = SDL_CreateRGBSurface(0, width, height, 32,
                                     rmask, gmask, bmask, amask);
    printf("apres tres triste 2\n");//##################
    //Partition
    for (int i = 0; i < partition->w; i++)
    {
        for (int j = 0; j < partition->h; j++)
        {
            putpixel(partition, i, j, getpixel(image, padding_left + i,
                                               padding_top + j));
        }
    }
    printf("apres forfor\n");//##################
    //if display == 1 then display partition before return
    if (display)
    {
        display_image(partition);
    }
    printf("fin\n");//##################
    return partition;
}
*/
size_t mystrlen(char *s) {
  size_t len = 0;

  while (*(s + len) != '\0')
  {
      len++;
  }

  return len;
}

char* concat(char* s1, char* s2){
    size_t len1 = mystrlen(s1);
    size_t len2 = mystrlen(s2);

    char* result = malloc((mystrlen(s1)+mystrlen(s2)+1) * sizeof(char));

    for (size_t i = 0; i < len1; i++)
    {
        *(result + i) = *(s1 + i);
    }

    for (size_t i = 0; i < len2; i++)
    {
        *(result + len1  + i) = *(s2 + i);
    }

    *(result + len1 + len2) = '\0';

    return result;
}

char* concatChar(char* s1, char c){
    size_t len1 = mystrlen(s1);

    char* result = malloc((mystrlen(s1) + 1) * sizeof(char));

    for (size_t i = 0; i < len1; i++)
    {
        *(result + i) = *(s1 + i);
    }

    *(result + len1) = c;

    *(result + len1 + 1) = '\0';

    return result;
}

int power10(int n){
    int res = 1;

    for (int i = 0; i < n; i++)
    {
        res *= 10;
    }
     return res;
}

char* int2str(int n){//uses power10
    int ncopy = n;
    int nbdigit = 0;

    while (ncopy > 0)
    {
        nbdigit++;
        ncopy = ncopy / 10;
    }

    printf("nb digit : %i\n\n", nbdigit);

    char *result = malloc(nbdigit * sizeof(char) + 1);

    for (int i = nbdigit; i > 0; i--)
    {
        *(result - i + nbdigit) = (char)(48+((n / power10(i-1))%10));
    }

    *(result + nbdigit + 1) = '\0';

    return result;
}



int* propagation(SDL_Surface* img, int boolmat[], int height, int width, int x, int y){
    Uint8 r;
    Uint8 g;
    Uint8 b;

    Uint32 p;

    boolmat[x + y * width] = 1;
    int col = x - 1;
    for(int i = y - 1; i < y + 2; i++){
        for(int j = col; j < x + 2; j++){
            if(i > -1 && i < height && j > -1 && j < width){
                if(i != y || j != x){
                    p = getpixel(img, j, i);
                    SDL_GetRGB(p, img->format, &r, &g, &b);
                    if(r < 127 && boolmat[j + i * width] == 0){
                        boolmat = propagation(img, boolmat, height, width, j, i);
                    }
                }
            }
        }
    }
    return boolmat;
}

struct sdlist* segmentChar(struct sdlist* list, SDL_Surface* img, int beginx){
    //printf("\ndebut segmentchar %d\n", 1);//================
    list->next = NULL;
    //printf("\nlist = %p\n", list);
    //list->surface = malloc(sizeof(SDL_Surface));
    int height = img->h;
    int width = img->w;
    /*premier pixel noir(colonne)*/
    int count = 0;
    int x = beginx;
    int y = 0;
    Uint8 r;
    Uint8 g;
    Uint8 b;

    Uint32 p;
    //printf("\nfin inti(segmentChar) %d\n", 1);//================
    while(count == 0 && x < width){
        y = 0;
        while(count == 0 && y < height){
            p = getpixel(img, x, y);
            SDL_GetRGB(p, img->format, &r, &g, &b);
            count += r < 127;
            y++;
        }
        x++;
    }
    if(x == width){
        return NULL;
    }
    /*init matrice booléen*/
    int matsize = height * width;
    //printf("\nmatsize = %d\n", matsize);//===============
    int *boolmat = malloc(matsize * sizeof(int));

    //printf("\n fin malloc1 matsize = %d/beginx = %d/width = %d\n", matsize, beginx, width);//===============
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            //printf("\nj = %d; j + i * width - beginx = %d\n", j, j + i * (width - beginx));//=============
            boolmat[j + i * width] = 0;
        }
    }
       /*propagation*/
    boolmat = propagation(img, boolmat, height, width, x, y);

    int f = 0;
    int padleft = 0;
    while(f == 0 && padleft < width){
        int oui = 0;
        while(oui < height){
            f += boolmat[padleft + oui * width];
            oui++;
        }
        padleft++;
    }

    int n = 1;
    int c = padleft;
    //printf("\n c = %d n = %d width = %d\n", c, n, width);//===================================
    while(n != 0 && c < width){
        int l = 0;
        n = 0;
        //printf("\nc = %d\n", c);//===================
        while(l < height){
            n += boolmat[c + l * width];
            //printf("\nl = %d, n = %d\n", l, n);//===================
            l++;
        }
        c++;
    }

    list->surface = image_partition(img, beginx, 0, c - 2 - padleft, height - 1, 0);
    if(c < width){
        list->next = malloc(sizeof(struct sdlist));
        list->next = segmentChar(list->next, img, c);
    }
    return list;
}


int detectLine(SDL_Surface* img, int i, int height, int width){
    Uint8 r;
    Uint8 g;
    Uint8 b;

    Uint32 p;

    for (int y = i; y < height; y++)
    {
        //printf("y = %d\n", y);//################
        int count = 0;
        for(int x = 0; x < width; x++)
        {

            p = getpixel(img, x, y);
            SDL_GetRGB(p, img->format, &r, &g, &b);
            if (r < 127)
            {
                count += 1;
                //printf("x = %d / black pixel detected\n\n", x);//#######
                break;
            }
        }
        if (count == 0)
        {
            //printf("line detected\n");
            return y;
        }
    }

    return -1;

}

int detectChar(SDL_Surface* img, int j, int height, int width){

    Uint8 r;
    Uint8 g;
    Uint8 b;

    Uint32 p;

    for (int x = j; x < width; x++)
    {
        int count = 0;
        for(int y = 0; y < height; y++)
        {
            p = getpixel(img, x, y);
            SDL_GetRGB(p, img->format, &r, &g, &b);
            if (r < 127)
            {
                count += 1;
            }
        }
        if (count == 0)
        {
            return x;
        }
    }
    return -1;
}

void write_in_file(char* str, int *beginWord, int *beginPar){

  FILE *f = fopen("RetourOCR.txt", "a");
  if(f == NULL){
    errx(1, "retourOCR = NUL");
  }

  if(*beginWord != 0){
    fprintf(f, " ");
    *beginWord = 0;
  }
  if(*beginPar != 0){
    fprintf(f, "\n\n");
    *beginPar = 0;
  }

  fprintf(f, "%c", str);

  fclose(f);
}


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


void segmentLine(SDL_Surface* img, int *beginPar){

    int height = img->h;
    int width = img->w;

    Uint8 r;
    Uint8 g;
    Uint8 b;

    Uint32 p;
    int endChar;
    int beginWord = 0;
    int charCount = 0;
    int tresholdSpace = 9999;

    for(int j = 0; j < width; j++)
    {
        for(int i = 0; i < height; i++)
        {
            p = getpixel(img, j, i);
            SDL_GetRGB(p, img->format, &r, &g, &b);
            if (r < 127)
            {
                int beginChar = j;

                if(charCount){
                    int space = beginChar - endChar;
                    if(space < 0 || space < tresholdSpace){
                        beginWord = 0;
                    }
                    else{
                        beginWord = 1;
                    }
                }

                endChar = detectChar(img, beginChar, height, width);

                charCount = 1;
                int charWidth = endChar - beginChar;
                tresholdSpace = charWidth < tresholdSpace ? charWidth : tresholdSpace;

                SDL_Surface* charIMG = image_partition(img, beginChar,
                                    0, endChar - beginChar, height, 0);
                struct sdlist* imglist = malloc(sizeof(struct sdlist));
                imglist = segmentChar(imglist, charIMG, 0);
                char ans;
                if(imglist->next == NULL){
                    //display_image(charIMG);
                    charIMG = resize_float(charIMG);
                    SDL_SaveBMP(charIMG, "currentChar.bmp");
                    // Call NN !!
                    ans = Init_lauch_ocr();
                    char* retRNA = (char)ans;
                    write_in_file(retRNA, &beginWord, beginPar);
                    printf("\n%c\n", ans);
                }
                else{
                    while(imglist != NULL){

                        //display_image(imglist->surface);
                        imglist->surface = resize_float(imglist->surface);
                        SDL_SaveBMP(imglist->surface, "currentChar.bmp");
                        // Call NN !!
                        ans = Run_ocr();
                        char* retRNA = (char)ans;
                        write_in_file(retRNA, &beginWord, beginPar);
                        imglist = imglist->next;
                    }
                }


                j = endChar;
            }

        }
    }
}

void cutIMG(SDL_Surface* img){

    int height = img->h;
    int width = img->w;

    Uint8 r;
    Uint8 g;
    Uint8 b;

    Uint32 p;
    int endLine;
    int tresholdPar = 9999;
    int lineCount = 0;
    int beginPar = 0;

    for(int i = 0; i < height; i++)
    {
        //printf("i = %d\n", i);//###########################

        for(int j = 0; j < width; j++)
        {
            //printf("j = %d\n", j);//###################
            p = getpixel(img, j, i);
            SDL_GetRGB(p, img->format, &r, &g, &b);
            if (r < 127)
            {
                //printf("start detecting the line \n");
                int beginLine = i;
                if(lineCount){
                    int space = beginLine - endLine;
                    if(space > tresholdPar){
                        beginPar = 1;
                    }
                    else{
                        beginPar = 0;
                    }
                }
                endLine = detectLine(img, beginLine, height, width);

                lineCount += 1;
                if (endLine == -1)
                {
                    errx(2, "error: detectLine() did not found the end\
                     of the line (number %d)", lineCount);
                }

                int spaceBPar = endLine - beginLine;
                tresholdPar = tresholdPar > spaceBPar ? spaceBPar : tresholdPar;

                SDL_Surface *imgline = image_partition(img, 0,
                            beginLine, width, endLine - beginLine, 0);

                segmentLine(imgline, &beginPar);
                i = endLine;
            }
        }
    }

}

void binarization(SDL_Surface* image)
{
    Uint32 pixel = 0;
    Uint8 r = 0;
    Uint8 g = 0;
    Uint8 b = 0;
    Uint8 grayscale = 0;
    Uint32 newpixel = 0;

    for (int i = 0; i < image->w; i++)
    {
        for (int j = 0; j < image->h; j++)
        {
            pixel = getpixel(image,i,j);

            SDL_GetRGB(pixel,image->format,&r,&g,&b);

            grayscale = (Uint8)(0.3f*r + 0.59f*g + 0.11*b);

            newpixel = SDL_MapRGB(image->format, grayscale, grayscale,
                                    grayscale);

            putpixel(image, i, j, newpixel);
        }
    }

    //display_image(image);

    Uint8 threshold = 127;
    Uint8 blackwhite = 0;

    for (int i = 0; i < image->w; i++)
    {
        for (int j = 0; j < image->h; j++)
        {
            pixel = getpixel(image,i,j);

            SDL_GetRGB(pixel,image->format,&r,&g,&b);

            blackwhite = (r > threshold ? 255 : 0);

            newpixel = SDL_MapRGB(image->format, blackwhite, blackwhite,
                                    blackwhite);

            putpixel(image, i, j, newpixel);
        }
    }
}

int main(int argc, char *argv[]){

    if(argc < 2)
    {
      errx(1, "nombre d'arguments trop faible");
    }
    char a = Init_lauch_ocr();
    FILE *f = fopen("RetourOCR.txt", "w");
    fclose(f);

    init_sdl();

    SDL_Surface* img = load_image(argv[1]);
    binarization(img);
    cutIMG(img);

    return 0;
}








