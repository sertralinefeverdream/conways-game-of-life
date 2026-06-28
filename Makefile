CC = gcc
CFLAGS = -std=c23 -Wall -Wextra 
BUILDDIR = ./build
EXEC_NAME = conways-game-of-life

vpath %.h ./include
vpath %.c ./src

OBJECTS = main.o cgol.o render.o

$(BUILDDIR)/$(EXEC_NAME) : $(patsubst %.o,$(BUILDDIR)/%.o, $(OBJECTS))
	mkdir -p $(BUILDDIR)
	$(CC) $^ -o $@
# rm $(patsubst %.o,$(BUILDDIR)/%.o,$(OBJECTS)) Optionally remove object files

$(BUILDDIR)/main.o : main.c cgol.h
	mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@ 

$(BUILDDIR)/cgol.o : cgol.c cgol.h
	mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@
	
$(BUILDDIR)/render.o : render.c render.h cgol.h
	mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY : clean
clean :  
	rm -rf $(BUILDDIR) 