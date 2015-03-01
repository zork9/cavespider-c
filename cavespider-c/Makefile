CC=gcc

OBJS=parsing.o file.o globals.o main.o network.o

all: cavespider

cavespider: $(OBJS)
	$(CC) -g -o cavespider $(OBJS)

clean:
	rm *.o cavespider

.c.o:
	$(CC) -g -c $<
