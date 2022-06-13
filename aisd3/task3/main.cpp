#include <iostream>
#include <set>
#include <vector>
#include <cassert>

struct ListGraph
{
 public:
  ListGraph(int size)
      : adjacencyLists(size)
  {
  }
  ~ListGraph() {}

  void AddEdge(int from, int to, int weight)
  {
    assert(0 <= from && from < adjacencyLists.size());
    assert(0 <= to && to < adjacencyLists.size());
    adjacencyLists[from].push_back(std::make_pair(to, weight));
    adjacencyLists[to].push_back(std::make_pair(from, weight));

  }

  int VerticesCount() const
  {
    return (int)adjacencyLists.size();
  }

  std::vector<std::pair<int,int>> GetNextVertices(int vertex) const
  {
    assert(0 <= vertex && vertex < adjacencyLists.size());
    return adjacencyLists[vertex];
  }

  std::vector<std::pair<int,int>> GetPrevVertices(int vertex) const
  {
    assert(0 <= vertex && vertex < adjacencyLists.size());
    std::vector<std::pair<int,int>> prevVertices;

    for (int from = 0; from < adjacencyLists.size(); from++)
    {
      for (auto to: adjacencyLists[from])
      {
        if (to.first == vertex)
          prevVertices.push_back(std::make_pair(from, to.second));
      }
    }
    return prevVertices;
  }

 private:
  std::vector<std::vector<std::pair<int,int>>> adjacencyLists;
};

class Cmp {
 public:
  bool operator()(const std::pair<int,int> &p1, const std::pair<int,int> &p2) const {
    if (p1.first == p2.first) {
      return p1.second < p2.second;
    }
    else {
      return p1.first < p2.first;
    }
  }
};

template <class Cmp>
int shortest_paths(const ListGraph &graph, int vertex, int end)
{
  Cmp cmp;
  std::set<std::pair<int,int>, decltype(cmp)> qu;
  std::vector<int> r(graph.VerticesCount(), 1e7);

  r[vertex] = 0;
  qu.insert(std::make_pair(r[vertex], vertex));

  while (!qu.empty())
  {
    int currentVertex = qu.begin()->second;
    qu.erase(qu.begin());

    for (const auto nextVertex: graph.GetNextVertices(currentVertex))
    {
      if (r[nextVertex.first] > r[currentVertex] + nextVertex.second) {
        r[nextVertex.first] = r[currentVertex] + nextVertex.second;
        qu.insert(std::make_pair(r[nextVertex.first], nextVertex.first));
      }
    }
  }
  return r[end];
}

int main() {
  int N, M, begin, end;
  std::cin >> N >> M;
  ListGraph graph(N);
  for (int i = 0; i < M; ++i) {
    int to, from, weight;
    std::cin >> to >> from >> weight;
    graph.AddEdge(to, from, weight);
  }
  std::cin >> begin >> end;
  Cmp cmp;
  std::cout << shortest_paths<Cmp>(graph, begin, end);
  return 0;
}
