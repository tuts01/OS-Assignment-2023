# Author:			Tristan S. Tutungis
# Date Created:		25/4/2023
# Last Modified:	7/5/2023 20:00

CFLAGS = -Wall -Wextra -g -pthread -Werror
OBJ = cq.o cust.o fileio.o misc.o queue.o teller.o
EXEC = cq
CC = gcc

# Linking of executable
$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) -pthread

# Compilation of object files
cq.o : cq.c cust.c cust.h queue.c queue.h fileio.c fileio.h teller.c teller.h misc.c misc.h
	$(CC) $(CFLAGS) -c cq.c

cust.o : cust.c cust.h queue.c queue.h fileio.c fileio.h misc.c misc.h
	$(CC) $(CFLAGS) -c cust.c

teller.o : teller.c teller.h queue.c queue.h misc.c misc.h cust.c cust.h
	$(CC) $(CFLAGS) -c teller.c

fileio.o : fileio.c fileio.h cust.c cust.h
	$(CC) $(CFLAGS) -c fileio.c

queue.o : queue.c queue.h cust.c cust.h
	$(CC) $(CFLAGS) -c queue.c

misc.o : misc.c misc.h
	$(CC) $(CFLAGS) -c misc.c

clean :
	rm $(OBJ) $(EXEC)
