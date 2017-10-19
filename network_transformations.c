
#include "math.h"
#include <stdio.h>
#include <stdlib.h>
#include "personal_math_functions.h"
#include "XOR_propre.h"
#include "network_value_calculus.h"
#include "printing_functions.h"

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
void Backward_propagation(Layer layers[], double *y, size_t iteration_y)
{
	double dL[layers[2].length];
	Init_arr_deltaL(dL, y[iteration_y], layers[2]); 
	
	double dl[layers[1].length];
	Init_arr_deltal(dl, dL, layers[2], layers[1]);
	
	//Print_delta(dL, dl, layers[2].length, layers[1].length);
	
	// change w and b
	Update_bw(layers[1], layers[2], dL);
	Update_bw(layers[0], layers[1], dl);
}
// will change in the future
void Init_feedforward(Layer layer_input, INPUTS in)
{
	for (size_t i = 0; i < layer_input.length; i++)
		layer_input.a[i] = in.inputs[in.current_iteration * layer_input.length + i]; 
}
// will change in the future
void Learning(Layer layers[3], size_t number_of_lessons, INPUTS inputs, double *y)
{
	for (size_t i = 0; i < number_of_lessons; i++)
	{
		Init_feedforward(layers[0], inputs);
		FeedForward(layers);
		// display feed forward results 
		printf("\nNew Iteration !\n");
		Print_input(layers[0]);
		Print_all(layers);
		
		Backward_propagation(layers, y, inputs.current_iteration);
		// display back prop result inside the back prop function
		
		printf("%.0g xor %.0g -> %.3g\n", layers[0].a[0], layers[0].a[1], layers[2].a[0]);
		
		inputs.current_iteration = (inputs.current_iteration + 1) % 4;
	}
}


