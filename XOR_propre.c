#define IN 2
#define OUT 1
#define HID 4

#define M 0.1f
#define N 0.1f

#include "math.h"
#include <stdio.h>


// STRUCTURES ##########################################################
typedef struct
{
	// pointer of array of length : length * (previous_layer * length)
	float *w;
	
	// pointers of arrays of length : length
	float *b;
	float *z;
	float *a;
	
	// number of neuron in the layer
	int length;
	
}Layer;

typedef struct
{
	Layer layers[3];
	
}Network;

// personal includes
#include "personal_math_functions.h"
#include "network_value_calculus.h"
#include "network_transformations.h"

int main()
{
	
	
	return 0;
}


