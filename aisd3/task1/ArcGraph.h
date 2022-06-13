#ifndef AISD3_TASK1_ARCGRAPH_H_
#define AISD3_TASK1_ARCGRAPH_H_
#include "IGraph.h"

class ArcGraph: public IGraph {
 public:
  ~ArcGraph() {}
  ArcGraph(int count);
  ArcGraph(const IGraph &graph);

  void AddEdge(int from, int to) override;
  int VerticesCount() const override;

  std::vector<int> GetNextVertices(int vertex) const override;
  std::vector<int> GetPrevVertices(int vertex) const override;
 private:
  int count;
  std::vector<std::pair<int, int>> vector_;
};

#endif //AISD3_TASK1_ARCGRAPH_H_
