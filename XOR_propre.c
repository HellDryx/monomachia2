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
#include "network_test.h"


// STRUCTURES ##########################################################

// personal includes
/*
#include "personal_math_functions.h"
#include "network_value_calculus.h"
#include "network_transformations.h"
#include "network_test.h"
*/


int main()
{
	Layer layers[3];
	double *y;
	double *inputs;
	
	//double x = (double)layers[0].length;
	//printf("%.1f", Exp(x));
	
	Init_layer_array(layers);
	Init_input(y, inputs); 
	Init_wb(layers);
	Print_input(layers[0]);
	Print_network(layers);
	
	return 0;
}

