#ifndef AISD3_TASK1_MATRIXGRAPH_H_
#define AISD3_TASK1_MATRIXGRAPH_H_
#include "IGraph.h"

class MatrixGraph: public IGraph {
 public:
  MatrixGraph(int count);
  MatrixGraph(const IGraph &graph);

  ~MatrixGraph() {
      }

  void AddEdge(int from, int to) override;
  int VerticesCount() const override;

  std::vector<int> GetNextVertices(int vertex) const override;
  std::vector<int> GetPrevVertices(int vertex) const override;

 private:
  std::vector<std::vector<bool>> matrix_;
};

#endif //AISD3_TASK1_MATRIXGRAPH_H_
