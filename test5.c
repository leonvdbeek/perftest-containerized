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

#include <strings.h>
#include "perftest.h"

void test5(void)
{
  FILE *f;
  long i, j;
  int tmp=0;
  char str[1048576];

  bzero(str, sizeof(str));

  for (i=0;i<TIMES/8;i++)
  {
    f = tmpfile();

    /* write */
    for (j=0;j<8;j++)
    {
      tmp =! tmp;
      if (tmp) show_status(0);
      if (!fwrite(str, sizeof(str), 1, f))
        printf("\nError writing file\n");
    }

    rewind(f);

    /* read */
    for (j=0;j<8;j++)
    {
      tmp =! tmp;
      if (tmp) show_status(0);
      if (!fread(str, sizeof(str), 1, f))
        printf("\nError reading file\n");
    }

    fclose(f);
  }
}
