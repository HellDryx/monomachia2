

#define M 10
#define N 00.1

#include "math.h"
#include <stdio.h>
#include <stdlib.h>
#include "personal_math_functions.h"
#include "XOR_propre.h"

#include "network_value_calculus.h"

double Get_z(Layer layers[], size_t l, size_t j)
{
	/* layers : the list of layers in the network 
	 * l : layer iteration in the array layers
	 * j : neuron iteration in the layer 
	 * 
	 * Formula : Z = Sigma(Ai * Wi) + B
	 */
	
	size_t iteration = (layers[l-1].length * j);
	//size_t iteration = (layers[l].length * j);
	
	double ans = layers[l].b[j];
	
	for (size_t i = 0; i < layers[l-1].length; i++)
		ans += layers[l].w[iteration + i] * layers[l-1].a[i];
	
	return ans;
}
double Get_deltaL(double y, double a, double z)
{
	return (a - y) * Sigmoid_prime(z);
}
double* Init_arr_deltaL(double *arr_deltaL, double y, Layer layer_out)
{
	/* *arr_deltaL : an already created array where the result will be put
	 * *y : a list of the output awaited from the network 
	 * layer : the output layer
	 */
	
	for (size_t i = 0; i < layer_out.length; i++)
		arr_deltaL[i] = Get_deltaL(y, layer_out.a[i], layer_out.z[i]); 
	
	return arr_deltaL;
}
// not used anymore + ancienne erreur ici 
double Get_deltal(double *deltaL, double *w, size_t length, size_t previous_layer_length, size_t j, double z)
{
	/* deltaL : the delta of the next layer (l+1)
	 * *w : the weight array of the next layer (l+1)
	 * length : the length the next layer (l+1)
	 * j : the current neuron analysed
	 * z : the z value of the j neuron in the current layer (l)
	 * 
	 * ICI
	 * deltal = Sigma(w[i * length] * deltaL[i]) * Sigmoid_prime(z) 
	 */
	
	double ans = 0.0f;
	//size_t iteration = length * j;
	
	for (size_t i = 0; i < length; i++)
		ans += w[i * previous_layer_length + j] * deltaL[i];
		//ans += w[i * length + j] * deltaL[i];
	
	ans *= Sigmoid_prime(z);
		
	return ans;
}
double* Init_arr_deltal(double *arr_deltal, double *arr_deltaL, Layer layer_out, Layer layer_hid)
{
	/*
	for (size_t j = 0; j < layer_out.length; j++)
	{
		double ans = 0.0f;
		
		//for (size_t i = 0; i < layer_hid.length; i++)
			//ans += w[i * layer_hid.length + j] * deltaL[i];
		for (size_t i = 0; i < layer_hid
		
		ans *= Sigmoid_prime(z);
		
		arr_deltal[j] = ans;
	}
	* */
	double ans;
	
	for (size_t j1 = 0; j1 < layer_hid.length; j1++)
	{
		ans = 0.0d;
		
		for (size_t j2; j2 < layer_out.length; j2++)
			ans += layer_out.w[j2 * layer_out.length + j1] * arr_deltaL[j2];
			
		ans *= Sigmoid_prime(layer_hid.z[j1]);
		
		arr_deltal[j1] = ans;
	}
		
	return arr_deltal;
}

void Set_new_arr_b(double *b, size_t length, double deltal[])
{
	/* *b : the posize_ter to the array of biais in the layer l 
	 * length : the length of the array b
	 * deltal : the delta array of the layer l 
	 * 
	 * Formula : b = b - (N * deltal)
	 */
	
	for (size_t j = 0; j < length; j++)
		b[j] -= N * deltal[j];
}
void Set_new_arr_w(double *w, size_t length, double deltal[], double *a, size_t previous_layer_length)
{
	/* *w : the pointer to the array of w from the layer l
	 * length : the number of neuron of the layer l
	 * deltal[] : the deltal array of the layer l
	 * *a : the posize_ter to the array of a from the layer l-1
	 * previous_layer_length : the length of a
	 * 
	 */ 
	
	for (size_t j = 0; j < length; j++)
	{
		size_t iteration = j * previous_layer_length;
	
		for (size_t k = 0; k < previous_layer_length; k++)
			w[iteration + k] -= N * a[k] * deltal[j];
	}
}
void Update_bw(Layer layer1, Layer layer2, double dl[])
{
	Set_new_arr_b(layer2.b, layer2.length, dl);
	Set_new_arr_w(layer2.w, layer2.length, dl, layer1.a, layer1.length);
}
