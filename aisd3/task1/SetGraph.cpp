#include "SetGraph.h"

void SetGraph::AddEdge(int from, int to) {
  assert(0 <= from && from < vector_.size());
  assert(0 <= to && to < vector_.size());
  vector_[from].insert(to);
}

int SetGraph::VerticesCount() const {
  return vector_.size();
}

std::vector<int> SetGraph::GetNextVertices(int vertex) const {
  assert(0 <= vertex && vertex < vector_.size());
  std::vector<int> result;
  for (const auto i: vector_[vertex]){
    result.push_back(i);
  }
  return result;
}
std::vector<int> SetGraph::GetPrevVertices(int vertex) const {
  assert(0 <= vertex && vertex < vector_.size());
  std::vector<int> result;
  for (size_t i = 0; i < vector_.size(); ++i) {
    if (vector_[i].find(vertex) != vector_[i].end()) {
      result.push_back(*vector_[i].find(vertex));
    }
  }
  return result;
}

SetGraph::SetGraph(int count)
: vector_(count)
{
}

SetGraph::SetGraph(const IGraph &graph)
: vector_(graph.VerticesCount())
{
  for (size_t i = 0; i < vector_.size(); ++i) {
    for (const auto j: graph.GetNextVertices(i)) {
      vector_[i].insert(j);
    }
  }
}
