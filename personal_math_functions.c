
#include "personal_math_functions.h"

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
