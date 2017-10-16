#define IN 2
#define OUT 1
#define HID 4


#define M 0.1f
#define N 0.1f

#include "math.h"
#include <stdio.h>
#include <stdlib.h>
#include "personal_math_functions.h"
#include "XOR_propre.h"
#include "network_value_calculus.h"

#include "network_transformations.h"

void FeedForward(Layer layers[])
{
	for (size_t l = 1; l < 3; l++)
	{
		for (size_t j = 0; j < layers[l].length; j++)
		{
			layers[l].z[j] = Get_z(layers, l, j);
			layers[l].a[j] = Sigmoid(layers[l].z[j]);
		}
	}
}
void Backward_propagation(Layer layers[], double *y)
{
	double dL[layers[2].length];
	Init_arr_deltaL(dL, y, layers[2]); 
	
	double dl[layers[1].length];
	Init_arr_deltal(dl, dL, layers[2], layers[1]);
	
	// change w and b
	Update_bw(layers[1], layers[2], dL);
	Update_bw(layers[0], layers[1], dl);
}
// will change in the future
void Init_feedforward(Layer layer_input, double *inputs)
{
	layer_input.a = inputs;
}
// will change in the future
void Learning(Layer layers[3], size_t number_of_lessons, double *inputs, double *y)
{
	for (size_t i = 0; i < number_of_lessons; i++)
	{
		Init_feedforward(layers[0], inputs);
		FeedForward(layers);
		Backward_propagation(layers, y);
	}
}


