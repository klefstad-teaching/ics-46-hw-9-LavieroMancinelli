#include "dijkstras.h"

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int n = G.numVertices;
    vector<int> dist(n, INF); // distance to each node from source
    vector<bool> visited(n, false);
    previous.resize(n, -1);
    // [](const pair<int, int>& a, const pair<int, int>& b) {return a.first > b.first;}
    priority_queue<pair<int,int>, vector<pair<int, int>>, greater<>> pq; // distance, index because pq ordered by first
    pq.push({0, source});
    dist[source] = 0;

    while (!pq.empty()) {
        pair<int, int> cur = pq.top();
        pq.pop();
        int v = cur.second;
        if (visited[v]) continue;
        else visited[v] = true;
        for (const Edge& e : G[v]) {
            int other = e.dst;
            if (!visited[other]) {
                int weight = e.weight;
                int newD = dist[v] + weight;
                if (newD < dist[other]) {
                    dist[other] = newD;
                    previous[other] = v;
                    pq.push({newD, other});
                }
            }
        }
    }
    return dist;
    
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> path;
    if (distances[destination] == INF) return path; 
    for (int it = destination; it != -1; it = previous[it]) {
        path.push_back(it);
    }

    reverse(path.begin(), path.end());
    return path;
}


void print_path(const vector<int>& v, int total) {
    int len = v.size();
    for (int i = 0; i < len; ++i)
        cout << v[i] << " ";
    cout << "\nTotal cost is " << total << endl;
}