#define IN 2
#define OUT 1
#define HID 2


#define M 0.1f
#define N 0.1f

#include "math.h"
#include <stdio.h>
#include <stdlib.h>
#include "personal_math_functions.h"
#include "XOR_propre.h"
#include "network_value_calculus.h"
#include "network_transformations.h"

#include "network_test.h"

void Init_input(double *y, double *inputs)
{
	static double inputs2[] = {0, 0, 0, 1, 1, 0, 1, 1};
	double y2[]  = {0, 1, 1, 0};
	y = y2;
	inputs = inputs2;
}

double a0[IN], a1[HID], a2[OUT]; 
double z1[HID], z2[OUT]; 
double b1[HID], b2[OUT]; 
double w1[IN * HID], w2[HID * OUT]; 

void Init_layer_array(Layer layers[3])
{
	layers[0].a = a0; layers[0].length = IN;
	layers[1].z = z1; layers[1].a = a1; layers[1].b = b1; layers[1].w = w1; layers[1].length = HID;
	layers[2].z = z2; layers[2].a = a2; layers[2].b = b2; layers[2].w = w2; layers[2].length = OUT;
}
void Init_wb(Layer layers[3])
{
	unsigned int seed = 0;
	
	for (size_t l = 1; l < 3; l++)
	{
		size_t length = layers[l].length;
		size_t length2 = layers[l-1].length;
		
		for (size_t i = 0; i < length; i++)
		{
			srand(seed);
			
			double b = (double)rand() / (double)RAND_MAX;
			layers[l].b[i] = b;
			
			seed++;
			
			for (size_t j = 0; j < length2; j++)
			{
				srand(seed);
				
				double w = (double)rand() / (double)RAND_MAX;
				layers[l].w[i * length + j] = w;
				
				seed++;
			}
			
		}
	}
}

void Print_network(Layer layers[3])
{
	for (int l = 1; l < 3; l++)
	{
		printf("\nLayer %d\n\n", l+1);
		Print_layer(layers[l], layers[l-1].length);
	}
}
void Print_layer(Layer layer, size_t previous_layer_length)
{
	size_t length = layer.length;
	
	for (size_t i = 0; i < length; i++)
		printf("b%d = %.3g\n", i, layer.b[i]);
	for (size_t i = 0; i < length; i++)
		for (size_t j = 0; j < previous_layer_length; j++)
			printf("w%d%d = %.3g\n", i, j, layer.w[i * length + j]);
	for (size_t i = 0; i < length; i++)
		printf("a%d = %.3g\n", i, layer.a[i]);
}
void Print_input(Layer layer_input)
{
	printf("\nLayer 1\n\n");
	
	for (size_t i = 0; i < layer_input.length; i++)
		printf("a%d = %.2g\n", i, layer_input.length);
}

