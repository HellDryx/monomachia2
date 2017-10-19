
#include <stdio.h>
#include <stdlib.h>
#include "XOR_propre.h"

#include "printing_functions.h"

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
		printf("a%d = %.2g\n", i, layer_input.a[i]);
}


void Print_z(Layer layers[3])
{
	for (int l = 1; l < 3; l++)
	{
		printf("\nLayer %d\n", l+1);
		
		for (size_t i = 0; i < layers[l].length; i++)
			printf("z%d = %.3g\n", i, layers[l].z[i]);
	}
}
void Print_a(Layer layers[3])
{
	for (int l = 1; l < 3; l++)
	{
		printf("\nLayer %d\n", l+1);
		
		for (size_t i = 0; i < layers[l].length; i++)
			printf("a%d = %.3g\n", i, layers[l].a[i]);
	}
}
void Print_b(Layer layers[3])
{
	for (int l = 1; l < 3; l++)
	{
		printf("\nLayer %d\n", l+1);
		
		for (size_t i = 0; i < layers[l].length; i++)
			printf("b%d = %.3g\n", i, layers[l].b[i]);
	}
}
void Print_w(Layer layers[3])
{
	for (int l = 1; l < 3; l++)
	{
		printf("\nLayer %d\n", l+1);
		
		size_t length = layers[l].length * layers[l-1].length;
		
		for (size_t i = 0; i < length; i++)
			printf("w%d = %.3g\n", i, layers[l].w[i]);
	}
}

void Print_all_layer(Layer layers[3], int l)
{
	size_t length = layers[l].length * layers[l-1].length;
	
	printf("\nLayer %d\n\n", l+1);	
	
	for (size_t i = 0; i < length; i++)
		printf("w%d = %.3g\n", i, layers[l].w[i]);
	printf("\n");
	for (size_t i = 0; i < layers[l].length; i++)
			printf("b%d = %.3g\n", i, layers[l].b[i]);
	printf("\n");
	for (size_t i = 0; i < layers[l].length; i++)
			printf("z%d = %.3g\n", i, layers[l].z[i]);
	printf("\n");
	for (size_t i = 0; i < layers[l].length; i++)
			printf("a%d = %.3g\n", i, layers[l].a[i]);
	printf("\n");		
}
void Print_all(Layer layers[3])
{
	for (int l = 1; l < 3; l++)
		Print_all_layer(layers, l);
}

void Print_delta(double *deltaL, double *deltal, size_t length, size_t length2)
{
	///*
	for (size_t i = 0; i < length2; i++)
		printf("delta l%d : %.3g\n", i, deltal[i]);
	
	printf("\n");	
	//*/
	for (size_t i = 0; i < length; i++)
		printf("delta L%d : %.3g\n", i, deltaL[i]);
		
	printf("\n");
}
