.PHONY: clean run

BIN_DIR = bin
SOURCES = $(wildcard src/*.c)
OBJECTS = $(SOURCES:.c=.o)
CFLAGS =

ifdef DEBUG
	CFLAGS += "-DDEBUG"
endif

all: run

%.o: %.c src/app.c
	$(CC) $(CFLAGS) -I include -I lib -c $< -o $@

src/app.c: app.rb
	mrbc -B app -o $@ $^

bin/iron-rb: $(OBJECTS) src/app.o
	@mkdir -p $(BIN_DIR)
	$(CC) -o $@ $^

clean:
	rm -rf $(BIN_DIR)/*
	rm -rf src/app.c
	rm -rf src/*.o

run: clean bin/iron-rb
	@bin/iron-rb
