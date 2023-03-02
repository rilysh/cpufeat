CC ?= gcc
PROG = cpufeat
FLAGS = -Wall -O2 -s -fPIE

all:
	@$(CC) $(FLAGS) $(PROG).c -o $(PROG)

clean:
	@rm $(PROG)
