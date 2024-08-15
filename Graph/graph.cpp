#include <bits/stdc++.h>
#include "graphRepresentation.h"
using namespace std;

#define MAX 100

void input(vector<int> adj[MAX], int& m, int& n) {
    cin >> m >> n;
    for (int i = 0; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        // for directed graphs, the following line should be removed
        adj[v].push_back(u);
    }
}

/*
Let graph G = <V,E>
Consider the time complexity of the following representations:
- adjacency matrix: O(V*V)
- egde list: O(V*E)
- adjacency list: O(V+E)
*/
void dfs(vector<int> adj[MAX], bool visited[MAX], int u);
void bfs(vector<int> adj[MAX], bool visited[MAX], int u);

int componentConnected(vector<int> adj[MAX], int m) {
    int count = 0;
    bool visited[MAX];
    memset(visited, false, sizeof(visited));
    for (int i = 1; i <= m; i++) {
        if (!visited[i]) {
            count++;
            dfs(adj, visited, i);
            // we can also use bfs instead of dfs
            // bfs(adj, visited, i);
        }
    }
    cout << endl;
    return count;
}


int main() {
    int a[MAX][MAX] = {0};
    vector<int> adj[MAX];
    vector<pair<int, int>> edge;
    bool visited[MAX];
    memset(visited, 0, sizeof(visited));
    int m, n;

    //transfer1(a, m, n);
    //transfer2(adj, m, n);
    //transfer3(edge, a, n);
    //transfer4(adj, a, n);
    //transfer5(a, adj, n);
    //transfer6(edge, adj, n);

    input(adj, m, n);
    //dfs(adj, visited, 1);
    //bfs(adj, visited, 1);

    cout << "The number of connected components: ";
    cout << componentConnected(adj, m) << endl;
    return 0;
}

/*
5
0 1 1 1 0
1 0 1 1 1
1 1 0 1 1
1 1 1 0 1
0 1 1 1 0

1 2
1 3
1 4
2 3
2 4
2 5
3 4
3 5
4 5

1: 2 3 4
2: 1 3 4 5
3: 1 2 4 5
4: 1 2 3 5
5: 2 3 4
*/

void dfs(vector<int> adj[MAX], bool visited[MAX], int u) {
    visited[u] = true;
    cout << u << " ";
    for (int i = 0; i < adj[u].size(); i++) {
        int v = adj[u][i];
        if (!visited[v]) {
            dfs(adj, visited, v);
        }
    }
    /*
    Another way:
    for (int v : adj[u]) {
        if (!visited[v]) {
            dfs(adj, visited, v);
        }
    }
    */
}

void bfs(vector<int> adj[MAX], bool visited[MAX], int u) {
    queue<int> q;
    q.push(u);
    visited[u] = true;

    while(!q.empty()) {
        int v = q.front();
        q.pop();
        cout << v << " ";
        for (int i = 0; i < adj[v].size(); i++) {
            int w = adj[v][i];
            if (!visited[w]) {
                q.push(w);
                visited[w] = true;
            }
        }
    }
}