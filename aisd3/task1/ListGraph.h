#ifndef AISD3_TASK1_LISTGRAPH_H_
#define AISD3_TASK1_LISTGRAPH_H_
#include "IGraph.h"

struct ListGraph: public IGraph
{
 public:

  ListGraph(int size);

  ListGraph(const IGraph &graph);

  ~ListGraph() {}

  void AddEdge(int from, int to) override;

  int VerticesCount() const override;

  std::vector<int> GetNextVertices(int vertex) const override;

  std::vector<int> GetPrevVertices(int vertex) const override;

 private:

  std::vector<std::vector<int>> adjacencyLists;

};

#endif //AISD3_TASK1_LISTGRAPH_H_
