
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
	return (Sigmoid(z) / (1.0d - Sigmoid(z)));
}
