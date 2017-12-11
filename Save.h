#ifndef _SAVE_H_
#define _SAVE_H_

void save_layer(Layer *layer, size_t prevLayerLength, char* filename);
Layer *load_layer(char* filename, size_t lengthOfPreviousLayer, size_t lengthForNewLayer);
void free_layer(Layer *layer);

#endif
