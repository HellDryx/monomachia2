#ifndef _XOR_PROPRE_H_
#define _XOR_PROPRE_H_

typedef struct 
{
	// posize_ter of array of length : length * (previous_layer * length)
	double *w;
	
	// posize_ters of arrays of length : length
	double *b;
	double *z;
	double *a;
	
	// number of neuron in the layer
	size_t length;
	
}Layer;


typedef struct
{
	double *y;
	double *pixels;
}Inputs;

char Init_launch_ocr();

#endif
