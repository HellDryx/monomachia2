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
	Layer layers[3];
	
}Network;

typedef struct
{
	double *y;
	double *inputs;
	size_t length;
	size_t current_iteration;
}INPUTS;

void Init_input(INPUTS inputs);
void Init_layer_array(Layer layers[3]);
void Init_wb(Layer layers[3]);
void Init_network(Layer layers[3], INPUTS inputs);


#endif
