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

double Get_z(Layer layers[], size_t l, size_t j)
{
	/* layers : the list of layers in the network 
	 * l : layer iteration in the array layers
	 * j : neuron iteration in the layer 
	 * 
	 * Formula : Z = Sigma(Ai * Wi) + B
	 */
	
	size_t iteration = (layers[l].length * j);
	
	double ans = layers[l].b[j];
	
	for (size_t i = 0; i < layers[l-1].length; i++)
		ans += layers[l].w[iteration + i] * layers[l-1].a[i];
	
	return ans;
}
double Get_deltaL(double y, double a, double z)
{
	return (a - y) * Sigmoid_prime(z);
}
double* Init_arr_deltaL(double *arr_deltaL, double *y, Layer layer_out)
{
	/* *arr_deltaL : an already created array where the result will be put
	 * *y : a list of the output awaited from the network 
	 * layer : the output layer
	 */
	
	for (size_t i = 0; i < layer_out.length; i++)
		arr_deltaL[i] = Get_deltaL(y[i], layer_out.a[i], layer_out.z[i]); 
	
	return arr_deltaL;
}
// ancienne erreur ici 
double Get_deltal(double *deltaL, double *w, size_t length, size_t j, double z)
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
		ans += w[i * length] * deltaL[i]; 
	
	ans *= Sigmoid_prime(z);
		
	return ans;
}
double* Init_arr_deltal(double *arr_deltal, double *arr_deltaL, Layer layer_out, Layer layer_hid)
{
	for (size_t j = 0; j < layer_out.length; j++)
		arr_deltal[j] = Get_deltal(arr_deltaL, layer_out.w, layer_out.length, j, layer_hid.z[j]);
		
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
	/* *w : the posize_ter to the array of w from the layer l
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
