NAME := testing
CFLAGS := -I src/incl/ -I thirdparty/ -lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++17
CC := g++

cpp_source_files := $(shell find src/impl/ -name *.cpp)

.PHONY: build_debug

build_debug:
	echo $(cpp_source_files)
	mkdir -p build/debug
	$(CC) $(cpp_source_files) $(CFLAGS) -ggdb -o build/debug/$(NAME).bin

build_release:
	echo $(cpp_source_files)
	mkdir -p build/release
	$(CC) $(cpp_source_files) $(CFLAGS) -O3 -s -o build/release/$(NAME).bin

run:
	./build/debug/$(NAME).bin

run_release:
	./build/release/$(NAME).bin

clean:
	rm -rf build
