#include <iostream>
#include "complex_gpu.h"

__global__ void subtract_psf_kernel(cuFloatComplex *d_subnfftsp,
                                    const cuFloatComplex __restrict__ *d_psf,
                                    int numWinTs,
                                    int subnfftspSize,
                                    int offset,
                                    const int *d_i1,
                                    const int *d_i2,
                                    const int *d_i3,
                                    const int *d_i4,
                                    const int *d_k1,
                                    const int *d_k2,
                                    const int *d_k3,
                                    const int *d_k4,
                                    int sizePSF1,
                                    int sizePSF2,
                                    int sizePSF3,
                                    cuFloatComplex *nfftval
                                   )
{

   int id = threadIdx.x + blockDim.x*blockIdx.x;

   if( id < numWinTs*subnfftspSize)
   {
      int thisWinTs = id/subnfftspSize;

      int p1 = d_k1[id] - d_i1[thisWinTs];
      int p2 = d_k2[id] - d_i2[thisWinTs];
      int p3 = d_k3[id] - d_i3[thisWinTs];
      int p4 = d_k4[id] - d_i4[thisWinTs];

      int idxOut = p4*sizePSF3*sizePSF2*sizePSF1+p3*sizePSF2*sizePSF1+p2*sizePSF1+p1+offset;

      d_subnfftsp[id] = d_subnfftsp[id] - d_psf[idxOut]*nfftval[thisWinTs];
   }

}

int main()
{
#if 0
   const int niter = 1000;
   const int numWinTs = 192;
   const int p1_size =  45;
   const int p2_size = 45;
   const int p3_size = 17;
   const int p4_size = 1;
   const int k1_size =  23;
   const int k2_size = 23;
   const int k3_size = 9;
   const int k4_size = 1;
   const int subnfftspSize = 4761;
   const int psfOffset = 17212;
   dim3 threads4(256,1,1);
   dim3 blocks4;
   blocks4.x = (numWinTs*subnfftspSize)/threads4.x;
   blocks4.x +=((numWinTs*subnfftspSize)%threads4.x)?1:0;

   cuFloatComplex *d_vecIn;
   cuFloatComplex *d_vecPSF;
   cudaMalloc(&d_vecIn, subnfftspSize*sizeof(cuFloatComplex));
   cudaCheckError();
   cudaMalloc(&d_vecPSF, psize*sizeof(cuFloatComplex));
   cudaCheckError();
   // copy data to GPU
   cudaMemcpy(d_vecIn, &vecIn[0], ksize*sizeof(cuFloatComplex), cudaMemcpyHostToDevice);
   cudaCheckError();
   cudaMemcpy(d_vecPSF, &vecPSF[0], psize*sizeof(cuFloatComplex), cudaMemcpyHostToDevice);
   cudaCheckError();
   cuFloatComplex d_nfftval = make_cuFloatComplex(crealf(nfftval), cimag(nfftval));

   for(int iter = 0 ; iter < niter ; iter++)
   {
   
      subtract_psf_kernel<<<blocks4, threads4>>>(cuFloatComplex *d_subnfftsp,
                                                 const cuFloatComplex __restrict__ *d_psf,
                                                 numWinTs,
                                                 subnfftspSize,
                                                 psfOffset,
                                                 const int *d_i1,
                                                 const int *d_i2,
                                                 const int *d_i3,
                                                 const int *d_i4,
                                                 const int *d_k1,
                                                 const int *d_k2,
                                                 const int *d_k3,
                                                 const int *d_k4,
                                                 p1_size,
                                                 p2_size,
                                                 p3_size,
                                                 cuFloatComplex *nfftval);
   }
#endif
   return 0;
}
