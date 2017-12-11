#include <stdlib.h>
#include <stdio.h>

#include "XOR_propre.h"

double randouble(void){
	int randed = rand();
	double ans = ((double)(randed)) / ((double)(RAND_MAX));
	
	return (randed % 2 == 1) ? ans : -ans;
}

void Init_wb(double* ws, double *bs, size_t layerLength, size_t prevLayerLength){
	for (size_t j = 0; j < layerLength; j++){
		for (size_t i = 0; i < prevLayerLength; i++){
			ws[j*prevLayerLength + i] = randouble();
		}
		bs[j] = randouble();
	}
}

void save_layer(Layer *layer, size_t prevLayerLength, char* filename){
	printf("\nlayer->length = %lu", layer->length);
	printf("\nprevLayerLength = %lu", prevLayerLength);
	FILE *savefile = fopen(filename, "w");
	fprintf(savefile, "%lu\n", prevLayerLength);
	fprintf(savefile, "%lu\n", layer->length);

	for (size_t j = 0; j < layer->length; j++){
		for (size_t i = 0; i < prevLayerLength; i++){
			printf("\nSAVE : j = %lu / i = %lu / pointer = %p\n", j, i, layer->w + prevLayerLength*j + i);
			fprintf(savefile, "%le\n", *(layer->w + prevLayerLength*j + i));
		}
	}
	
	for (size_t k = 0; k < layer->length; k++){		
		fprintf(savefile, "%le\n", *(layer->b + k));
	}
	
	fclose(savefile);
}

Layer *load_layer(char* filename, size_t lengthOfPreviousLayer, size_t lengthForNewLayer){
	
	FILE *loadfile = fopen(filename, "r");
	double *ws;
	double *bs;
	Layer *layer = malloc(sizeof(Layer));
	
	if (loadfile == NULL){
		ws = malloc(lengthOfPreviousLayer*lengthForNewLayer * sizeof(double));
		bs = malloc(lengthForNewLayer * sizeof(double));
		
		layer->length = lengthForNewLayer;
		
		Init_wb(ws, bs, lengthForNewLayer, lengthOfPreviousLayer);
	}
	else{
		size_t prevLayerLength = 0;
		size_t length = 0;
		fscanf(loadfile, "%lu", &prevLayerLength);
		fscanf(loadfile, "%lu", &length);

		ws = malloc(length*prevLayerLength * sizeof(double));
		bs = malloc(length * sizeof(double));
		for (size_t j = 0; j < length; j++){
			for (size_t i = 0; i < prevLayerLength; i++){
				fscanf(loadfile, "%le", ws + j*prevLayerLength + i);
				printf("\nLOAD j = %lu / i = %lu / pointer = %p / affected = %le\n",
								j, i, ws + j*prevLayerLength + i, *(ws + j*prevLayerLength + i));
			}
		}

		for (size_t k = 0; k < length; k++){		
			fscanf(loadfile, "%le", bs + k);
			printf("\nk = %lu / pointer = %p / affected = %le\n", k, bs + k, *(bs + k));
		}
		layer->length = length;
		
		fclose(loadfile);
	}	
	
	layer->w = ws;
	layer->b = bs;
	layer->z = malloc(layer->length * sizeof(double));
	layer->a = malloc(layer->length * sizeof(double));
	
	return layer;
}

void free_layer(Layer *layer){
	
	free(layer->w);
	free(layer->b);
	free(layer->z);
	free(layer->a);
	free(layer);	
}

