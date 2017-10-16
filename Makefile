# Makefile
 
CC = gcc #-fsanitize=address
CPPFLAGS = -MMD
CFLAGS =  -Wall -Wextra -std=c99 -O0 -g 
LDFLAGS =
LDLIBS = -lm
 
OBJ = Appel.o XOR_propre.o network_test.o network_value_calculus.o personal_math_functions.o network_transformations.o
OBJ2 = XOR_propre.o network_test.o network_value_calculus.o personal_math_functions.o network_transformations.o
DEP = ${OBJ:.o=.d}
 
all: XOR_propre

appel: Appel
 
Appel: ${OBJ}

XOR_propre: ${OBJ2}
 
.PHONY: clean
 
clean:
	${RM} ${OBJ} ${DEP} Appel
 
-include ${DEP}
 
# END
