#include "square.hpp"

__global__ void square(float* d_in, float* d_out) {
    int idx =  threadIdx.x;
    float f = d_in[idx];
    d_out[idx] = f * f;
}

void square_run(float* d_in, float* d_out, const int d_buffsize){
    square<<<1, d_buffsize>>>(d_in, d_out);
}
