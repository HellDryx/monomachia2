# Makefile

CC = gcc -fsanitize=address
CPPFLAGS = `pkg-config --cflags sdl` -MMD
CFLAGS =  -Wall -Wextra -std=c99
LDFLAGS =
LDLIBS = `pkg-config --libs sdl` -lSDL_image -lm

OBJ2 = XOR_propre.o network_transformations.o matrix_creation.o Save.o Detection.o sdl_functions.o
DEP = ${OBJ2:.o=.d}

all: Detection

Detection: ${OBJ2}

.PHONY: clean

clean:
	${RM} ${OBJ2}
	${RM} ${DEP}
	${RM} Detection

-include ${DEP}

# END
