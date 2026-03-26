# CS451: Introduction to Parallel and Distributed Computing

Spring 2026

Assignment 5: OpenMP

## Setup:

1. Create a FABRIC slice that contains a single node
   provisioned with Ubuntu 22.04.5.
2. On that node, install GCC, Valgrind, and gprof.

## Development:

3. Take your program from step 3 in Assignment 3, and
   adapt it to use OpenMP instead of explicit threading.
4. Run the (updated) Life program for 100 cycles and time
   its execution.
5. Using `valgrind`, check the (updated) Life binary for
   memory leaks.
6. Using `gprof`, profile the (updated) Life binary.

## Bonus: Variable granularity (+30%)

7. Take your program from step 6 in Assignment 3, and
   adapt it to use OpenMP instead of explicit threading.
8. Setting `G=10` and using `valgrind`, check the
   (updated) Life binary for memory leaks.
9. Setting `G=10` and using `gprof`, profile the
   (updated) Life binary.

## What to submit: A `.tgz` file containing a set of text files:

- A file called `openmp_life.c` containing the code of
  your updated Life program from step 3, and any other
  `.c` and `.h` files that accompany the partitioned
  program.
- (Bonus only) A file called `granular_openmp_life.c`
  containing the code of your updated Life program from
  step 6.
- A set of files named `a.out`, `a.err`, `b.out`, etc,
  each containing the contents specified below:
  1. **(a)** The output from the compilation of your program
     (from step 3).
  2. **(b)** Theoutput from running your program (from step 4).
  3. **(c)** The output from step 5. (Penalty: -10% if there are
     memory leaks)
  4. **(d)** The output from step 6.
  5. **(e)** (Bonus only) The (compiler's) output from step 7.
  6. **(f)** (Bonus only) The output from step 8.
  7. **(g)** (Bonus only) The output from step 9.

  Where files ending in `.out` should contain the standard
  output, and files ending in `.err` should contain the error
  output.
