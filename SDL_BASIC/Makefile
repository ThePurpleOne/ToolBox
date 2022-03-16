CC       := gcc
CFLAGS   := -Wall -Wextra -g -fsanitize=address -fsanitize=leak

BIN     	 := bin
SRC     	 := src
INCLUDE 	 := include
LIBRARIES    := -lm -lSDL2
EXECUTABLE   := main

# ADD ALL THE SOURCES FOR EXECUTABLE1
SOURCES += $(SRC)/$(EXECUTABLE).c
SOURCES += $(SRC)/j_sdl.c
SOURCES += $(SRC)/gfx.c

.PHONY: all run prebuild clean # Specify these are not files but internal terms

all: prebuild $(BIN)/$(EXECUTABLE)

prebuild:
	@mkdir -p $(BIN)

run: clean all
	clear
	@echo "########## EXECUTE FIRST PROGRAM ##########"
	./$(BIN)/$(EXECUTABLE)

main : build/main.o build/gfx.o
	$(CCC) -o main $(BUILD)/main.o $(BUILD)/gfx.o $(OPT) 

clean:
	@echo "########## CLEANING ##########"
	-rm $(BIN)/*

# COMPILE MAIN EXECUTABLE
$(BIN)/$(EXECUTABLE): $(SOURCES)
	@echo "########## COMPILING FIRST EXECUTABLE ##########"
	$(CC) $(CFLAGS) -I $(INCLUDE) $^ -o $@ $(LIBRARIES)
