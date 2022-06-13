#ifndef AISD3_TASK1_IGRAPH_H_
#define AISD3_TASK1_IGRAPH_H_
#include <iostream>
#include <vector>
#include <cassert>

struct IGraph {
  virtual ~IGraph() {}

  virtual void AddEdge(int from, int to) = 0;
  virtual int VerticesCount() const  = 0;

  virtual std::vector<int> GetNextVertices(int vertex) const = 0;
  virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};

#endif //AISD3_TASK1_IGRAPH_H_
