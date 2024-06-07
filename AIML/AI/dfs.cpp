#include <iostream>
#include <list>
#include <map>
using namespace std;
class Graph {
public:
    map<int, bool> visited;
    map<int, list<int>> adj;
    void addEdge(int v, int w);
    void DFS(int v);
};
void Graph::addEdge(int v, int w) {
    adj[v].push_back(w);
}

void Graph::DFS(int v) {
    visited[v] = true;
    cout << v << " ";
    for (auto i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
            DFS(*i);
}


int main() {
    int vertices, edges;
    cout << "Enter the number of vertices in the graph: ";
    cin >> vertices;

    Graph g;

    cout << "Enter the number of edges: ";
    cin >> edges;

    cout << "Enter the edges (format: source destination):" << endl;
    for (int i = 0; i < edges; ++i) {
        int src, dest;
        cin >> src >> dest;
        g.addEdge(src, dest);
    }

    int startVertex;
    cout << "Enter the starting vertex for DFS: ";
    cin >> startVertex;

    cout << "Following is Depth First Traversal (starting from vertex "
         << startVertex << "):\n";

    g.DFS(startVertex);

    return 0;
}
