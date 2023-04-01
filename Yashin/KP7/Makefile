CXX       := g++
CXX_FLAGS := -std=c++17 -Wall -fsanitize=address

BIN     := bin
SRC     := src
INCLUDE := include
LIB     := lib
TESTS   := tests
LIBRARIES   := -lstdc++ -lm
EXECUTABLE  := main

build: $(BIN)/$(EXECUTABLE)

run: clean build
	clear
	@echo "Executing..."
	$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp | $(BIN)
	@echo "Building..."
	$(CXX) $(CXX_FLAGS) -I $(INCLUDE) -L $(LIB) $^ -o $@ $(LIBRARIES)

$(TESTS)/$(EXECUTABLE): $(SRC)/*.cpp
	@echo "Building..."
	$(CXX) $(CXX_FLAGS) -I $(INCLUDE) -L $(LIB) $^ -o $@ $(LIBRARIES)

$(BIN):
	mkdir $@

clean:
	@echo "Clearing..."
	-rm $(BIN)/*

test: clean
	clear
	@echo "Run tests..."
	./$(TESTS)/$(EXECUTABLE)



