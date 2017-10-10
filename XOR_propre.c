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

// MATH FUNCTION #######################################################
double Exp(double x)
{ 
	return exp(0.1d);
}
float* Han(float *A, float *B, int length, float *new_matrice)
{
	for (int i = 0; i < length; i++)
	{
		new_matrice[i] = A[i] * B[i];
	}
	
	return new_matrice;
}
float Sigmoid(float z)
{
	return 1.0f / (1.0f + Exp(-z));
}
float Sigmoid_prime(float z)
{
	return (Exp(-z) / (1.0f + Exp(-z)) * (1.0f + Exp(-z)));
}

// NETWORK VALUE CALCULUS ############################################## 
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
float Get_deltal(float *deltaL, float *w, int length, int j, float z)
{
	/* deltaL : the delta of the next layer (l+1)
	 * *w : the weight array of the next layer (l+1)
	 * length : the length the next layer (l+1)
	 * j : the current neuron analysed
	 * z : the z value of the j neuron in the current layer (l)
	 * 
	 * deltal = Sigma((wi * deltaLi) * Sigmoid_prime(z)) 
	 */
	
	float ans = 0.0f;
	int iteration = length * j;
	float sigDeriv_z = Sigmoid_prime(z);
	
	for (int i = 0; i < length; i++)
		ans += w[iteration + i] * deltaL[i] * sigDeriv_z; 
		
	return ans;
}
float* Init_arr_deltal(float *arr_deltal, float *arr_deltaL, Layer layer_out, Layer layer_hid)
{
	for (int j = 0; j < layer_out.length; j++)
		arr_deltal[j] = Get_deltal(arr_deltaL, layer_out.w, layer_out.length, j, layer_hid.z[j]);
		
	return arr_deltal;
}

void Get_new_b(float *b)
{
	
}
void Set_new_w(float *w, int j)
{
	
}
void Update_bw(Layer layer1, Layer layer2, float dl[])
{
	
}

// NETWORK MANIPULATION ################################################
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


int main()
{
	
	
	return 0;
}


