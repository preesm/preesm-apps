#makefile


TARGET=main
DEPS=image

CC=g++

INCS=
LIBS=$(shell pkg-config --libs opencv)

CFLAGS=-Wall -Wextra -fpic -Werror

all: $(TARGET)

test: $(TARGET)
	./$(TARGET)

$(TARGET): $(TARGET).o $(patsubst %,%.o,$(DEPS))
	$(CC) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -rf *.o

proper: clean
	rm -rf $(TARGET)
