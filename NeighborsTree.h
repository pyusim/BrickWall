#pragma once

#include <vector>
#include <bitset>

#include "constants.h"

class NeighborsTree
{
  typedef std::vector< std::vector<long> > Neighbors;
  typedef std::bitset<MAX_ROW_WIDTH> Permutation;                         // using a long is faster, but it also limited to sizeof(long) (most commonly 64-bits as of 2014) and platform-dependent
                                                                          // bitsets are platform-independent
  typedef std::vector<Permutation> Permutations;

  Neighbors m_neighbors;

  void addBrick(Permutation & permutation, const int length) const;
  void buildRowPermutations(Permutations & permutations, const int index, const Permutation & edge) const;
  int numRowPermutations(const int width) const;
  void build(const int width);

 public:

  NeighborsTree(const int width);

  int getNumNeighbors(const int permutation) const
  {
    return m_neighbors[permutation].size();
  }
  
  int get(const int permutation, const int row) const
  {
    return m_neighbors[permutation][row];
  }
  
  int getNumPermutations() const 
  { 
    return m_neighbors.size(); 
  }
};
