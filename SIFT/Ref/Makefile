CXX     := g++
CFLAGS  := -O2 -Wall -Iinclude/

BIN_SEQ := build/image_match-seq build/feature_extract-seq
BIN_SRC_SEQ := examples/image_match.cpp examples/feature_extract.cpp
LIB_SEQ := build/libezsiftseq.so
LIB_SRC_SEQ := src/ezsift-seq.cpp src/img_io.cpp
LIB_OBJ_SEQ := build/ezsift-seq.o build/img_io.o

BIN_PAR := build/image_match-par build/feature_extract-par
BIN_SRC_PAR := examples/image_match.cpp examples/feature_extract.cpp
LIB_PAR := build/libezsiftpar.so
LIB_SRC_PAR := src/ezsift-par.cpp src/img_io.cpp
LIB_OBJ_PAR := build/ezsift-par.o build/img_io.o

all: $(BIN_SEQ) $(BIN_PAR) $(BIN_PREESM)

build/%-seq:  examples/%.cpp $(LIB_SEQ)
	$(CXX) $(CFLAGS) -Wl,-rpath='$$ORIGIN/'. -o $@ $< -L./build/ -lezsiftseq

$(LIB_SEQ): $(LIB_OBJ_SEQ)
	$(CXX) $(CFLAGS) -Wl,-soname=libezsiftseq.so -o $@ $^ -shared -fPIC

build/%-par:  examples/%.cpp $(LIB_PAR)
	$(CXX) $(CFLAGS) -Wl,-rpath='$$ORIGIN/'. -o $@ $< -L./build/ -lezsiftpar

$(LIB_PAR): $(LIB_OBJ_PAR)
	$(CXX) $(CFLAGS) -Wl,-soname=libezsiftpar.so -o $@ $^ -shared -fPIC -fopenmp



build/%.o: src/%.cpp include/*.h
	mkdir -p build/
	$(CXX) $(CFLAGS) -c $< -o $@ -fPIC -fopenmp



clean:
	rm -rf $(LIB_OBJ_SEQ) $(LIB_SEQ) $(BIN_SEQ) $(LIB_OBJ_PAR) $(LIB_PAR) $(BIN_PAR)
