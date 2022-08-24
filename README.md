Comparing various *schedules* for *OpenMP-based* **vector element sum**.

Two floating-point vectors `x` and `y`, with number of **elements** from `1E+6`
to `1E+9` were multiplied using OpenMP. Each element count was attempted with
various **OpenMP schedule configs**, running each config 5 times to get a good
time measure. Sum here represents any `reduce()` operation that processes
several values to a single value. Results indicate a **num-threads** of `32`,
and a **schedule-kind** of `auto` to be suitable (for **float**).

All outputs are saved in [out](out/) and a small part of the output is listed
here. Some [charts] are also included below, generated from [sheets].

<br>

```bash
$ g++ -O3 -fopenmp main.cxx
$ ./a.out

# ...
#
# Elements 1e+07
# [00017.005 ms] [1.644725] sumSeq
# [00017.002 ms] [1.644725] sumOpenmp [1 threads; schedule static 64]
# [00016.983 ms] [1.644725] sumOpenmp [1 threads; schedule static 128]
# [00016.988 ms] [1.644725] sumOpenmp [1 threads; schedule static 256]
# [00016.729 ms] [1.644725] sumOpenmp [1 threads; schedule static 512]
# [00015.477 ms] [1.644725] sumOpenmp [1 threads; schedule static 1024]
# [00015.384 ms] [1.644725] sumOpenmp [1 threads; schedule static 2048]
# [00015.472 ms] [1.644725] sumOpenmp [1 threads; schedule static 4096]
# [00015.434 ms] [1.644725] sumOpenmp [1 threads; schedule static 8192]
# [00015.471 ms] [1.644725] sumOpenmp [1 threads; schedule static 16384]
# [00015.525 ms] [1.644725] sumOpenmp [1 threads; schedule static 32768]
# [00015.770 ms] [1.644725] sumOpenmp [1 threads; schedule static 65536]
# ...
```

[![](https://i.imgur.com/81zeekV.png)][sheetp]
[![](https://i.imgur.com/zaum47S.png)][sheetp]
[![](https://i.imgur.com/hK3yEyB.png)][sheetp]
[![](https://i.imgur.com/G916hQw.png)][sheetp]
[![](https://i.imgur.com/9mRfPvR.png)][sheetp]

[![](https://i.imgur.com/g4Th6c1.png)][sheetp]
[![](https://i.imgur.com/sjnMTmb.png)][sheetp]
[![](https://i.imgur.com/K2Dkk50.png)][sheetp]
[![](https://i.imgur.com/QQ6GgKw.png)][sheetp]
[![](https://i.imgur.com/sao63mM.png)][sheetp]

<br>
<br>


## References

- [What's the difference between "static" and "dynamic" schedule in OpenMP?](https://stackoverflow.com/a/10852852/1413259)
- [OpenMP Dynamic vs Guided Scheduling](https://stackoverflow.com/a/43047074/1413259)

<br>
<br>

[![](https://i.imgur.com/MJi0vOn.jpg)](https://knowyourcodelyokofacts.tumblr.com/post/49493220478/jeremy-belpois-jeremy-is-known-to-have-been)

[charts]: https://photos.app.goo.gl/2XgojedirZ3LZhy47
[sheets]: https://docs.google.com/spreadsheets/d/1m0IhoxjrarXYqE6yr_NdHlIrNn9QpkkOrHPidmNTcbo/edit?usp=sharing
[sheetp]: https://docs.google.com/spreadsheets/d/e/2PACX-1vTlIUrPp-YXzG2Svlwrg-uVZLja-csxl1m6iMEv9RXC0vxo9O_Ra5S4_ztl1PUg79QU4I3XefV3V7dJ/pubhtml
