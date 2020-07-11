#include <iostream>
#include "cuda_runtime.h"
#include "cuda/square.hpp"

int main()
{

    const int BUFF_SIZE = 100;
    const int BUFF_SIZE_BYTE = BUFF_SIZE * sizeof(float);

    float h_in[BUFF_SIZE];
    for(int i=0; i<BUFF_SIZE; i++){
        h_in[i] = float(i);
    }

    for(int i=0; i<BUFF_SIZE; i++){
        std::cout << h_in[i] << " ";
    }
    std::cout << std::endl << std::endl;

    float h_out[BUFF_SIZE];

    float* d_in;
    float* d_out;

    cudaMalloc((void**)&d_in, BUFF_SIZE_BYTE );
    cudaMalloc((void**)&d_out, BUFF_SIZE_BYTE );

    cudaMemcpy(d_in, h_in, BUFF_SIZE_BYTE, cudaMemcpyHostToDevice);
    
    square_run(d_in, d_out, BUFF_SIZE);

    cudaMemcpy(h_out, d_out, BUFF_SIZE_BYTE, cudaMemcpyDeviceToHost);

    for(int i=0; i<BUFF_SIZE; i++){
        std::cout << h_out[i] << " ";
    }

    std::cout << std::endl;
    
    
    return 0;
}