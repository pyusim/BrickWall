#pragma once

#include <vector>

#include "NeighborsTree.h"

// The class BrickWallSolutions encapsulates an algorithm that figures out all the tilings of a wall by bricks of two and three units with a running crack.
// The algorithm used to find the number of legal tilings involves finding all the tilings of a row, building a tree of possible legal neighbors for each tiling, then traversing the tree
// to the right depth (height of wall).  Doing this operatin is still very expensive, so a cache is maintained to avoid re-traversing subtrees (dynamic programming)
class BrickWallSolutions
{
  int m_width;
  int m_rows;

  typedef std::vector< std::vector<unsigned long> > Cache;

  NeighborsTree m_neighborsTree;

  unsigned long calculateSolutions(const int row, const int permutationIndex, Cache & cache) const;

 public:

  BrickWallSolutions(const int width, const int rows);

  unsigned long getNumPossibleSolutions();
};
