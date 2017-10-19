#define IN 2
#define OUT 1
#define HID 2

#include "math.h"
#include <stdio.h>
#include <stdlib.h>
#include "personal_math_functions.h"
#include "XOR_propre.h"
#include "network_value_calculus.h"
#include "network_transformations.h"
#include "printing_functions.h"


double a0[IN], a1[HID], a2[OUT]; 
double z1[HID], z2[OUT]; 
double b1[HID], b2[OUT]; 
double w1[IN * HID], w2[HID * OUT]; 

double inputs2[8] = {0, 0, 0, 1, 1, 0, 1, 1};
double y2[4]  = {0, 1, 1, 0};

// will change in the future
void Init_inputs(INPUTS inputs)
{
	inputs.y = y2;
	inputs.inputs = inputs2;
}
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

void Init_network(Layer layers[], INPUTS inputs)
{
	Init_layer_array(layers);
	Init_inputs(inputs); 
	Init_wb(layers);
	
	//printf("%.2g", inputs.y[1]);
	
}


int main()
{
	// init
	Layer layers[3];
	layers[0].a = a0; layers[0].length = IN;
	layers[1].z = z1; layers[1].a = a1; layers[1].b = b1; layers[1].w = w1; layers[1].length = HID;
	layers[2].z = z2; layers[2].a = a2; layers[2].b = b2; layers[2].w = w2; layers[2].length = OUT;
	
	INPUTS inputs;
	inputs.current_iteration = 0;
	inputs.y = y2;
	inputs.inputs = inputs2;
	
	Init_wb(layers);
	
	// tests
	Learning(layers, 2, inputs, inputs.y);
	
	// learning
	//Learning(layers, 1000, inputs, inputs.y);
	
	// final test
	/*
	inputs.current_iteration = 0;
	printf("\nFinal Test\n");
	Learning(layers, 4, inputs, inputs.y);
	//*/
	return 0;
}

