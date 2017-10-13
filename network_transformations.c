
#include "network_transformations.h"

void FeedForward(Layer layers[])
{
	for (int l = 1; l < 3; l++)
	{
		for (int j = 0; j < layers[l].length; j++)
		{
			layers[l].z[j] = Get_z(layers, l, j);
			layers[l].a[j] = Sigmoid(layers[l].z[j]);
		}
	}
}
void Backward_propagation(Layer layers[], float *y)
{
	float dL[layers[2].length];
	Init_arr_deltaL(dL, y, layers[2]); 
	
	float dl[layers[1].length];
	Init_arr_deltal(dl, dL, layers[2], layers[1]);
	
	// change w and b
	Update_bw(layers[1], layers[2], dL);
	Update_bw(layers[0], layers[1], dl);
}
