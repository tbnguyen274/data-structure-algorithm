#include <iostream>
#include <string>
using namespace std;

struct vertex {
    string color; // white, gray, black
    int distance; // distance
    vertex* pi; // v’s predecessor in the breadth-ûrst tree
};

// BFS in graph
// Time complexity: O(V+E)
void BFS(int a[][6], vertex* vertices, int n, int s) {
    for (int i = 0; i < n; i++) {
        if (i != s) {
            vertices[i].color = "white";
            vertices[i].distance = 0;
            vertices[i].pi = NULL;
        }
    }
    vertices[s].color = "gray";
    vertices[s].distance = 0;
    vertices[s].pi = NULL;
    int q[n];
    int front = 0;
    int rear = 0;
    q[rear] = s;
    rear++;
    while (front != rear) {
        int u = q[front];
        front++;
        for (int v = 0; v < n; v++) {
            if (a[u][v] == 1) {
                if (vertices[v].color == "white") {
                    vertices[v].color = "gray";
                    vertices[v].distance = vertices[u].distance + 1;
                    vertices[v].pi = &vertices[u];
                    q[rear] = v;
                    rear++;
                }
            }
        }
        vertices[u].color = "black";
    }
}