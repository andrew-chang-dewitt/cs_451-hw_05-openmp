# Assignment 5: OpenMP

CS451: Introduction to Parallel and Distributed Computing \
Spring 2026

---

a quick practice in implicit multi-threading using OpenMP. takes an existing
multithreaded program (from assignment 3) & replaces the explicit threading
code w/ openmp function & pragmas. see [assignment writeup](./assignment.md)
for more details.

> [!NOTE]
>
> source file ./granular_openmp_life.c is simply a symbolic link to
> ./openmp_life.c because my implementation has no difference between the two.
> if the granularity flag is not specified (e.g. calling `openmp_life -s 4 -c 5
-i 0000111` instead of `openmp_life -s 4 -g 2 -c 5 -i 0000111`), then the
> default granularity of 4 will be used.
