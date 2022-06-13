#include <iostream>
#include <vector>
#include <functional>
#include <queue>

#include "IGraph.h"

#include "ListGraph.h"
#include "MatrixGraph.h"
#include "SetGraph.h"
#include "ArcGraph.h"

void BFS(const IGraph &graph, int vertex, std::vector<bool> &visited, const std::function<void(int)> &func)
{
  std::queue<int> qu;
  qu.push(vertex);
  visited[vertex] = true;

  while (!qu.empty())
  {
    int currentVertex = qu.front();
    qu.pop();

    func(currentVertex);

    for (int nextVertex: graph.GetNextVertices(currentVertex))
    {
      if (!visited[nextVertex])
      {
        visited[nextVertex] = true;
        qu.push(nextVertex);
      }
    }
  }
}

void mainBFS(const IGraph &graph, const std::function<void(int)> &func)
{
  std::vector<bool> visited(graph.VerticesCount(), false);

  for (int i = 0; i < graph.VerticesCount(); i++)
  {
    if (!visited[i])
      BFS(graph, i, visited, func);
  }
}

void DFS(const IGraph &graph, int vertex, std::vector<bool> &visited, const std::function<void(int)> &func)
{
  visited[vertex] = true;
  func(vertex);

  for (int nextVertex: graph.GetNextVertices(vertex))
  {
    if (!visited[nextVertex])
      DFS(graph, nextVertex, visited, func);
  }
}

void mainDFS(const IGraph &graph, const std::function<void(int)> &func)
{
  std::vector<bool> visited(graph.VerticesCount(), false);

  for (int i = 0; i < graph.VerticesCount(); i++)
  {
    if (!visited[i])
      DFS(graph, i, visited, func);
  }
}

int main() {

  ListGraph graph(7);
  graph.AddEdge(0, 1);
  graph.AddEdge(0, 5);
  graph.AddEdge(1, 2);
  graph.AddEdge(1, 3);
  graph.AddEdge(1, 5);
  graph.AddEdge(1, 6);
  graph.AddEdge(3, 2);
  graph.AddEdge(3, 4);
  graph.AddEdge(3, 6);
  graph.AddEdge(5, 4);
  graph.AddEdge(5, 6);
  graph.AddEdge(6, 4);

  std::cout << "List graph" << std::endl;
  mainBFS(graph, [](int vertex){ std::cout << vertex << " "; });
  std::cout << std::endl;
  mainDFS(graph, [](int vertex){ std::cout << vertex << " "; });
  std::cout << std::endl;

  SetGraph graph2(graph);
  std::cout << "set graph" << std::endl;
  mainBFS(graph2, [](int vertex){ std::cout << vertex << " "; });
  std::cout << std::endl;
  mainDFS(graph2, [](int vertex){ std::cout << vertex << " "; });
  std::cout << std::endl;

  MatrixGraph graph3(graph2);
  std::cout << "matrix graph" << std::endl;
  mainBFS(graph3, [](int vertex){ std::cout << vertex << " "; });
  std::cout << std::endl;
  mainDFS(graph3, [](int vertex){ std::cout << vertex << " "; });
  std::cout << std::endl;

  ArcGraph graph4(graph3);
  std::cout << "arc graph" << std::endl;
  mainBFS(graph4, [](int vertex){ std::cout << vertex << " "; });
  std::cout << std::endl;
  mainDFS(graph4, [](int vertex){ std::cout << vertex << " "; });
  std::cout << std::endl;

  ListGraph graph5(graph4);
  std::cout << "list graph" << std::endl;
  mainBFS(graph5, [](int vertex){ std::cout << vertex << " "; });
  std::cout << std::endl;
  mainDFS(graph5, [](int vertex){ std::cout << vertex << " "; });
  std::cout << std::endl;

  return 0;
}
