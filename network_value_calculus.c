
#include "network_value_calculus.h"

float Get_z(Layer layers[], int l, int j)
{
	/* layers : the list of layers in the network 
	 * l : layer iteration in the array layers
	 * j : neuron iteration in the layer 
	 * 
	 * Formula : Z = Sigma(Ai * Wi) + B
	 */
	
	int iteration = (layers[l].length * j);
	
	float ans = layers[l].b[j];
	
	for (int i = 0; i < layers[l-1].length; i++)
		ans += layers[l].w[iteration + i] * layers[l-1].a[i];
	
	return ans;
}
float Get_deltaL(float y, float a, float z)
{
	return (a - y) * Sigmoid_prime(z);
}
float* Init_arr_deltaL(float *arr_deltaL, float *y, Layer layer_out)
{
	/* *arr_deltaL : an already created array where the result will be put
	 * *y : a list of the output awaited from the network 
	 * layer : the output layer
	 */
	
	for (int i = 0; i < layer_out.length; i++)
		arr_deltaL[i] = Get_deltaL(y[i], layer_out.a[i], layer_out.z[i]); 
	
	return arr_deltaL;
}
// ancienne erreur ici 
float Get_deltal(float *deltaL, float *w, int length, int j, float z)
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
	
	float ans = 0.0f;
	//int iteration = length * j;
	
	for (int i = 0; i < length; i++)
		ans += w[i * length] * deltaL[i]; 
	
	ans *= Sigmoid_prime(z);
		
	return ans;
}
float* Init_arr_deltal(float *arr_deltal, float *arr_deltaL, Layer layer_out, Layer layer_hid)
{
	for (int j = 0; j < layer_out.length; j++)
		arr_deltal[j] = Get_deltal(arr_deltaL, layer_out.w, layer_out.length, j, layer_hid.z[j]);
		
	return arr_deltal;
}

void Set_new_arr_b(float *b, size_t length, float deltal[])
{
	/* *b : the pointer to the array of biais in the layer l 
	 * length : the length of the array b
	 * deltal : the delta array of the layer l 
	 * 
	 * Formula : b = b - (N * deltal)
	 */
	
	for (size_t j = 0; j < length; j++)
		b[j] -= N * deltal[j];
}
void Set_new_arr_w(float *w, size_t length, float deltal[], float *a, size_t previous_layer_length)
{
	/* *w : the pointer to the array of w from the layer l
	 * length : the number of neuron of the layer l
	 * deltal[] : the deltal array of the layer l
	 * *a : the pointer to the array of a from the layer l-1
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
void Update_bw(Layer layer1, Layer layer2, float dl[])
{
	Set_new_arr_b(layer2.b, layer2.length, dl);
	Set_new_arr_w(layer2.w, layer2.length, dl, layer1.a, layer1.length);
}
