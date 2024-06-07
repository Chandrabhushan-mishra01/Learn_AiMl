#include <iostream>
#include <queue>
#include <vector>

using namespace std;

void bfs(vector<vector<int> >& adjList, int startNode,
         vector<bool>& visited)
{
    
    queue<int> q;

    visited[startNode] = true;
    q.push(startNode);

 
    while (!q.empty()) {
 
        int currentNode = q.front();
        q.pop();
        cout << currentNode << " ";

        for (int neighbor : adjList[currentNode]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
}

void addEdge(vector<vector<int> >& adjList, int u, int v)
{
    adjList[u].push_back(v);
}

int main()
{
    int vertices, edges;
    cout << "Enter the number of vertices in the graph: ";
    cin >> vertices;

 
    vector<vector<int> > adjList(vertices);

    cout << "Enter the number of edges: ";
    cin >> edges;

    cout << "Enter the edges (format: source destination):" << endl;
    for (int i = 0; i < edges; ++i) {
        int src, dest;
        cin >> src >> dest;
        addEdge(adjList, src, dest);
    }

    vector<bool> visited(vertices, false);

    int startVertex;
    cout << "Enter the starting vertex for BFS: ";
    cin >> startVertex;

    cout << "Breadth First Traversal starting from vertex "
            << startVertex << ": ";
    bfs(adjList, startVertex, visited);

    return 0;
}
