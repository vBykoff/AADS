#include <iostream>
#include <unordered_set>
#include <vector>
#include <cassert>
#include <queue>
#include <functional>

//Дан невзвешенный неориентированный граф.
//В графе может быть несколько кратчайших путей между какими-то вершинами.
//Найдите количество различных кратчайших путей между заданными вершинами.
//Требования: сложность O(V+E).
//Формат ввода.
//v: кол-во вершин (макс. 50000),
//n: кол-во ребер (макс. 200000),
//n пар реберных вершин,
//    пара вершин u, w для запроса.
//Формат вывода.
//Количество кратчайших путей от u к w.

struct IGraph {
  virtual ~IGraph() {}

  virtual void AddEdge(int from, int to) = 0;
  virtual int VerticesCount() const  = 0;

  virtual std::vector<int> GetNextVertices(int vertex) const = 0;
  virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};

struct ListGraph: public IGraph
{
 public:
  ListGraph(int size)
      : adjacencyLists(size)
  {
  }

  ListGraph(const IGraph &graph)
      : adjacencyLists(graph.VerticesCount())
  {
    for (int i = 0; i < graph.VerticesCount(); i++)
      adjacencyLists[i] = graph.GetNextVertices(i);
  }

  ~ListGraph() {}

  void AddEdge(int from, int to) override
  {
    assert(0 <= from && from < adjacencyLists.size());
    assert(0 <= to && to < adjacencyLists.size());
    adjacencyLists[from].push_back(to);
    adjacencyLists[to].push_back(from);

  }

  int VerticesCount() const override
  {
    return (int)adjacencyLists.size();
  }

  std::vector<int> GetNextVertices(int vertex) const override
  {
    assert(0 <= vertex && vertex < adjacencyLists.size());
    return adjacencyLists[vertex];
  }

  std::vector<int> GetPrevVertices(int vertex) const override
  {
    assert(0 <= vertex && vertex < adjacencyLists.size());
    std::vector<int> prevVertices;

    for (int from = 0; from < adjacencyLists.size(); from++)
    {
      for (int to: adjacencyLists[from])
      {
        if (to == vertex)
          prevVertices.push_back(from);
      }
    }
    return prevVertices;
  }

 private:
  std::vector<std::vector<int>> adjacencyLists;
};

std::vector<int> shortest_paths(const ListGraph &graph, int vertex)
{
  std::queue<int> qu;
  std::vector<int> r(graph.VerticesCount(), graph.VerticesCount());
  std::vector<int> k(graph.VerticesCount(), 0);

  qu.push(vertex);
  r[vertex] = 0;
  k[vertex] = 1;

  while (!qu.empty())
  {
    int currentVertex = qu.front();
    qu.pop();

    for (int nextVertex: graph.GetNextVertices(currentVertex))
    {
      if (r[nextVertex] > r[currentVertex] + 1) {
        r[nextVertex] = r[currentVertex] + 1;

        qu.push(nextVertex);
      }
      if (r[nextVertex] == r[currentVertex] + 1) {
        k[nextVertex] += k[currentVertex];
      }
    }
  }
  return k;
}

int main() {
  int v, n;
  std::cin >> v >> n;
  ListGraph graph(v);
  for (int i = 0; i < n; ++i) {
    int from, to;
    std::cin >> from >> to;
    graph.AddEdge(from, to);
  }
  int u,w;
  std::cin >> u >> w;
  std::cout << shortest_paths(graph, u)[w] << std::endl;

  return 0;
}