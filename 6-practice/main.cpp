#include <iostream>
#include <vector>
#include <Windows.h>
#include <map>
#include <set>

using namespace std;

map<char, int> dijkstra(map<char, vector<pair<char, int>>> &graph, const char &start) {
    map<char, int> dist;
    for (const auto &[from, to]: graph)
        dist[from] = INT_MAX;
    dist[start] = 0;
    set<pair<int, char>> q;
    q.insert({dist[start], start});

    while (!q.empty()) {
        char nearest = q.begin()->second;
        q.erase(q.begin());

        for (auto &[to, weight]: graph[nearest]) {
            if (dist[to] > dist[nearest] + weight) {
                q.erase({dist[to], to});
                dist[to] = dist[nearest] + weight;
                q.insert({dist[to], to});
            }
        }
    }

    return dist;
}


int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    cout << "Input number of edges and vertices:\n";
    int edgesCount, verticesCount;
    cin >> edgesCount >> verticesCount;
    map<char, vector<pair<char, int>>> graph;
    cout << "Input " << edgesCount << " edges in the following format: \"from to weight\":\n";
    for (int i = 0; i < edgesCount; ++i) {
        char a, b;
        int weight;
        cin >> a >> b >> weight;
        graph[a].emplace_back(b, weight);
        graph[b].emplace_back(a, weight);
    }
    char start;
    cout << "Input start vertex";
    cin >> start;
    auto dist = dijkstra(graph, start);

    for (const auto &[to, d]: dist) {
        if (d == INT_MAX) {
            cout << "No path from" << start << " to " << to << "\n";
        } else {
            cout << "Distance from" << start << " to " << to << ": " << d << "\n";
        }
    }
}