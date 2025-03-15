#include "dijkstras.h"

int main() {
    string filename = "./src/large.txt";
    Graph g;
    file_to_graph(filename, g);
    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(g, 0, previous);
    int destination = g.numVertices -1;
    vector<int> path = extract_shortest_path(distances, previous, destination);
    print_path(path, distances[destination]);
    return 0;
}