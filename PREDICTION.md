# Prediction sheet — push by 0:20, before you compile

> Marked on **having predicted** and on reconciling it in S3.1 — **not on being
> right.** A confident wrong prediction you then explain is full marks. A blank
> page is none. A page timestamped after your first run is worse than none.
>
> Read `src/given.c` and `BRIEF.md`. Run nothing.

Cores:  4 — from PREP.md
Lab 0 spread:  15.8 — the percentage, from PREP.md

> **P1.** `./bar given` on **one** thread — does it come out right? Yes/no, one
> sentence why.

Yes, since one thread is used its the same as serial execution

> **P2.** On **8** threads, pick one and commit to it: right answer / wrong
> answer / it stops. If wrong, roughly how big is `bad`? If it stops, say at
> which of the two waits in a round.

It does not execute correctly, as it deadlocks.

> **P3.** Three runs at 8 threads — **identical** numbers, or different? Think
> about this one before you write it; it is the most useful line on the page.

8 threads are ran with the span of 1 round per execution, the spread is around 0.0001s, we can say that there is a larger execution due to the amount of rounds, but it's useless due to the semaphore deadlocking.

> **P4.** Seconds, before measuring. Orders of magnitude are what matter. `cpu`
> is process CPU time over all threads, so `cpu`/`time` is how many cores were
> busy — one number per box.

| | 1 thread: time | 8 threads: time | 8 threads: cpu/time |
|---|---|---|---|
| `given` |0.00020s |0.00250s |0.00100s |
| `fixed` |0.00008s |0.00010s | 0.00004s|
| `alt` | 0.00000s|0.00000s | 0.00000s|

> **P5.** Fastest and slowest at 8 threads? Name anything you expect to get
> **slower** as threads are added, and anything you expect to stop altogether.

Slowest would be the given at 8 threads as the semaphore doesn't fully filter all of the threads to one process. Fastest would be fixed as its doing what it's supposed to be doing.
