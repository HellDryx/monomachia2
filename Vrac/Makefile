## Simple SDL mini code
 
CC=gcc
 
CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -std=c99 -O3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL_image
 
OBJ= Vrac.o
DEP= ${SRC:.o=.d}
 
all: Vrac
 
main: ${OBJ}
 
clean:
	rm -f Vrac Vrac.d Vrac.o 
	
 
-include ${DEP}
 
# END
