#ifndef _PRINTING_FUNCTIONS_H_
#define _PRINTING_FUNCTIONS_H_

void Print_network(Layer layers[3]);
void Print_layer(Layer layer, size_t previous_layer_length);
void Print_input(Layer layer_input);

void Print_z(Layer layers[3]);
void Print_a(Layer layers[3]);
void Print_b(Layer layers[3]);
void Print_w(Layer layers[3]);

void Print_all_layer(Layer layers[3], int l);
void Print_all(Layer layers[3]);

void Print_delta(double *deltaL, double *deltal, size_t length, size_t length2);

#endif

