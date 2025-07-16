#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <limits>
#include <algorithm>
using namespace std;

class Graph {
private:
    unordered_map<int, vector<pair<int, int>>> adjList;

public:
    void addEdge(int u, int v, int weight) {
        adjList[u].push_back({v, weight});
        adjList[v].push_back({u, weight});
    }

    vector<int> shortestPath(int src, int dest) {
        unordered_map<int, int> dist;
        unordered_map<int, int> parent;
        for (auto& it : adjList) {
            dist[it.first] = numeric_limits<int>::max();
        }
        dist[src] = 0;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, src});

        while (!pq.empty()) {
            int node = pq.top().second;
            int nodeDist = pq.top().first;
            pq.pop();

            if (node == dest) break;

            for (auto& neighbor : adjList[node]) {
                int nextNode = neighbor.first;
                int edgeWeight = neighbor.second;

                if (nodeDist + edgeWeight < dist[nextNode]) {
                    dist[nextNode] = nodeDist + edgeWeight;
                    parent[nextNode] = node;
                    pq.push({dist[nextNode], nextNode});
                }
            }
        }

        vector<int> path;
        if (dist[dest] == numeric_limits<int>::max()) return path;

        for (int at = dest; at != src; at = parent[at]) {
            path.push_back(at);
        }
        path.push_back(src);
        reverse(path.begin(), path.end());
        return path;
    }
};

#endif
