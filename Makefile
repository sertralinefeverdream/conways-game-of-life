CC = gcc
CFLAGS = -Wall -Wextra 

vpath %.h ./include
vpath %.c ./src

objects = main.o

cgol : $(objects)
	$(CC) $^ -o $@

main.o : main.c
	$(CC) $(CFLAGS) -c $< -o $@ 

.PHONY : clean
clean :  
	rm cgol $(objects)  