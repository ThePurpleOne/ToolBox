CC       := gcc
CFLAGS := -Wall -Wextra -g -fsanitize=address -fsanitize=leak

BIN     	 := bin
SRC     	 := src
INCLUDE 	 := include
LIBRARIES    := -lm -lSDL2 -lGLEW -lGLU -lGL -lglut
EXECUTABLE   := main
TEST_EXE   := test

SOURCES += $(SRC)/$(EXECUTABLE).c

TEST_SOURCES += $(SRC)/$(TEST_EXE).c

.PHONY: all run test clean prebuild

all: prebuild $(BIN)/$(EXECUTABLE) $(BIN)/$(TEST_EXE)

run: clean all
	@echo "########## EXECUTE FIRST PROGRAM ##########"
	./$(BIN)/$(EXECUTABLE)

test: $(BIN)/$(TEST_EXE)
	./$(BIN)/$(TEST_EXE)

prebuild:
	@mkdir -p $(BIN)

clean:
	@echo "########## CLEANING ##########"
	-rm $(BIN)/*

# COMPILE FIRST EXECUTABLE
$(BIN)/$(EXECUTABLE): $(SOURCES)
	@echo "########## COMPILING FIRST EXECUTABLE ##########"
	$(CC) $(CFLAGS) -I $(INCLUDE) $^ -o $@ $(LIBRARIES)

# COMPILE TEST EXECUTABLE
$(BIN)/$(TEST_EXE): $(TEST_SOURCES)
	@echo "########## COMPILING TEST EXECUTABLE ##########"
	$(CC) $(CFLAGS) -I $(INCLUDE) $^ -o $@ $(LIBRARIES)

