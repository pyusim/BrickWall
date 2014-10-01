#include "NeighborsTree.h"
#include "constants.h"

#include <sstream>

using namespace std;

NeighborsTree::NeighborsTree(const int width)
{
  if ((width > MAX_ROW_WIDTH) || (width < 2))
    {
      stringstream errorStream;
      errorStream << "width=" << width << " outside boundaries (2," << MAX_ROW_WIDTH << ")";
      throw errorStream.str();
    }

  m_neighbors.resize(numRowPermutations(width));

  build(width);
}

// build m_neighbors.  Represented as a vector of vectors, m_neighbors holds all the legal neighbors for each permutations.
// m_neighbors[p] is a list of all possible neighbors for a row that holds permutation p.
void NeighborsTree::build(const int width)
{
  Permutation edge = 1;

  edge <<= (width-1);

  Permutations permutations(1);

  buildRowPermutations(permutations, 0, edge);

  for (int i=0; i<m_neighbors.size(); i++)
    {
      for (int j=0; j<m_neighbors.size(); j++)
        {
          if ((permutations[i] & permutations[j]) == edge)       // two permutations can be neighbors if their bitwise AND only contains the edge value (wall edge)                                                                        
            {
              m_neighbors[i].push_back(j);
            }
        }
    }
}

// add a brick to a wall, represented as bitfield.  Shift bits by the number of bricks being added, then add a bit to represent a boundary
void NeighborsTree::addBrick(Permutation & permutation, const int length) const
{
  permutation <<= length;
  permutation |= (1 << (length-1));
}

// Given a row width, create all possible tilings of that row.
// Recurive function - makes a copy of the current permutation, adds a 2-brick to the original, adds a 3-brick to the copy, calls itself again on both.
// permutations - vector of all possible permutations for a row of width=m_width
// edge - constant with only the last bit set, corresponding to the end of the wall.
void NeighborsTree::buildRowPermutations(Permutations & permutations, const int index, const Permutation & edge) const
{
  if (((edge >> 2) & permutations[index]) != 0)                                  // base case 1 - 2 spaces left, can only add a 2-brick
    {
      addBrick(permutations[index], 2);
    }
  else if (((edge >> 3) & permutations[index]) != 0)                             // base case 2 - 3 spaces left, can only add 3-brick
    {
      addBrick(permutations[index], 3);
    }
  else
    {
      Permutation permutation = permutations[index];                             // save off current permutation

      addBrick(permutations[index], 2);                                          // add 2-brick and call self recursively
      buildRowPermutations(permutations, index, edge);

      if (((edge >> 4) & permutation) == 0)                                      // if 4 spaces are left, do not add a 3-brick
	{
	  addBrick(permutation, 3);                                              // add 3-brick to copy, save copy, call self recursively
	  permutations.push_back(permutation);

	  buildRowPermutations(permutations, permutations.size()-1, edge);
	}
    }
}

// number of permutations P of double and triple bricks in a wall of width W is the number of permutations in a wall of width W-3 plus number of permutations in a wall of width W-2:
// P(W) = P(W-3) + P(W-2)
// P(0) = P(1) = 0 (nothing fits)
// P(2) = P(2) = 1 (one brick fits)
int NeighborsTree::numRowPermutations(const int width) const
{
  int numPermutations[width+1 >= 3 ? width+1 : 3];

  numPermutations[0] = 0;
  numPermutations[1] = 0;
  numPermutations[2] = 1;
  numPermutations[3] = 1;

  for (int i=4; i<=width; i++)
    {
      numPermutations[i] = numPermutations[i-2] + numPermutations[i-3];
    }

  return numPermutations[width];
}
