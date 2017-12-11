#define IN 32*32
#define OUT 62
#define HID 42
#define filename_layer1 "layers_save/file_layer1.txt"
#define filename_layer2 "layers_save/file_layer2.txt"
#define filename_letter "/.bmp"

#include "math.h"
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include "XOR_propre.h"
#include "network_transformations.h"
#include "matrix_creation.h"
#include "Save.h"


char Int_to_char(size_t i)
{
  if (i < 10)
    return '0' + i;
  else if (i < 36)
    return 'a' + (i - 10);
  else
    return 'A' + (i - 36);
}
char Get_result(Layer *layer_out)
{
  size_t best = 0;

  for (size_t i = 1; i < layer_out->length; i++)
  {
    if (layer_out->a[i] > layer_out->a[best])
      best = i;
  }

  return Int_to_char(best);
}
char Get_expected(double *y)
{
  size_t best = 0;

  for (size_t i = 1; i < 62; i++)
  {
    if (y[i] > y[best])
      best = i;
  }

  return Int_to_char(best);
}

void Memory_allocation(Layer **layers, Inputs *inputs)
{
    layers[0] = malloc(sizeof(Layer));
    layers[0]->length = IN;
    layers[0]->a = malloc(IN * sizeof(double));

    layers[1] = load_layer(filename_layer1, IN, HID);
    layers[2] = load_layer(filename_layer2, HID, OUT);

  // init memory for inputs
    inputs->y = malloc(62 * sizeof(double));
  inputs->pixels = malloc(32 * 32 * sizeof(double));
}

char Run_ocr(Layer **layers, double *image)
{
  layers[0]->a = image;
  FeedForward(layers);
  return Get_result(layers[2]);
}
char Init_lauch_ocr()
{
    Layer **layers = calloc(3, sizeof(Layer*));
    Inputs *inputs = malloc(sizeof(Inputs));

    // allocate memory for layers and inputs and set w and b
    Memory_allocation(layers, inputs);

  Set_matrix(filename_letter, inputs->pixels);

    // run
  return Run_ocr(layers, inputs->pixels);
}

void Make_suffix(char *url, size_t iteration, size_t i)
{
    short c = 0;
    url[c] = Int_to_char(iteration);
    c++;

    if (iteration >= 36)
    {
      url[c] = '!';
      c++;
    }

    url[c + 4] = '\0';

    size_t n = i / 62 + 1;
    char max = 4 + c/2;
    for (int o = 0; o < 4; o++)
    {
      url[max-o] = '0' + n%10;
      n = n/10;
    }
}
void Make_path(char *path, char *path_prefix, char *jpg, char *path_suffix)
{
  int i = 0;
  for (; *(path_prefix + i) != '\0'; i++){
    *(path + i) = *(path_prefix + i);
  }

  int o = 0;
  for (; *(path_suffix + o) != '\0'; o++){
    *(path + i + o) = *(path_suffix + o);
  }

  int u = 0;
  for (; *(jpg + u) != '\0'; u++){
    *(path + i + o + u) = *(jpg + u);
  }

  *(path + i + o + u) = '\0';
}
void Learning(Layer **layers, size_t number_of_lessons, Inputs *inputs)
{
  size_t iteration = 0;

  for (size_t o = 0; o < 62; o++){
      inputs->y[o] = 0.0;
  }

  /*if (number_of_lessons > 62992)
      number_of_lessons = 62992;*/

  size_t loop = number_of_lessons / 62992 + 1;
  size_t loopLessonN;

  char *path_prefix = "test_characters/";
  char *jpg = ".jpg";

  for (size_t k = 0; k < loop; k++)
  {
    loopLessonN = ((k + 1) * 62992 < number_of_lessons ? 62992 : (number_of_lessons % 62992));
    for (size_t i = 0; i < loopLessonN ; i++)
    {

      // build url
      char *path_suffix;
      path_suffix = (iteration < 36) ? malloc(6 * sizeof(char)) : malloc(7 * sizeof(char));
      Make_suffix(path_suffix, iteration, i);
      char *path = malloc(30 * sizeof(char));
      Make_path(path, path_prefix, jpg, path_suffix);

      // init pixels
      Set_matrix(path, inputs->pixels);
      // FREE URL
      free(path_suffix);
      free(path);

      // init y
      inputs->y[iteration] = 1.0;

      // learning
      One_step_learning(layers, inputs);

      printf("%lu : RESULT = %c EXPECTED = %c\n", k*62992 + i, Get_result(layers[2]), Get_expected(inputs->y));
      /*printf("\nnumber_of_lessons = %lu / loopLessonN = %lu / iteration = %lu / k = %lu",
              k*62992 + i, i, iteration, k);*/
      /*for (size_t i = 0; i < layers[2]->length; i++)
        printf("b = %lf \n", layers[2]->b[i]);
      printf("\n");*/

      inputs->y[iteration] = 0.0;
      iteration = (iteration + 1) % 62;
    }
  }
}
void Teach_ocr(size_t learning)
{
  Layer **layers = calloc(3, sizeof(Layer*));
    Inputs *inputs = malloc(sizeof(Inputs));

    // allocate memory for layers and inputs and set w and b
    Memory_allocation(layers, inputs);

    // learn
  Learning(layers, learning, inputs);

  // save biases and weight
  char a;
  printf("Sauvegarder les layers ? y/n ");
  scanf("%c" , &a);
  if (a == 'y')
  {
    save_layer(layers[1], layers[0]->length, filename_layer1);
    save_layer(layers[2], layers[1]->length, filename_layer2);
  }
}


/*int main()
{
  Teach_ocr(190000);

  return 0;
}*/

