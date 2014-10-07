SRC = interpreter.c
CC = gcc
CC_ARGS = -Wall -o
CC_DEBUG_ARGS = -g
BIN = escalonador_rr escalonador_sjf escalonador_pri

debug =	$(CC) $(CC_DEBUG_ARGS) $(CC_ARGS)$(2)$(1) $(SRC) -lm
compile = $(CC) $(CC_ARGS)$(2)$(1) $(SRC) -lm

main: rr sjf pri
	@echo "** Compiled Everything **"

rr:
	$(call debug, escalonador_rr.c, escalonador_rr)
	@echo "** Compiled  escalonador_rr**"

sjf:
	$(call debug, escalonador_sjf.c, escalonador_sjf)
	@echo "** Compiled  escalonador_sjf**"

pri:
	$(call debug, escalonador_pri.c, escalonador_pri)
	@echo "** Compiled  escalonador_pri**"

clean:
	rm -f *.o *.bin $(BIN)

.PHONY: main rr sjf pri
