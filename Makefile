#CC = gcc -fPIC
#CFLAGS = -Wall `sdl-config --cflags`
#LIBS = `sdl-config --libs` -lm -lSDL_ttf -lSDL_image

#%: %.c
#	rm -f $@
#	$(CC) $(CFLAGS) $@.c -o $@ $(LIBS)


#variable du compilateur gcc
CC = g++

#The final ecacutable name
EXEC = app

#All files with .c extension
SRC = $(wildcard *.cpp)

#All files with .c are copied with .o extension
OBJ = $(SRC:.c=.o)

all : app
myShell : main.o
$(EXEC) : $(OBJ)
	$(CC) -o $@ $^
%.o : %.c
	$(CC) -o $@ -c $<
clean:
	rm -rf *.o
mrproper : clean
	rm -rf $(EXEC)