
#define N 0.1

#include "math.h"
#include <stdio.h>
#include <stdlib.h>
#include "XOR_propre.h"
#include "network_transformations.h"

double Sigmoid(double z)
{
    return 1.0 / (1.0 + exp(-z));
}
double Sigmoid_prime(double z)
{
    return (Sigmoid(z) * (1.0 - Sigmoid(z)));
}
double Get_z(Layer **layers, size_t l, size_t j)
{
    double ans = layers[l]->b[j];
    for (size_t i = 0; i < layers[l-1]->length; i++)
    {
        ans += layers[l]->w[j + i * layers[l]->length] * layers[l-1]->a[i];
    if (l == 3)
      printf("ans += w(%lf) * a(%lf) = %lf \n", layers[l]->w[j + i * layers[l]->length], layers[l-1]->a[i], layers[l]->w[j + i * layers[l]->length] * layers[l-1]->a[i]);
  }
  if (l == 3)
  {
    printf("b = %lf \n", layers[l]->b[j]);
    printf("ans = %lf \n", ans);
    char bin;
    scanf("%c", &bin);
  }

    return ans;
}


void FeedForward(Layer **layers)
{
  for (size_t l = 1; l < 3; l++)
    {
        for (size_t j = 0; j < layers[l]->length; j++)
        {
            layers[l]->z[j] = Get_z(layers, l, j);
            layers[l]->a[j] = Sigmoid(layers[l]->z[j]);
        }
    }
}
void Backward_propagation(Layer **layers, double *y)
{
  Layer *layer_out = layers[2];
  Layer *layer_hid = layers[1];
  Layer *layer_in = layers[0];

  // calcul du delta du layer d'output
  double dL[layer_out->length];

    for (size_t i = 0; i < layer_out->length; i++)
    {
        dL[i] = (y[i] - layer_out->a[i]) * Sigmoid_prime(layer_out->z[i]);
    //printf("(%lf - %lf) * %lf = %lf\n", y[i], layer_out->a[i], Sigmoid_prime(layer_out->z[i]), dL[i]);
  }
  // calcul du delta du layer caché
    double dl[layer_hid->length];

    for (size_t j1 = 0; j1 < layer_hid->length; j1++)
    {
        dl[j1] = 0.0;

        for (size_t j2 = 0; j2 < layer_out->length; j2++)
            dl[j1] += layer_out->w[j2 * layer_hid->length + j1] * dL[j2];

        dl[j1] *= Sigmoid_prime(layer_hid->z[j1]);
    }

    // change w and b

    // change w and b du layer_out
    for (size_t j = 0; j < layer_out->length; j++)
    layer_out->b[j] += N * dL[j];

  for (size_t j = 0; j < layer_out->length; j++)
  {
    for (size_t k = 0; k < layer_hid->length; k++)
      layer_out->w[k * layer_out->length + j] += N * layer_hid->a[k] * dL[j];
  }

    // change w and b du layer_hid
    for (size_t j = 0; j < layer_hid->length; j++)
    layer_hid->b[j] += N * dl[j];

    for (size_t j = 0; j < layer_hid->length; j++)
  {
    for (size_t k = 0; k < layer_in->length; k++)
      layer_hid->w[k * layer_hid->length + j] += N * layer_in->a[k] * dl[j];
  }

}
void One_step_learning(Layer **layers, Inputs *inputs)
{
  layers[0]->a = inputs->pixels;
    FeedForward(layers);

    Backward_propagation(layers, inputs->y);
}



