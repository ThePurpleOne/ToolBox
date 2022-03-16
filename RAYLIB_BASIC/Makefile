CC       := gcc
CC_FLAGS := -Wall -Wextra 

BIN     	:= bin
SRC     	:= src
INCLUDE 	:= include
LIB     	:= lib
LIBRARIES   := -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
EXECUTABLE  := main

.PHONY :all run prebuild clean

all: prebuild $(BIN)/$(EXECUTABLE)

run: clean all
	clear
	@echo "Executing..."
	./$(BIN)/$(EXECUTABLE)

prebuild :
	@mkdir -p $(BIN)

clean:
	@echo "Clearing..."
	-rm $(BIN)/*

$(BIN)/$(EXECUTABLE): $(SRC)/*.c
	@echo "Building..."
	$(CC) $(CC_FLAGS) -I $(INCLUDE) -L $(LIB) $^ -o $@ $(LIBRARIES)
