#pragma once
#include "_main.hxx"




struct SumOptions {
  int repeat;
  int numThreads;
  int scheduleKind;
  int chunkSize;

  SumOptions(int repeat=1, int numThreads=1, int scheduleKind=omp_sched_static, int chunkSize=64) :
  repeat(repeat), numThreads(numThreads), scheduleKind(scheduleKind), chunkSize(chunkSize) {}
};


template <class T>
struct SumResult {
  T     result;
  float time;

  SumResult(T result, float time) :
  result(result), time(time) {}
};
