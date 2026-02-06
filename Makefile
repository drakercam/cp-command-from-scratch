CC = gcc
SRC = cp.c
OUT = cp
FLAGS = -Wall -Werror

$(OUT): $(SRC)
	${CC} ${FLAGS} ${SRC} -o ${OUT}

run:
	./${OUT}

clean:
	rm ${OUT}
