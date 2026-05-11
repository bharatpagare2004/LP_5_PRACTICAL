#include<iostream>
#include<cuda_runtime.h>
using namespace std;

//kernel function
__global__ void add(int *A,int *B, int *C)
{
  int i = threadIdx.x;
  C[i] = A[i]+B[i];
}
int main()
{
  int n = 5;
  int A[n] = {1,2,3,4,5};
  int B[n] = {5,4,3,2,1};
  int C[n];

  int *d_A,*d_B,*d_C;

  //allocate memory on GPU
  cudaMalloc(&d_A,n*sizeof(int));
  cudaMalloc(&d_B,n*sizeof(int));
  cudaMalloc(&d_C,n*sizeof(int));

  //copy data to GPU
  cudaMemcpy(d_A,A,n*sizeof(int),cudaMemcpyHostToDevice);
  cudaMemcpy(d_B,B,n*sizeof(int),cudaMemcpyHostToDevice);

  add<<<1,n>>>(d_A,d_B,d_C);

  //back to copy for cpu 
  cudaMemcpy(C,d_C,n*sizeof(int),cudaMemcpyDeviceToHost);

  //result
  for(int i = 0;i<n;i++)
  {
    cout<<C[i]<<" ";

  }
  cudaFree(d_A);
  cudaFree(d_B);
  cudaFree(d_C);

  return 0;

}
