
CC=gcc
CFLAGS=-Wall -Wextra
LDFLAGS=
LIB_OBJS=obj/lib/aes256.o
OBJS=obj/main.o obj/encrypt.o obj/misc.o
BIN=file-encrypter.out

.PHONY: all run clean

all: $(BIN)

run: $(BIN)
	./$<

# -------------------------------------------

$(BIN): $(OBJS) $(LIB_OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

$(OBJS): obj/%.o : src/%.c
	@mkdir -p obj		# Don't like calling mkdir each obj but whatever
	$(CC) $(CFLAGS) -c -o $@ $< $(LDFLAGS)

# -------------------------------------------

$(LIB_OBJS): obj/lib/%.o : src/lib/%.c
	@mkdir -p obj/lib
	$(CC) $(CFLAGS) -c -o $@ $<

# -------------------------------------------

clean:
	rm -f $(OBJS) $(BIN)
