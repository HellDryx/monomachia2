#ifndef NETWORK_TEST_H
#define NETWORK_TEST_H

void Init_input(double *y, double *inputs);
void Init_layer_array(Layer layers[3]);
void Init_wb(Layer layers[3]);
void Print_network(Layer layers[3]);
void Print_layer(Layer layer, size_t previous_layer_length);

#endif
