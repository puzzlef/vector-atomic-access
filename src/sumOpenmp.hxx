#pragma once
#include "_main.hxx"
#include "sum.hxx"




template <class T>
T sumOmp(const T *x, int N) {
  T a = T();
  #pragma omp parallel for reduction(+:a)
  for (int i=0; i<N; i++)
    a += x[i];
  return a;
}

template <class T>
T sumOmp(const vector<T>& x) {
  return sumOmp(x.data(), x.size());
}


template <class T>
SumResult<T> sumOpenmp(const T *x, int N, const SumOptions& o={}) {
  int NT = o.numThreads;
  int SK = o.scheduleKind;
  int SC = o.chunkSize;
  omp_set_num_threads(NT);
  omp_set_schedule((omp_sched_t) SK, SC);
  T a = T(); float t = measureDuration([&] { a = sumOmp(x, N); }, o.repeat);
  return {a, t};
}

template <class T>
SumResult<T> sumOpenmp(const vector<T>& x, const SumOptions& o={}) {
  return sumOpenmp(x.data(), x.size(), o);
}
