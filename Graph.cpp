#include <bits/stdc++.h>

using namespace std;

class Graph
{
     vector<vector<int>> graph;

public:
     Graph(vector<vector<int>> graph)
     {
          this->graph = graph;
     }
     void dfs(int nodes, int s)
     {
          vector<bool> visited(nodes, false);
          stack<int> live;
          live.push(s);
          while (!live.empty())
          {
               int n = live.top();
               live.pop();
               if (!visited[n])
               {
                    visited[n] = true;
                    for (int i = 0; i < nodes; i++)
                    {
                         if (!visited[i] && this->graph[n][i] == 1)
                         {
                              live.push(i);
                         }
                    }
                    cout << n << " ";
               }
          }
     }
     void bfs(int nodes, int s)
     {
          vector<bool> visited(nodes, false);
          queue<int> live;
          live.push(s);
          while (!live.empty())
          {
               int n = live.front();
               live.pop();
               if (!visited[n])
               {
                    visited[n] = true;
                    for (int i = 0; i < nodes; i++)
                    {
                         if (!visited[i] && this->graph[n][i] == 1)
                         {
                              live.push(i);
                         }
                    }
                    cout << n << " ";
               }
          }
     }
};

int main()
{
     vector<vector<int>> graph{
         {0, 1, 1, 1, 0, 0, 0, 0},
         {1, 0, 0, 1, 1, 0, 0, 0},
         {1, 0, 0, 1, 1, 1, 0, 0},
         {1, 1, 1, 0, 0, 0, 1, 0},
         {0, 1, 1, 0, 0, 1, 1, 1},
         {0, 0, 1, 0, 1, 0, 1, 0},
         {0, 0, 0, 1, 1, 1, 0, 0},
         {0, 0, 0, 0, 1, 0, 0, 0}};
     Graph g(graph);
     g.dfs(graph.size(), 0);
     // g.bfs(graph.size(),0);
}    