
#include <cassert>
#include <complex>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <random>

#include "cblas.h"
#define BLAS(name)      name##_


//void sw_ColMajor_zgemm_reduce_master(char trans_1, char trans_2, int M, int N,int  K, std::complex<double>* A, int lda, std::complex<double>* B, int ldb, double* R);

int main() {
//  int M = 65536, N = 32768, K = 128;
  int M=196608, N=36864,K=128;


int fuse_op=1;
  std::complex<double> *A, *B,*C;
  std::complex<double> complexOne (1.0,0.0);
  std::complex<double> complexZero (0.0,0.0);
  double *R;
  A = (std::complex<double>*)malloc(sizeof(std::complex<double>) * M * K);
  B = (std::complex<double>*)malloc(sizeof(std::complex<double>) * K * N);
  R = (double*)malloc(sizeof(double) * M);
  std::generate(R, R + M, [&](){return 0.0;});
  int lda = M, ldb = K;

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(-1.0, 1.0);

  std::generate(A, A + M * K, [&](){return std::complex<double>{dis(gen), dis(gen)};});
  std::generate(B, B + N * K, [&](){return std::complex<double>{dis(gen), dis(gen)};});

  int batchSize=512;
  C = (std::complex<double>*)malloc(sizeof(std::complex<double>) * M * batchSize);
  int batchGemmNum=N/batchSize;
  int lessBatch=N%batchSize;
  std::cout<<"batchnum: " << batchGemmNum << " lessbatch: " <<lessBatch << std::endl;
  auto start = std::chrono::high_resolution_clock::now();


if(fuse_op==1)
{
  sw_ColMajor_zgemm_reduce_master('N', 'N', M, N, K, A, lda, B, ldb, R);
}


else
{


    for(int g=0;g<batchGemmNum;g++)
    {
    cblas_zgemm(CblasColMajor,CblasNoTrans, CblasNoTrans, M, batchSize, K, &complexOne, A,lda, &B[g*batchSize], ldb, &complexZero,C,M );

    for(int j=0;j<batchSize;j++)
    {
        for( int p = 0; p < M; p++ ) {
        R[p] += std::real((std::conj(C[p + j * M]) * C[p + j * M])) ;
        }
    }
    }
   cblas_zgemm(CblasColMajor,CblasNoTrans, CblasNoTrans, M, lessBatch, K, &complexOne, A,lda, &B[batchGemmNum*batchSize], ldb, &complexZero,C,M );

    for(int j=0;j<lessBatch;j++)
    {
        for( int p = 0; p < M; p++ ) {
        R[p] += std::real((std::conj(C[p + j * M]) * C[p + j * M])) ;
        }
    }  
}


  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> duration = end - start;
  std::cout<<"time: " << duration.count() << " ms" << std::endl;
double Gflops = (8 * (long long)M * N * K / duration.count()) / 1e6;
   std::cout << M << "," << N << "," << K << "," << duration.count() << "," << Gflops << std::endl;


}
