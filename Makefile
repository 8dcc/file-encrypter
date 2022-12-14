
CC=gcc
CFLAGS=-Wall
LDFLAGS=
OBJS=obj/main.o obj/encrypt.o obj/misc.o
BIN=file-encrypter.out

.PHONY: all run clean

all: $(BIN)

run: $(BIN)
	./$<

# -------------------------------------------

$(BIN): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

$(OBJS): obj/%.o : src/%.c
	@mkdir -p obj			# Don't like calling mkdir each obj but whatever
	$(CC) $(CFLAGS) -c -o $@ $< $(LDFLAGS)

# -------------------------------------------
# TODO: Lib

# -------------------------------------------

clean:
	rm -f $(OBJS) $(BIN)
