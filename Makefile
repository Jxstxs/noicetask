CC=gcc
CFLAGS=-Wall
DEBUG=-g
RELEASE=-O2
CLIBS=-l sqlite3

BINDIR=bin
SRCDIR=src
OBJDIR=obj
INST_DEST=/usr/bin

SRCS=$(wildcard $(SRCDIR)/*.c)
OBJS=$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))
BIN=nt

all: $(BIN)

bindir:
	mkdir -p $(BINDIR)

objsdir:
	mkdir -p $(OBJDIR)

$(BIN): $(OBJS) bindir
	$(CC) $(CFLAGS) $(OBJS) $(CLIBS) -o $(BINDIR)/$(BIN)

debug: $(OBJS) bindir
	$(CC) $(DEBUG) $(CFLAGS) $(OBJS) $(CLIBS) -o $(BINDIR)/debug

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(SRCDIR)/%.h objsdir
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BINDIR)/* $(OBJDIR)/* test/*.o

install: $(TARGET)
	sudo cp $(BINDIR)/$(BIN) $(INST_DEST)

run: $(BIN)
	./$(BINDIR)/$(BIN)


# TESTS

test: tests/test.c bindir
	$(CC) $(CFLAGS) -o $(BINDIR)/test tests/test.c

test-argparse: tests/argparse-test.c src/argparse.c tests/printConf.c bindir
	$(CC) $(CFLAGS) tests/argparse-test.c src/argparse.c tests/printConf.c -o $(BINDIR)/argparse-test

test-additional: tests/additional-tests.c src/additional.c bindir
	$(CC) $(CFLAGS) tests/additional-tests.c src/additional.c -o $(BINDIR)/additional-test

tests: test-argparse
