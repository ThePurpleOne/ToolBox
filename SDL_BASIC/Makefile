#arguments $(arg)
CCC = gcc
OPT = -lm -lSDL2
BUILD = build
SRC = src


all : main

pre-build:
	mkdir -p build/

main : build/main.o build/gfx.o
	$(CCC) -o main $(BUILD)/main.o $(BUILD)/gfx.o $(OPT) 

build/main.o : $(SRC)/main.c
	$(CCC) -o $(BUILD)/main.o -c $(SRC)/main.c $(OPT) 

build/gfx.o : $(SRC)/gfx.c
	$(CCC) -o $(BUILD)/gfx.o -c $(SRC)/gfx.c $(OPT)