#
# Makefile
#
CC=gcc

CFLAGS=-I -Wall -Wextra

#DEBUG=-DDMULT

default:         a.out
veclib.o:		 veclib.c
main.o:          main.c

# Build the executable 
a.out: veclib.o main.o
	$(CC) $(CFLAGS) $(DEBUG) $^ $(LIBS) -lm

# Clean out all transient files
clean:
	$(RM) a.out *.o
	$(RM) info

# Run the executable through valgrind
valgrind: a.out
	valgrind --leak-check=full --malloc-fill=AA --free-fill=BB ./a.out

# Run the executable through gdb
gdb: a.out
	gdb ./a.out

# Just run the executable
run: a.out
	./a.out 2> info
