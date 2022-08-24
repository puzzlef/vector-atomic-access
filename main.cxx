#include <cmath>
#include <vector>
#include <string>
#include <cstdio>
#include "src/main.hxx"

using namespace std;



#define TYPE float


void runSum(int N, int repeat) {
  vector<TYPE> x(N);
  for (int i=0; i<N; i++) {
    TYPE n = i+1;
    x[i] = 1/(n*n);
  }

  // Find Σx using a single thread.
  auto a0 = sumSeq(x, {repeat});
  printf("[%09.3f ms] [%f] sumSeq\n", a0.time, a0.result);

  // Find x*y accelerated using OpenMP.
  int maxThreads = omp_get_max_threads();
  for (int i=0;; i++) {
    bool done = false;
    int threads = 1<<(i/2) + (i&1)<<(i/4);
    if (threads>maxThreads) { threads = maxThreads;  done = true; }
    // Use static schedule.
    for (int chunkSize=64; chunkSize<=65536; chunkSize*=2) {
      auto a1 = sumOpenmp(x, {repeat, threads, omp_sched_static, chunkSize});
      printf("[%09.3f ms] [%f] sumOpenmp [%d threads; schedule static %d]\n", a1.time, a1.result, threads, chunkSize);
    }

    // Use dynamic schedule.
    for (int chunkSize=64; chunkSize<=65536; chunkSize*=2) {
      auto a2 = sumOpenmp(x, {repeat, threads, omp_sched_dynamic, chunkSize});
      printf("[%09.3f ms] [%f] sumOpenmp [%d threads; schedule dynamic %d]\n", a2.time, a2.result, threads, chunkSize);
    }

    // Use guided schedule.
    for (int chunkSize=64; chunkSize<=65536; chunkSize*=2) {
      auto a3 = sumOpenmp(x, {repeat, threads, omp_sched_guided, chunkSize});
      printf("[%09.3f ms] [%f] sumOpenmp [%d threads; schedule guided %d]\n", a3.time, a3.result, threads, chunkSize);
    }

    // Use auto schedule.
    for (int chunkSize=64; chunkSize<=65536; chunkSize*=2) {
      auto a4 = sumOpenmp(x, {repeat, threads, omp_sched_auto, chunkSize});
      printf("[%09.3f ms] [%f] sumOpenmp [%d threads; schedule auto %d]\n", a4.time, a4.result, threads, chunkSize);
    }
    if (done) break;
  }
}


int main(int argc, char **argv) {
  int repeat = argc>1? stoi(argv[1]) : 5;
  for (int n=1000000; n<=1000000000; n*=10) {
    printf("# Elements %.0e\n", (double) n);
    runSum(n, repeat);
    printf("\n");
  }
  return 0;
}
