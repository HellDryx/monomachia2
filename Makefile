# Makefile
 
CC = gcc #-fsanitize=address
CPPFLAGS = -MMD
CFLAGS =  -Wall -Wextra -std=c99 -O0 -g 
LDFLAGS =
LDLIBS = -lm
 
OBJ2 = XOR_propre.o network_value_calculus.o personal_math_functions.o network_transformations.o printing_functions.o
DEP = ${OBJ2:.o=.d}
 
all: XOR_propre

XOR_propre: ${OBJ2}
 
.PHONY: clean
 
clean:
	${RM} ${OBJ2} ${DEP} Appel
 
-include ${DEP}
 
# END
