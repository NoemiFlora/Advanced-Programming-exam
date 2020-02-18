EXE = main
CXX = g++
CXXFLAGS = -c -Wextra -Wall -std=c++14 -I include
SRC = src/main.cc
OBJ = $(SRC:.cc=.o)
INC = include/bst.hpp

default: $(EXE)

$(EXE): main.o
		$(CXX) $< -o $@

main.o: $(SRC)
		$(CXX) $< $(CXXFLAGS)

main.o: $(INC)

clean:
		rm -rf $(OBJ) $(EXE) src/*~ include/*~ *~ html latex main.o
