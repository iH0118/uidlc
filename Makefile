CC     := gcc
CFLAGS := -I../../include -O -Wall -Wextra -Wno-unused-parameter -c -g

OUTPUT := build/uidlc
SRCS   := $(shell find src -name '*.c')
OBJS   := $(patsubst src/%.c,build/%.o,$(SRCS))

build: $(OUTPUT)

clean:
	rm -f $(wildcard build/*.o)

clean_all: clean
	rm -f $(OUTPUT)

$(OUTPUT): $(OBJS) 
	$(CC) -o $@ $^ $(LDFLAGS)

build/%.o: src/%.c
	$(CC) $(CFLAGS) -o $@ $<

src/%.c: src/%.h src/uib_structs.h

.PHONY: build clean clean_all