#makefile


TARGET=main
DEPS=$(patsubst %.c,%,$(wildcard src/*.c))
GENS=$(patsubst %.cpp,%,$(wildcard generated/*.cpp))

CC=g++

INCS=-I./include -I./generated
LIBS=$(shell pkg-config --libs opencv) -lpthread -lSpider

CFLAGS=-fpic $(INCS) -O0
CPPFLAGS=$(CFLAGS)

all: $(TARGET)

test: proper all
	./$(TARGET)

$(TARGET): $(patsubst %,%.o,$(DEPS)) $(patsubst %,%.o,$(GENS))
	$(CC) -o $@ $^ $(LIBS)


generated/%.o: %.cpp $(wildcard include/*.h)
	$(CC) -c $(CFLAGS) $< -o $@
	
src/%.o: %.c $(wildcard include/*.h)
	$(CC) -c $(CFLAGS) $< -o $@


clean:
	rm -rfv *.o src/*.o generated/*.o

proper: clean
	rm -rfv $(TARGET)
