brickWallSolutions: BrickWallSolutions.o NeighborsTree.o main.o
	g++ main.cpp BrickWallSolutions.cpp NeighborsTree.cpp -o brickWallSolutions

clean:
	rm *.o brickWallSolutions

test: BrickWallSolutions.o NeighborsTree.o main.o BrickWallSolutionsTest.o
	g++ main.cpp BrickWallSolutions.cpp NeighborsTree.cpp BrickWallSolutionsTest.cpp -o brickWallSolutions -DTESTBUILD
