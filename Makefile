
CC=gcc
CFLAGS=-Wall
LDFLAGS=
OBJS=obj/main.o obj/misc.o obj/encrypt.o
BIN=file-encrypter.out

.PHONY: all run clean

all: $(BIN)

run: $(BIN)
	./$<

# obj folder
obj:
	mkdir -p obj

# -------------------------------------------

$(BIN): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

$(OBJS): obj/%.o : src/%.c obj
	$(CC) $(CFLAGS) -c -o $@ $< $(LDFLAGS)

# -------------------------------------------
# TODO: Lib

# -------------------------------------------

clean:
	rm -f $(GAME_OBJS)
	rm -f $(GAME_BIN)
	rm -f $(SOLVER_OBJS)
	rm -f $(SOLVER_BIN)
