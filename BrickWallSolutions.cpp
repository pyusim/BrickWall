#include "BrickWallSolutions.h"

#include <sstream>
#include <iostream>

using namespace std;

BrickWallSolutions::BrickWallSolutions(const int width, const int rows)
  : m_width(width), m_rows(rows), m_neighborsTree(width)
{
  if (m_rows < 1)
    {
      stringstream errorStream;
      errorStream << "rows=" << m_rows << " is not a positive number";
      throw errorStream.str();
    }
}

// a recursive function to calculate the number of solutions starting with a particular row which holds a particular permutation:
// row - starting row
// permutationIndex - index of permutation of bricks in the row.  Its legal neighbors can be looked up in m_neighbors
// cache - saves the number of solutions r rows with permutation p in the row above in cache[p][r]
unsigned long BrickWallSolutions::calculateSolutions(const int row, const int permutationIndex, Cache & cache) const
{
  unsigned long result = 0;

  if (row == m_rows - 1)  // if we are at the bottom, return 1
    {
      return 1;
    }
  else // otherwise, sum up go through all possible solutions starting with this row
    {
      for (int i=0; i<m_neighborsTree.getNumNeighbors(permutationIndex); i++)
	{
	  if (cache[ m_neighborsTree.get(permutationIndex,i) ][ m_rows - row -1 ] != NO_VALUE)  // if we already have this value cached, use it
	    {
	      result += cache[ m_neighborsTree.get(permutationIndex,i) ][ m_rows - row - 1];
	    }
	  else                                                                           // otherwise call self recursively to obrain value and save it in cache
	    {
	      unsigned long numSolutions = calculateSolutions(row+1, m_neighborsTree.get(permutationIndex,i), cache);
	      cache[ m_neighborsTree.get(permutationIndex,i) ][ m_rows - row -1] = numSolutions;
	      result += numSolutions;
	    }
	}
    }

  return result;
}

// executes an algorithm based on building a legal neighbors tree and keeping a cache to find the number of possible way to tile a brick wall with bricks
// of length 2 and 3 without having cracks span more than one row
unsigned long BrickWallSolutions::getNumPossibleSolutions()
{
  Cache cache;

  cache.resize(m_neighborsTree.getNumPermutations());                                   // prepare an empty cache (initialized to NO_VALUE)
  
  for (int i=0; i<m_neighborsTree.getNumPermutations(); i++)
    {
      cache[i].assign(m_rows, NO_VALUE);
    }

  unsigned long solutions = 0;

  for (int i=0; i<m_neighborsTree.getNumPermutations(); i++)                            // call calculateSolutions for each possible permutation of the 1st (0th row)
    {
      solutions += calculateSolutions(0, i, cache);
    }

  return solutions;
}
