CC = gcc
CFLAGS = -Wall -Wextra 

vpath %.h ./include
vpath %.c ./src

objects = main.o cgol.o

cgol : $(objects)
	$(CC) $^ -o $@

main.o : main.c cgol.h
	$(CC) $(CFLAGS) -c $< -o $@ 

cgol.o : cgol.c cgol.h
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY : clean
clean :  
	rm cgol $(objects)  