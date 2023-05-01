# Author:			Tristan S. Tutungis
# Date Created:		25/4/2023
# Last Modified:	25/4/2023 20:30

CFLAGS = -Wall -Wextra -g
OBJ = 
EXEC = cq
CC = gcc

# Linking of executable
$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

# Compilation of object files


queue.o : queue.c queue.h cust.h
	$(CC) $(CFLAGS) -c queue.c