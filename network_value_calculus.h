#ifndef _NETWORK_VALUE_CALCULUS_H_
#define _NETWORK_VALUE_CALCULUS_H_

double Get_z(Layer layers[], size_t l, size_t j);
double Get_deltaL(double y, double a, double z);
double* Init_arr_deltaL(double *arr_deltaL, double *y, Layer layer_out);
// ancienne erreur ici 
double Get_deltal(double *deltaL, double *w, size_t length, size_t j, double z);
double* Init_arr_deltal(double *arr_deltal, double *arr_deltaL, Layer layer_out, Layer layer_hid);

void Set_new_arr_b(double *b, size_t length, double deltal[]);
void Set_new_arr_w(double *w, size_t length, double deltal[], double *a, size_t previous_layer_length);
void Update_bw(Layer layer1, Layer layer2, double dl[]);

#endif
