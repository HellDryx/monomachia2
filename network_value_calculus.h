#ifndef _NETWORK_VALUE_CALCULUS_H_
#define _NETWORK_VALUE_CALCULUS_H_

float Get_z(Layer layers[], int l, int j);
float Get_deltaL(float y, float a, float z);
float* Init_arr_deltaL(float *arr_deltaL, float *y, Layer layer_out);
// ancienne erreur ici 
float Get_deltal(float *deltaL, float *w, int length, int j, float z);
float* Init_arr_deltal(float *arr_deltal, float *arr_deltaL, Layer layer_out, Layer layer_hid);

void Set_new_arr_b(float *b, size_t length, float deltal[]);
void Set_new_arr_w(float *w, size_t length, float deltal[], float *a, size_t previous_layer_length);
void Update_bw(Layer layer1, Layer layer2, float dl[]);

#endif
