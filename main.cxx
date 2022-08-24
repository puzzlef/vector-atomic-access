#include <cstdint>
#include <random>
#include <vector>
#include <atomic>
#include <cstdio>
#include <omp.h>
#include "src/main.hxx"

using namespace std;




template <class T>
int threadRun(vector<T>& x, int L) {
  int a = 0;  // parity sum
  random_device dev;
  default_random_engine rnd(dev());
  uniform_int_distribution<> idxDis(0, int(x.size()-1));
  for (int l=0; l<L; ++l) {
    int i = idxDis(rnd);
    x[i] = randomWithSplitOddParity1<T>(rnd);
    a += parity1(x[i]);
  }
  return a;
}


template <class T>
void runWithTypeAndSize(int size, int accesses, int numThreads, int repeat, const char *name) {
  vector<T>   sharedData(size);
  vector<int> paritySum(numThreads);
  float t = measureDuration([&]() {
    fillValueU(sharedData, T());
    #pragma omp parallel for schedule(static, 1)
    for (int t=0; t<numThreads; ++t)
      paritySum[t] = threadRun(sharedData, accesses);
  }, repeat);
  float totalParitySum = float(sumValues(paritySum)) / repeat;
  printf("[%09.3f ms; %.1f par_sum] %s {accesses=%d}\n", t, totalParitySum, name, accesses);
}

template <class T>
void runWithType(int accesses, int numThreads, int repeat, const char *name) {
  for (int N=32; N<=1024; N*=2)
    runWithType<T>(N, accesses, numThreads, repeat, name);
}


void runExperiment(int repeat) {
  int maxThreads = 12;
  int accesses   = 1000000000;
  omp_set_num_threads(maxThreads);
  printf("OMP_NUM_THREADS=%d\n", maxThreads);
  runWithType<uint32_t>(accesses, maxThreads, repeat, "access32Default");
  runWithType<atomic<uint32_t>>(accesses, maxThreads, repeat, "access32Atomic");
  runWithType<uint64_t>(accesses, maxThreads, repeat, "access64Default");
  runWithType<atomic<uint64_t>>(accesses, maxThreads, repeat, "access64Atomic");
  runWithType<array<uint64_t, 2>>(accesses, maxThreads, repeat, "access128Default");
  runWithType<atomic<array<uint64_t, 2>>>(accesses, maxThreads, repeat, "access128Atomic");
  runWithType<array<uint64_t, 4>>(accesses, maxThreads, repeat, "access256Default");
  runWithType<atomic<array<uint64_t, 4>>>(accesses, maxThreads, repeat, "access256Atomic");
  runWithType<array<uint64_t, 8>>(accesses, maxThreads, repeat, "access512Default");
  runWithType<atomic<array<uint64_t, 8>>>(accesses, maxThreads, repeat, "access512Atomic");
  runWithType<array<uint64_t, 16>>(accesses, maxThreads, repeat, "access1024Default");
  runWithType<atomic<array<uint64_t, 16>>>(accesses, maxThreads, repeat, "access1024Atomic");
}


int main(int argc, char **argv) {
  int repeat = argc>1? stoi(argv[1]) : 5;
  runExperiment(repeat);
  printf("\n");
  return 0;
}
