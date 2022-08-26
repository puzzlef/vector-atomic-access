Compare ways to access elements of a vector *atomically*.

In this experiment we try to **access a shared vector on mutiple threads** (*48*
*threads*, using *OpenMP*). Our objective is to **obtain the number size** (in
bits), **beyond which memory reads and writes are not atomic** (by default).
Each thread generates a random number with *zero parity*, and writes to a
*random index* in the vector. It then reads a number stored at *another random*
*index*, and computes its parity. When a read and write occurrs to the same
memory location at the same time (randomly), and the number is read before a
full write is complete (or vice versa), it can be detected with *50% chance*
when we observe a *parity of the number* to be a `1` instead of a `0`. However
when reads and writes are *atomic*, a parity of `1` can **never** be observed.
We sum the total parity of obtained on all threads.

We attempt both the **default memory access**, and the **atomic memory access**
(using `std::atomic`). We adjust the size of the vector from `1` to `32`. With
each size, we initialize the vector with zeros (with parity *0*) and perform a
total of *one million writes and reads* on each thread (we repeat this *5 times*
to obtain an average time). Memory accesses are performed using *default* and
*atomic* approach with the bit-width of number varying from `32` to `16384`
bits. Numbers larger than *64 bits* are represented using `std::array` of
`uint64_t`.

From the results we observe a *zero parity-sum* for numbers of sizes `32` and
`64` bits (on *both* default and atomic accesses). This indicates that the
**x86_64 architecture performs atomic reads and writes of upto 64-bit numbers**
**(its word size) by default**. For numbers larger that `64` bits, we observe a
*non-zero parity-sum* for the *default access* approach, indicating that reads
and writes are *not* atomic. Also note that **as the size of the vector is**
**increased** from `1` to `32`, the **number of read-write conflicts decrease**
(as indicated by a decrease in parity-sum) as we would expect it to given the
*reducing chances* two threads accessesing the *same* memory location at the
same time. However, we observe *no* increase/decrease in the number of conflicts
with increasing *number size (in bits)*. In terms of *time taken* for *1M*
*accesses*, we also observe that **increasing the size of the vector reduces the**
**amount of time taken to complete**. Increasing the bit-width of each number also
increases the time take, but this is expected to the larger memory access
requirement with larger numbers.

All outputs are saved in a [gist] and a small part of the output is listed here.
Some [charts] are also included below, generated from [sheets]. This experiment
was done with guidance from [Prof. Kishore Kothapalli], [Prof. Dip Sankar Banerjee],
and [Prof. Sathya Peri].

<br>

```bash
$ g++ -std=c++17 -O3 -latomic -fopenmp main.cxx
$ ./a.out

# OMP_NUM_THREADS=48
# [02686.566 ms; 0.0 par_sum] access32Default {size=1}
# [02742.435 ms; 0.0 par_sum] access32Atomic  {size=1}
# [02662.369 ms; 0.0 par_sum] access32Default {size=2}
# [02753.327 ms; 0.0 par_sum] access32Atomic  {size=2}
# [02675.026 ms; 0.0 par_sum] access32Default {size=4}
# [02797.603 ms; 0.0 par_sum] access32Atomic  {size=4}
# ...
#
# ...
# [1164004.250 ms; 0.0 par_sum] access16384Atomic  {size=4}
# [27715.729 ms; 2362642.0 par_sum] access16384Default {size=8}
# [1163569.125 ms; 0.0 par_sum] access16384Atomic  {size=8}
# [27597.848 ms; 1384799.0 par_sum] access16384Default {size=16}
# [1156279.500 ms; 0.0 par_sum] access16384Atomic  {size=16}
# [27711.156 ms; 576781.0 par_sum] access16384Default {size=32}
# [1156447.125 ms; 0.0 par_sum] access16384Atomic  {size=32}
```

[![](https://i.imgur.com/shhkO4H.png)][sheetp]
[![](https://i.imgur.com/GeKBVbD.png)][sheetp]

<br>
<br>


## References

- [C++ undefined reference to `__atomic_load_16'](https://stackoverflow.com/q/37613415/1413259)
- [How to declare a vector of atomic in C++](https://stackoverflow.com/a/46736273/1413259)
- [What exactly is std::atomic?](https://stackoverflow.com/a/31978762/1413259)
- [Concurrency: Atomic and volatile in C++11 memory model](https://stackoverflow.com/a/8833218/1413259)
- [std::atomic: cppreference](https://en.cppreference.com/w/cpp/atomic/atomic)

<br>
<br>

[![](https://i.imgur.com/INKPsi2.jpg)](https://www.youtube.com/watch?v=fDubIYr4qTA)<br>


[Prof. Dip Sankar Banerjee]: https://sites.google.com/site/dipsankarban/
[Prof. Kishore Kothapalli]: https://faculty.iiit.ac.in/~kkishore/
[Prof. Sathya Peri]: https://people.iith.ac.in/sathya_p/
[gist]: https://gist.github.com/wolfram77/4a786b39ebd6b551a8f7eca4fe05618c
[charts]: https://imgur.com/a/BS2Z91C
[sheets]: https://docs.google.com/spreadsheets/d/1f8L7T6gpA1NKH92PxwwkaShZvmFVuwbAAaXspKYfB_4/edit?usp=sharing
[sheetp]: https://docs.google.com/spreadsheets/d/e/2PACX-1vSXye2IGLb10v8K9zdvYPN6teGNo8Woghrzzm-aiQJ4lgejbC8ESvwTXSnE1Jg3QF4YSeSxf9Iyj58j/pubhtml
