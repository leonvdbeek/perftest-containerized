/* Copyright (c) 2004 Thomas "tom" S. <tom@eggdrop.ch>
 *
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <sys/time.h>
#include <time.h>
#include "perftest.h"

long summary;

void show_status(int reset)
{
  static long t = -1;
  long i;
  t++;

  printf("\r[");

  if (reset)
  {
    t = -1;
    i = TIMES-1;
    while (i-- > 0)
      printf("=");
    printf(">]\n");
    return;
  }
  
 
  if (t)
  {
    i = t-1;
    while (i-- > 0)
      printf("=");
  }

  if (t)
    printf(">");

  i = TIMES-t;

  while (i-- > 0)
    printf(" ");

  printf("]");

  fflush(stdout);

}

void stopwatch(void)
{
  static int mode = 0; /* 0 = stopped, 1 = running */
  struct timeval tv;
  struct timezone tz;
  static long last;
  long current, difference;
  double double_diff;

  mode =! mode;

  gettimeofday(&tv, &tz);

  if (mode == 0)
  {
    current = tv.tv_sec*1000 + tv.tv_usec/1000;
    difference = current-last;
    summary += difference;
    double_diff = difference/1000.0;
    printf("Result: %3.3lf\n", double_diff);
  }

  if (mode != 0)
    last = tv.tv_sec*1000 + tv.tv_usec/1000;
}

void runtest(int num, char *description, void (*function)(void))
{
  stopwatch(); /* start */
  printf("\nRunning test %d: %s\n", num, description);
  function();
  show_status(1);
  stopwatch(); /* stop */
}

int main(int argc, char *argv[])
{
  double double_sum;
  summary = 0;

  runtest(1, "addition and subtraction", test1);
  runtest(2, "multiplication and division", test2);
  runtest(3, "floating point", test3);
  runtest(4, "file i/o: 1 KB (you need 1 MB free space)", test4);
  runtest(5, "file i/o: 1 MB (you need 8 MB free space)", test5);
  runtest(6, "memory i/o (1 KB)", test6);
  runtest(7, "memory i/o (1 MB)", test7);
  runtest(8, "processes", test8);
  runtest(9, "threads", test9);

  double_sum = summary/1000.0;
  printf("\nTotal time: %3.3lf\t\tScore: %ld points\n\n", \
      double_sum, 10000000/summary);
  
  return 0;
}
