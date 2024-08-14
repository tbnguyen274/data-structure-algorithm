#include <bits/stdc++.h>
using namespace std;

#define MAX 100

// from edge list to adjacent matrix
void transfer1(int a[][MAX], int& m, int& n) {
    cin >> m >> n;
    for (int i = 0; i < n; i++) {
        int u, v;
        cin >> u >> v;
        a[u][v] = 1;
        a[v][u] = 1;
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= m; j++) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
}

// from edge list to adjacent list
void transfer2(vector<int> adj[MAX], int& m, int& n) {
    cin >> m >> n;
    for (int i = 0; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for (int i = 1; i <= m; i++) {
        cout << i << ": ";
        for (int j = 0; j < adj[i].size(); j++) {
            cout << adj[i][j] << " ";
        }
        cout << endl;
    }
}

// from adjacent matrix to edge list
void transfer3(vector<pair<int, int>> edge, int adj[][MAX], int& n) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> adj[i][j];
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (adj[i][j] == 1 && i < j) {
                edge.push_back(make_pair(i, j));
            }
        }
    }
    for (auto it : edge) {
        cout << it.first << " " << it.second << endl;
    }
}

// from adjacent matrix to adjacent list
void transfer4(vector<int> adj[MAX], int a[][MAX], int& n) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> a[i][j];
            if (a[i][j] == 1) {
                adj[i].push_back(j);
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << i << ": ";
        for (int j = 0; j < adj[i].size(); j++) {
            cout << adj[i][j] << " ";
        }
        cout << endl;
    }
}

// from adjacent list to adjacent matrix
void transfer5(int a[][MAX], vector<int> adj[MAX], int& n) {
    cin >> n;
    cin.ignore();
    for (int i = 1; i <= n; i++) {
        string s;
        getline(cin, s);
        stringstream ss(s);
        int x;
        while (ss >> x) {
            a[i][x] = 1;
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
}

// from adjecent list to edge list
void transfer6(vector<pair<int, int>> edge, vector<int> adj[MAX], int& n) {
    cin >> n;
    cin.ignore();
    for (int i = 1; i <= n; i++) {
        string s;
        getline(cin, s);
        stringstream ss(s);
        int x;
        while (ss >> x) {
            adj[i].push_back(x);
            if (x > i) {
                edge.push_back(make_pair(i, x));
            }
        }
    }
    for (auto it : edge) {
        cout << it.first << " " << it.second << endl;
    }
}



