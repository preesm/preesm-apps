#makefile


TARGET=main

CC=g++

INCS=
LIBS=$(shell pkg-config --libs opencv)

CFLAGS=-Wall -Wextra -fpic
# -Werror

all: $(TARGET)

test: $(TARGET)
	./$(TARGET)

$(TARGET): $(TARGET).o
	$(CC) -o $@ $^ $(LIBS)

$(TARGET).o: $(TARGET).c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -rf *.o

proper: clean
	rm -rf $(TARGET)
