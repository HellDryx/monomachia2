#define IN 2
#define OUT 1
#define HID 4


#define M 0.1f
#define N 0.1f

#include "math.h"
#include <stdio.h>
#include <stdlib.h>

#include "personal_math_functions.h"

double Exp(double x)
{ 
	return exp(x);
}
double* Han(double *A, double *B, size_t length, double *new_matrice)
{
	for (size_t i = 0; i < length; i++)
	{
		new_matrice[i] = A[i] * B[i];
	}
	
	return new_matrice;
}
double Sigmoid(double z)
{
	return 1.0d / (1.0d + Exp(-z));
}
double Sigmoid_prime(double z)
{
	return (Exp(-z) / (1.0d + Exp(-z)) * (1.0d + Exp(-z)));
}
