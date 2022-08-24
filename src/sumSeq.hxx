#pragma once
#include <vector>
#include "sum.hxx"

using std::vector;




template <class T>
T sumLoop(const T *x, int N) {
  T a = T();
  for (int i=0; i<N; i++)
    a += x[i];
  return a;
}

template <class T>
SumResult<T> sumSeq(const T *x, int N, const SumOptions& o={}) {
  T a = T(); float t = measureDuration([&]() { a = sumLoop(x, N); }, o.repeat);
  return {a, t};
}

template <class T>
SumResult<T> sumSeq(const vector<T>& x, const SumOptions& o={}) {
  return sumSeq(x.data(), x.size(), o);
}
