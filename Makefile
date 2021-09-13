CC=gcc
CFLAGS=-Wall
LIBS=-lpthread
OBJS=perftest.o test1.o test2.o test3.o test4.o test5.o test6.o test7.o \
test8.o test9.o

perftest:	$(OBJS)
		$(CC) $(LIBS) -o perftest *.o

.c.o:		
		$(CC) $(CFLAGS) -c $< -o $@

clean:		
		rm -f *.o
