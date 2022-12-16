
CC=gcc
CFLAGS=-Wall -Wextra
LDFLAGS=
LIB_OBJS=obj/lib/aes256.o obj/lib/md5.o
OBJS=obj/main.o obj/encrypt.o obj/misc.o
BIN=file-encrypter.out

.PHONY: all run clean install uninstall

all: $(BIN)

run: $(BIN)
	./$<

# -------------------------------------------

$(BIN): $(OBJS) $(LIB_OBJS)
	$(CC) -o $@ $(OBJS) $(LIB_OBJS) $(LDFLAGS)

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

install: $(BIN)
	install --mode=0755 $< /usr/local/bin/file-encrypter
	mkdir -p /usr/local/share/man/man1/
	install --mode=0644 file-encrypter.1 /usr/local/share/man/man1/

uninstall: $(BIN)
	rm -f /usr/local/bin/file-encrypter
	rm -f /usr/local/share/man/man1/file-encrypter.1

