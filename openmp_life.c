/*
    Conway's Game of Life (and rough edges in the code for teaching purposes)
    Copyright (C) 2025 Nik Sultana

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.


gcc life.c -o life # -pg
valgrind -s --leak-check=full --show-leak-kinds=all \
  ./life -s 20 -c 20 \
  -i 010000000001000000000010000000010000000011100000000100000000

./life -s 3 -c 3 -i 011001010

./life -s 5 -c 10 -i 011001010110101111

./life -s 20 -c 10 \
  -i 011001010110101111011001010110101111010111101010101111100110111

# Glider and blinker:
./life -s 20 -c 20 \
  -i 010000000001000000000010000000010000000011100000000100000000

# Bee-hive and loaf:
./life -s 10 -c 100 \
  -i 010000000001000000000010000000010000000011100000000100000000
*/
// fix error w/ unknown * ‘pthread_barrier_*’ caused by -std=c99 compile time
// flag
#define _POSIX_C_SOURCE 200112L /* Or higher */
// Source - https://stackoverflow.com/a/61648098
// Posted by Shawn, modified by community. See post 'Timeline' for change
// history Retrieved 2026-02-20, License - CC BY-SA 4.0

#include "omp.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef ARGH
#include "args.h"
#endif
#ifndef STEPH
#include "step.h"
#endif
#ifndef WORLDH
#include "world.h"
#endif

int main(int argc, char *const *argv) {
  // parse args to config values
  Config cfg = parse_args(argc, argv);
  // initialize state obj
  char *world_history = init_world(cfg.size, cfg.cycles, cfg.init_world);

  // set up openmp
  // take control of how many threads are created by disabling dynamic teams
  // see SO: https://stackoverflow.com/a/11096742
  omp_set_dynamic(0);
  // hard-code thread counts based on config
  omp_set_num_threads(cfg.num_parts);

  // print initial state as first step
  print_world(world_history, cfg.size, 0);
  printf("\n");

  // set up thread worker variables
  unsigned long part_offsets[cfg.num_parts][2];
  // first part starts at beginning
  part_offsets[0][0] = 0;
  part_offsets[0][1] = cfg.parts[0];
  // then each subsequent part starts at end of last part
  for (unsigned int t = 1; t < cfg.num_parts; t++) {
    part_offsets[t][0] = part_offsets[t - 1][1];
    part_offsets[t][1] = part_offsets[t][0] + cfg.parts[t];
  }

  char *cur_step;
  char *new_step = world_history;

  // main thread will print each step
  for (unsigned long i = 1; i < cfg.cycles; i++) {
    cur_step = new_step;
    new_step = cur_step + (cfg.size * cfg.size);

#pragma omp parallel
    {
#ifdef VERBOSE
#pragma omp master
      printf("[main()] in parallel region with %d threads\n",
             omp_get_num_threads());
#endif
#pragma omp for
      for (unsigned int p = 0; p < cfg.num_parts; p++) {
#ifdef VERBOSE
        printf("[main()] thread num %d working on part_num %d\n",
               omp_get_thread_num(), p);
#endif
        step_part(cur_step, part_offsets[p][0], part_offsets[p][1], cfg.size,
                  new_step);
      }
    }

    // then print that step
    print_world(world_history, cfg.size, i);
    printf("\n");
  }

  free(world_history);
  free(cfg.init_world);
  free(cfg.parts);

  return EXIT_SUCCESS;
}
