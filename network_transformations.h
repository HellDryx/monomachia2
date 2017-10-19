#ifndef _NETWORK_TRANSFORMATIONS_H_
#define _NETWORK_TRANSFORMATIONS_H_

void FeedForward(Layer layers[]);
void Backward_propagation(Layer layers[], double *y, size_t iteration_y);
// will change in the future
void Init_feedforward(Layer layer_input, INPUTS in);
// will change in the future
void Learning(Layer layers[3], size_t number_of_lessons, INPUTS inputs, double *y);

#endif

