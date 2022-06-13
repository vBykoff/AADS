#include "ArcGraph.h"

void ArcGraph::AddEdge(int from, int to) {
  assert(0 <= from && from < count);
  assert(0 <= to && to < count);
  vector_.push_back(std::make_pair(from, to));
}

int ArcGraph::VerticesCount() const {
  return count;
}

std::vector<int> ArcGraph::GetNextVertices(int vertex) const {
  assert(0 <= vertex && vertex < count);
  std::vector<int> result;
  for (const auto &i: vector_) {
    if (i.first == vertex)
      result.push_back(i.second);
  }
  return result;
}

std::vector<int> ArcGraph::GetPrevVertices(int vertex) const {
  assert(0 <= vertex && vertex < count);
  std::vector<int> result;
  for (const auto &i: vector_) {
    if (i.second == vertex)
      result.push_back(i.first);
  }
  return result;
}

ArcGraph::ArcGraph(int count)
: count(count)
{
}

ArcGraph::ArcGraph(const IGraph &graph)
: count(graph.VerticesCount())
{
  for (int i = 0; i < count; ++i) {
    for (const auto j: graph.GetNextVertices(i)) {
      vector_.push_back(std::make_pair(i, j));
    }
  }
}
