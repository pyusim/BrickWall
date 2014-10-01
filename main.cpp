#include <iostream>
#include <ctime>

#include "BrickWallSolutions.h"

#ifdef TESTBUILD
#include "BrickWallSolutionsTest.h"
#endif

using namespace std;

// When called with no arguments, this program will return the number of possible tilings for a 32x8 wall.
// Otherwise, the usage is progname W R [-v], where W is the width, R is number of rows, and the -v option makes the output verbose.
// Verbose output shows the dimensions of the wall and the time it took (in seconds) to calculate the number of solutions.
int main(int argc, char * argv[])
{
  int width = 32;
  int rows = 10;

  if (argc >=3)
    {
      width = atoi(argv[1]);
      rows = atoi(argv[2]);
    }

#ifndef TESTBUILD

  try
    {
      BrickWallSolutions brickWallSolutions(width, rows);
  
      unsigned long solutions = brickWallSolutions.getNumPossibleSolutions();

      cout << solutions << endl;
    }
  catch (std::string & e)
    {
      cout << "Exception: " << e << endl;
    }

#else
  
  BrickWallSolutionsTest::run();

#endif

  return 0;
}
