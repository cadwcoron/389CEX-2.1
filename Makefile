COMPILE=gcc
STD=-std=c99 
CFLAGS=-Wall -Werror -Wextra -pedantic -O3


make: accesstime.c
	$(COMPILE) $(STD) $(CFLAGS) -o accesstime accesstime.c

clean:
	rm accesstime