#include "MatrixGraph.h"

void MatrixGraph::AddEdge(int from, int to) {
  assert(0 <= from && from < matrix_.size());
  assert(0 <= to && to < matrix_.size());
  matrix_[from][to] = 1;
}

int MatrixGraph::VerticesCount() const {
  return matrix_.size();
}

std::vector<int> MatrixGraph::GetNextVertices(int vertex) const {
  std::vector<int> result;
  assert(0 <= vertex && vertex < matrix_.size());

  for (size_t i = 0; i < matrix_.size(); ++i) {
    if (matrix_[vertex][i] != 0)
      result.push_back(i);
  }
  return result;
}
std::vector<int> MatrixGraph::GetPrevVertices(int vertex) const {
  std::vector<int> result;
  assert(0 <= vertex && vertex < matrix_.size());

  for (size_t i = 0; i < matrix_.size(); ++i) {
    if (matrix_[i][vertex] != 0)
      result.push_back(i);
  }
  return result;
}

MatrixGraph::MatrixGraph(int count)
: matrix_(count)
{
  for (size_t i = 0; i < matrix_.size(); ++i) {
    matrix_[i] = std::vector<bool>(matrix_.size());
  }

  for (int i = 0; i < matrix_.size(); ++i) {
    for (int j = 0; j < matrix_.size(); ++j) {
      matrix_[i][j] = 0;
    }
  }
}

MatrixGraph::MatrixGraph(const IGraph &graph)
: matrix_(graph.VerticesCount())
{
  for (size_t i = 0; i < matrix_.size(); ++i) {
    matrix_[i] = std::vector<bool>(matrix_.size());
  }

  for (size_t i = 0; i < matrix_.size(); ++i) {
    std::vector<int> temp = graph.GetNextVertices(i);
    for (size_t j = 0; j < temp.size(); ++j) {
      matrix_[i][temp[j]] = 1;
    }
  }
}
