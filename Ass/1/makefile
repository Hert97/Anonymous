CC = gcc
CFLAGS = -Wall -Werror -Wconversion -pedantic-errors -Wextra -Wstrict-prototypes -std=c11

SRC = assignment.c
EXE = assignment

IN_SAME_PRIORITY = input_same_priority.txt
IN_SAME_ARRIVAL = input_same_arrival.txt

in = ${IN_SAME_PRIORITY}

all: build
	./${EXE} ${in}

build: ${SRC}
	${CC} ${CLAGS} ${SRC} -o ${EXE}