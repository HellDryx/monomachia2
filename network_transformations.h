#ifndef _NETWORK_TRANSFORMATIONS_H_
#define _NETWORK_TRANSFORMATIONS_H_

void FeedForward(Layer layers[]);
void Backward_propagation(Layer layers[], double *y);
// will change in the future
void Init_feedforward(Layer layer_input, double *inputs);
// will change in the future
void Learning(Layer layers[3], size_t number_of_lessons, double *inputs, double *y);

#endif

