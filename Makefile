#CXX = g++ -std=gnu++11 -O3 -Wall -Wpedantic -Wextra
CXX = $(CROSS_COMPILE_PREFIX)g++ $(CROSS_COMPILE_SWITCHES) -std=gnu++11 -O3 -Wall -Wextra -pedantic -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wundef -Wno-unused -Wno-variadic-macros -Wno-parentheses -fdiagnostics-show-option

MAIN_BINARIES = $(addprefix Build/, $(basename $(wildcard **/*Main.cpp) $(wildcard *Main.cpp)))
TEST_BINARIES = $(addprefix Build/, $(basename $(wildcard **/*Test.cpp) $(wildcard *Test.cpp)))

HEADER = $(wildcard **/*.h)
OBJECTS = $(addprefix Build/, $(addsuffix .o, $(basename $(filter-out %Main.cpp %Test.cpp, $(wildcard **/*.cpp) $(wildcard *.cpp)))))

CPPLINT_PATH = ../cpplint.py

.PRECIOUS: Build/%.o

all: clean compile test

compile: compile/main compile/test

compile/test: $(TEST_BINARIES)

compile/main: $(MAIN_BINARIES)

run: run/sokoban

test: $(TEST_BINARIES)
	@echo ----------------------------------------------------------------------
	@echo testing ...
	@for T in $(TEST_BINARIES); do ./$$T; done

run/solver: Build/SolverMain
	@echo ----------------------------------------------------------------------
	@echo running solver ...
	@./Build/SolverMain ../Levels

run/sokoban: Build/SokobanMain
	@echo ----------------------------------------------------------------------
	@echo running sokoban ...
	@./Build/SokobanMain -x 4 -y 3 Levels
	
checkstyle:
	@echo ----------------------------------------------------------------------
	@echo checking ...
	@echo checking header ...
	@python $(CPPLINT_PATH) *.h */*.h
	@echo ----------------------------------------------------------------------
	@echo checking source ...
	@python $(CPPLINT_PATH) *.cpp */*.cpp
	@echo ----------------------------------------------------------------------

clean:
	@echo ----------------------------------------------------------------------
	@echo cleaning ...
	@rm -rf Build/*
	@echo ----------------------------------------------------------------------

Build/%Main: Build/%Main.o $(OBJECTS)
	$(CXX) -g -o $@ $^ -lncurses

Build/%Test: Build/%Test.o $(filter-out Build/Game/%.o Build/Display/%.o, $(OBJECTS))
	$(CXX) -g -o $@ $^ -lgtest_main -lgtest -lpthread

Build/%.o: %.cpp $(HEADER)
	@mkdir -p $(shell dirname $@) || true
	$(CXX) -g -c -o $@ $<
