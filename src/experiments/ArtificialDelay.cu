#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

#define ALLOC_SIZE 1024000
#define CUDA_SUCCESS cudaSuccess 

int GetCudaFrequency() {
  cudaDeviceProp prop;
  cudaGetDeviceProperties(&prop, 0);
  return prop.clockRate;
}

__global__ void SpinForever() {
  int i = 0;
  while (i == 0) {}
}

// Spin in the GPU for a certain delay, siAAmulates load to induce synchronization delay.
__global__ void LaunchSpinForTime(uint64_t delay) {
    uint64_t start_clock = clock64();
    uint64_t clock_offset = 0;
    while (clock_offset < delay)
    {
        clock_offset = clock64() - start_clock;
    }
}


int ExperimentNoUse(int cpuDelay) {
  
  uint64_t gpuDelay = (cpuDelay + (cpuDelay * 0.20)) * (GetCudaFrequency() * 1000);
  fprintf(stderr, "GPU will delay for - %ull clock cycles (%ull seconds)\n",gpuDelay, gpuDelay / (GetCudaFrequency() * 1000) );
  //uint64_t *x, *d_x, *d_y;
  // Launch GPU Kernel
  LaunchSpinForTime<<<1,1>>>(gpuDelay);
  //LaunchSpinOnMem<<<1,1>>>(flags);
  // Immediately sleep to simulate CPU workload
  sleep(cpuDelay);
  fprintf(stderr, "Left CPU Work, waiting on GPU synchronization\n");
  // Unnnecessary Synchronization that should take between 10-20% of execution time
  cudaDeviceSynchronize();
  fprintf(stderr, "GPU synchronization complete\n");
  sleep(15);
  return 0;
}

int myexperiment() {
  fprintf(stderr, "Cycle count: %d\n", GetCudaFrequency());
  SpinForever<<<1,1>>>();
  sleep(5);
  fprintf(stderr, "Cycle count: %d\n", GetCudaFrequency());
  uint64_t *d_x;
  if (CUDA_SUCCESS != cudaMalloc(&d_x, ALLOC_SIZE*sizeof(uint64_t)))
   fprintf(stderr, "ERROR\n"); 
  for (int i = 0; i < 2; i++)
    ExperimentNoUse(60);
  return 0;
}

int main() {
    return myexperiment();
}
