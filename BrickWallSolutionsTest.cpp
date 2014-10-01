#include "BrickWallSolutions.h"
#include "BrickWallSolutionsTest.h"
#include "Constants.h"

#include <iostream>

using namespace std;

void BrickWallSolutionsTest::run()
{
  runTestCase(16, 6, 5218);
  runTestCase(20, 6, 156684);
  runTestCase(20, 7, 784344);
  runTestCase(21, 7, 2059492);
  runTestCase(22, 7, 5629686);
  runTestCase(25, 8, 870875826);
  runTestCase(26, 8, 2617507202);
  runTestCase(27, 8, 7735113546);
  runTestCase(32, 10, 806844323190414);
  runTestCase(MAX_ROW_WIDTH+1, 10, 0);
  runTestCase(5, -1, 0);
  runTestCase(-1, 1, 0);
}

void BrickWallSolutionsTest::runTestCase(int width, int rows, unsigned long expectedValue)
{
  unsigned long result = 0;

  clock_t startTime = clock();
  
  try
    {
      
      BrickWallSolutions brickWallSolutions(width, rows);

      result = brickWallSolutions.getNumPossibleSolutions();

      double secondsElapsed =  (clock() - startTime) / CLOCKS_PER_SEC;
      
      cout << width << "x" << rows << " -> " <<  result << " solutions found in " << secondsElapsed << " seconds";
    }
  catch (std::string & e)
    {
      cout << "Exception: " << e << endl;
    }  

  if (result == expectedValue)
    {
      cout << " >>> PASSED <<<" << endl;
    }
  else
    {
      cout << " >>> FAILED <<<" << endl;
    }
}
