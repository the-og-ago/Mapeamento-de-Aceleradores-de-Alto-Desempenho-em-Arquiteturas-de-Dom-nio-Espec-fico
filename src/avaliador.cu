#include <cuda_runtime.h>
#include <stdio.h>
#include <time.h>
#include "gerador.hpp"
#define CHECK(call) \
{ \
    const cudaError_t error = call; \
    if (error != cudaSuccess) \
    { \
        printf("Error: %s:%d, ", __FILE__, __LINE__); \
        printf("code:%d, reason: %s\n", error, cudaGetErrorString(error)); \
        exit(1); \
    } \
}
__global__ void avaliar(float *A, int linhas, int n_atributos)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if(i<linhas){
        if(A[i*n_atributos+2]>30){
            if(A[i*n_atributos+0]>23){
                A[i*n_atributos+(n_atributos-1)]=1;
            } else {
                A[i*n_atributos+(n_atributos-1)]=2;
            }
        } else {
            if(A[i*n_atributos+1]>53){
                A[i*n_atributos+(n_atributos-1)]=2;
            } else {
                A[i*n_atributos+(n_atributos-1)]=0;
            }
        }
    }
}

int main(int argc, char **argv)
{
    srand((unsigned) time(NULL));
    float elapsed_time;

    // set up device
    int dev = 0;
    cudaDeviceProp deviceProp;
    CHECK(cudaGetDeviceProperties(&deviceProp, dev));
    printf("Using Device %d: %s\n", dev, deviceProp.name);
    CHECK(cudaSetDevice(dev));

    // set up data size of vectors
    int linhas= 1 << 20; //~1m
    int colunas= 4;
    float lim_s=10.0f;
    float lim_i=-10.0f;
    //int nElem = 1 << 24; // 2^24 = 16 M elements, 64Mbytes
    printf("Vector Size %d\n", linhas*colunas);

    // malloc host memory
    size_t nBytes = linhas*colunas * sizeof(float);

    float *h_A, *hostRef, *h_C;
    float *h_B;
    /*h_A     = (float *)malloc(nBytes);
    h_B     = (float *)malloc(nBytes);
    hostRef = (float *)malloc(nBytes);
    h_C  = (float *)malloc(nBytes);
    */
    Gerador g(linhas,colunas);
    g.randomizar(lim_s,lim_i);
    h_A=g.get_tabela();
    /*memset(hostRef, 0, nBytes);
    memset(h_C,  0, nBytes);
    */
    // malloc device global memory
    float *d_A, *d_C;
    float *d_B;
    CHECK(cudaMalloc((float**)&d_A, nBytes));
    /*CHECK(cudaMalloc((float**)&d_B, nBytes));
    CHECK(cudaMalloc((float**)&d_C, nBytes));
    */
    // transfer data from host to device
    CHECK(cudaMemcpy(d_A, h_A, nBytes, cudaMemcpyHostToDevice));
    //CHECK(cudaMemcpy(d_B, h_B, nBytes, cudaMemcpyHostToDevice));

    // invoke kernel at host side
    int iLen = 512;
    dim3 block (iLen);
    dim3 grid  ((linhas + block.x - 1) / block.x);

    cudaEvent_t start, stop;
    CHECK(cudaEventCreate(&start));
    CHECK(cudaEventCreate(&stop));
    // record start event
    CHECK(cudaEventRecord(start, 0));


    // Kernel Call *********************

    avaliar<<<grid, block>>>(d_A,linhas,colunas);

    // *********************************

    CHECK(cudaEventRecord(stop, 0));
    CHECK(cudaEventSynchronize(stop));
    // calculate elapsed time
    CHECK(cudaEventElapsedTime(&elapsed_time, start, stop));
    printf("Measured time for parallel execution = %.6fms\n",
           elapsed_time );

    // check kernel error
    CHECK(cudaGetLastError()) ;

    // copy kernel result back to host side
    CHECK(cudaMemcpy(h_A, d_A, nBytes, cudaMemcpyDeviceToHost));

    // free device global memory
    CHECK(cudaFree(d_A));
    //CHECK(cudaFree(d_B));
    //CHECK(cudaFree(d_C));
    CHECK(cudaEventDestroy(start));
    CHECK(cudaEventDestroy(stop));

    // free host memory
    /*free(h_A);
    free(h_B);
    free(hostRef);
    free(h_C);
    */
    return(0);
}