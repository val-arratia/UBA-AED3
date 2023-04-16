CC = g++
CPPFLAGS = -g -std=c++11 -Wall -pedantic
OUTPUT_PATH := bin
OUTPUT_FILENAME := ej11

.PHONY: all clean

all: ej11

ej11: ej11.cpp
	@mkdir -p $(OUTPUT_PATH)
	$(CC) $(CPPFLAGS) $< -o $(OUTPUT_PATH)/$(OUTPUT_FILENAME)

clean:
	rm -f *.o
	rm -rf $(OUTPUT_PATH)