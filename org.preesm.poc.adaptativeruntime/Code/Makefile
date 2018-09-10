#makefile


TARGET=main
DEPS=$(patsubst %.c,%,$(wildcard src/*.c))
GENS=$(patsubst %.cpp,%,$(wildcard generated/*.cpp))

CC=g++

INCS=-I./include -I./generated
LIBS=$(shell pkg-config --libs opencv) -lpthread -lSDL2 -lSDL2_ttf -lSDL2main  -lSpider

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

install_odroid_deps:
	sudo apt update
	sudo apt upgrade -y
	sudo apt install -y libsdl2-ttf-dev


scheduler_get:
	@echo -n "A7: "
	@cat /sys/bus/cpu/devices/cpu0/cpufreq/scaling_governor
	@echo -n "A15: "
	@cat /sys/bus/cpu/devices/cpu4/cpufreq/scaling_governor

scheduler_set_ondemand:
	echo "ondemand" | sudo tee /sys/bus/cpu/devices/cpu0/cpufreq/scaling_governor
	echo "ondemand" | sudo tee /sys/bus/cpu/devices/cpu4/cpufreq/scaling_governor

scheduler_set_performance:
	echo "performance" > /sys/bus/cpu/devices/cpu0/cpufreq/scaling_governor
	echo "performance" > /sys/bus/cpu/devices/cpu4/cpufreq/scaling_governor

demo: scheduler_set_ondemand proper
	EnergyMonitor &
	$(MAKE) test
