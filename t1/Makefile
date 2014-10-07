SRC = interpreter.c
CC = gcc
CC_ARGS = -Wall -o
CC_DEBUG_ARGS = -g
BIN = escalonador_rr

debug =	$(CC) $(CC_DEBUG_ARGS) $(CC_ARGS)$(2)$(1) $(SRC) -lm
compile = $(CC) $(CC_ARGS)$(2)$(1) $(SRC) -lm

main: rr
	@echo "** Compiled Everything **"

rr:
	$(call debug, escalonador_rr.c, escalonador_rr)
	@echo "** Compiled  escalonador_rr**"

clean:
	rm -f *.o *.bin $(BIN)

.PHONY: main rr
