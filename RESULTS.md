# Lab 2 results — sealed core

Name:  Johan Gonzaga
Student number:  12977609
Lab section:  L02
Core:  4 — B the letter on BRIEF.md
Machine:  Codespace
Cores:  4 — an integer

## Tools and sources

Tools and sources: Little book of semaphores

> Mandatory, even if it says "none". **No AI in the lab, at all** — see the
> README. Missing declaration: zero until you supply one. False one: misconduct.

## S2 — the defect · 40 marks

Three or more runs of `./bar given`, including one thread:

```
mode=given threads=1 rounds=1 bad=0 firstbad=-1 checksum=ok correct=yes deadlock=no time=0.0002 cpu=0.0003
mode=given threads=1 rounds=2 bad=0 firstbad=-1 checksum=ok correct=yes deadlock=no time=0.0001 cpu=0.0002
mode=given threads=1 rounds=3 bad=0 firstbad=-1 checksum=ok correct=yes deadlock=no time=0.0001 cpu=0.0002
```

**S2.1** Name the mechanism: which claim in `given.c`'s header is false, and
what is actually happening? State the barrier's invariant and say which half of
it this code does not keep.

The counter can be used as a wake-up condition, but as not the only wake-up condition as it also needs to simultaneously wake up, threads while also counting down through the wait() function

**S2.2** Prove it, in the form your `BRIEF.md` requires.

in given.c we can see that in the wait_ function the counter has a condition where if the count is == to n it wakes up a thread. Since we don't know the execution and posisition of each thread we can't say for sure if the 'next' thread is the one that needs to awaken, therefore causing the deadlock

**S2.3** Minimality: what breaks if you do less, what it costs if you do more.

It costs more if you wake up all the threads pertaining to the round, however it breaks if you only wake up one per round as with more threads it's no longer a parallel, but serial program

## S3 — the measurement · 30 marks

`./bar all <t> <rounds>` at 1, 2, 4 and 8 threads. Pasted, not retyped. If a
mode stops, `all` stops with it — run the modes one at a time and paste those.

```
mode=given threads=1 rounds=2 bad=0 firstbad=-1 checksum=ok correct=yes deadlock=no time=0.0002 cpu=0.0002
mode=fixed threads=1 rounds=2 bad=0 firstbad=-1 checksum=ok correct=yes deadlock=no time=0.0001 cpu=0.0001
mode=alt threads=1 rounds=2 bad=-1 firstbad=-1 checksum=nobarrier correct=no deadlock=no time=0.0000 cpu=0.0000
alt: create() returned NULL -- nothing was run
---
mode=given threads=2 rounds=2 bad=0 firstbad=-1 checksum=ok correct=yes deadlock=no time=0.0002 cpu=0.0003
mode=fixed threads=2 rounds=2 bad=0 firstbad=-1 checksum=ok correct=yes deadlock=no time=0.0002 cpu=0.0002
mode=alt threads=2 rounds=2 bad=-1 firstbad=-1 checksum=nobarrier correct=no deadlock=no time=0.0000 cpu=0.0000
alt: create() returned NULL -- nothing was run
---
mode=given threads=4 rounds=2 bad=-1 firstbad=-1 checksum=unknown correct=no deadlock=yes time=5.0092 cpu=0.0025
mode=fixed threads=4 rounds=2 bad=0 firstbad=-1 checksum=ok correct=yes deadlock=no time=0.0004 cpu=0.0006
mode=alt threads=4 rounds=2 bad=-1 firstbad=-1 checksum=nobarrier correct=no deadlock=no time=0.0000 cpu=0.0000
alt: create() returned NULL -- nothing was run
---
mode=given threads=8 rounds=2 bad=-1 firstbad=-1 checksum=unknown correct=no deadlock=yes time=5.0082 cpu=0.0025
mode=fixed threads=8 rounds=2 bad=0 firstbad=-1 checksum=ok correct=yes deadlock=no time=0.0006 cpu=0.0011
mode=alt threads=8 rounds=2 bad=-1 firstbad=-1 checksum=nobarrier correct=no deadlock=no time=0.0000 cpu=0.0000
```

| threads | given: correct? | given: time | given: cpu | fixed: time | fixed: cpu | alt: time | alt: cpu |
|---|---|---|---|---|---|---|---|
| 1 |Yes |0.0002 |0.0002 |0.0001 |0.0001 |0.0000 |0.0000 |
| 2 |No |5.0092 |0.0092 |0.0002 |0.0002 |0.0000 |0.0000 |
| 4 |No |5.0000|0.0000 |0.0004 |0.0006 |0.0000 |0.0000 |
| 8 |No |5.0000 |0.0000 |0.0006 |0.0011 |0.0000 |0.0000 |

**S3.1** Reconcile with `PREDICTION.md`: quote what you predicted, say what
happened, account for the difference. If you were right, say what would have
made you wrong.

Prediction.md stated that as a parallel to Lab 1, it would cause a faster execution for the program, however it seems that with the amount of threads increasing the cpu time and the program time increases marginally.

**S3.2** Which would you ship on this machine, **and what measurement would
change your mind?**

Similarly to lab 1 I would ship the fixed on multi core systems, but for single core it would provide a program that would be marginally worse.

## S4 — explain-back · 15 marks

> Two or three sentences, your own words: someone who has not seen this code
> asks *what was wrong with it, and what did fixing it cost?*

What happened was that the code was trying to find a specific thread for the system to run next, but most of the time the thread that was projected to being used was incorrect causing the system to pause, and end. This was fixed by allowing all remaining threads per round to activate. Allowing for the system to execute without any need for considering what's next. Fixing costed relatively nothing other than some extra resources as a consequence to utilizing parallization in the system.

## Anything you got stuck on

Optional. One or two lines.
