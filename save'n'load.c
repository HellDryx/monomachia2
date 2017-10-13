#define stringSize 1000


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <err.h>

#include "XOR_propre.h"

char* concat(char* s1, char* s2)
{	
	char* result = malloc(strlen(s1) + strlen(s2) + 1);
	
	strcat(result, s1);
	strcat(result, s2);
	s1 = result;	
	
	return s1;
}

Layer initLayer(float* weights, float* biases, int l)
{
	Layer newLayer;
	
	newLayer.w = weights;
	newLayer.b = biases;
	newLayer.z = NULL;
	newLayer.a = NULL;
	
	newLayer.length = l;
	
	return newLayer;
}

void serializeLayer(Layer layer, size_t lines, size_t cols, char* s)
{
	char[12] currentDoubleString;
	
	//Serialize weights
	for (size_t i = 0; i < lines; i++)
	{
		for (size_t j = 0; j < cols; j++)
		{
			sprintf(currentDoubleString, "(%d)", w[j + i * cols]);
			s = concat(s, currentDoubleString);
		}
	}
	
	s = concat(s, "\n");

	//Serialize biases
	for (size_t k = 0; k < lines; k++)
	{
		sprintf(currentDoubleString, "(%d)", b[k]);
		s = concat(s, currentDoubleString);
	}
	
	s = concat(s, "\n");
}

void saveNetwork(Network network, char* filename)
{
	s = "";
	
	//Add Input Layer neuron amount
	sprintf(s, "%i\n", network.layers[0].length);
	
	//Add Hidden Layer serialization
	serializeLayer(network.layers[1], network.layers[1].length,
				   network.layers[0].length, s);
				   
	//Add Output Layer serialization
	serializeLayer(network.layers[2], network.layers[2].length,
				   network.layers[1].length, s);
				   
	//Open savefile and write down serialized ANN
	FILE* file = fopen(filename, "w");
	fprintf(file, s);
}

Network loadNetwork(char* path)
{
	FILE* file = fopen(path, "r+");
	
	char currentString[stringSize];
	
	fgets(currentString, stringSize - 1, file); //Get InLayer size
	
	int inLayerSize = (int)currentString;
	
	while (currentString[i] != 'i')
	{
		nbNeuron1++;
		i++;
	}
	
	
}
