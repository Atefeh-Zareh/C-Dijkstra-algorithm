//
// Created by 39351 on 6/25/2022.
//

#ifndef GRAPH_GRAPH_SP_HPP
#define GRAPH_GRAPH_SP_HPP


#include <exception>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <list>
#include <memory>



//--------------------------------------------------------------------------

// Searches an element in the container, if it exists, it is removed
// Exception : wrong node identifier
class NodeNotFound {
    const int id;
public:
    NodeNotFound(int node_id) : id(node_id) {}

    std::string msg() const {
        std::string m = "Node " + std::to_string(id) + " not found";
        return m;
    }
};

// Exception : wrong node identifier
class EdgeNotFound {
    const int id;
public:
    EdgeNotFound(int edge_id) : id(edge_id) {}

    std::string msg() const {
        std::string m = "Edge " + std::to_string(id) + " not found";
        return m;
    }
};

template <typename ...Tp>
class EdgeData : public Tp ... {
    std::string str;


public:
    void set_string(const std::string &s) { str = s; }
    std::string get_string() const { return str; }
};

class RouteLength {
    double l;
    int averageTime;
public:
    void set_length(double len) { l = len; }
    double get_length(double len) const { return l; }

    int getAverageTime() const {
        return averageTime;
    }

    void setAverageTime(int averageTime) {
        RouteLength::averageTime = averageTime;
    }
};




// ND=nodes, ED=edges
template <typename N, typename E>
class Graph {
    struct Node {
        int node_id;
        std::shared_ptr<N> data;
        Node(int id, N data) {
            this->node_id = id;
            this->data = data;
        }
    };
    struct Edge {
        int edge_id;
        int source_id;
        int dest_id;

        std::shared_ptr<E> data;

        Edge(int edge_id, E data, int source_id, int dest_id) {
            this->edge_id = edge_id;
            this->data = data;
            this->source_id = source_id;
            this->dest_id = dest_id;
        }
    };



    /* data structures */
    std::map<int, Node> nodes;
    std::map<int, Edge> edges;
    std::map<std::pair< int,int>, Edge> edges_detailed;
private:
    std::map<int, std::vector<int> > dests;//map of node to edge
    int node_counter;//the same id_counter in initial project template
    int edge_counter;

public:
    Graph() : node_counter(0), edge_counter(0) {}
    Graph(const Graph &other) :
            nodes(other.nodes), edges(other.edges), dests(other.dests),
            node_counter(other.node_counter), edge_counter(other.edge_counter) {}

    inline int add_edge(const E m, int source_id, int dest_id) {
        Edge edge(edge_counter, m, source_id, dest_id);
        edges.insert(std::make_pair(edge_counter, edge));
        if (dests_exists(source_id)) {
            auto iterator = dests.find(source_id);
            if (iterator != dests.end()) {
                iterator->second.push_back(dest_id);
            }
        } else {
            std::vector<int> destinationsForSource;
            destinationsForSource.push_back(dest_id);
            dests.insert(std::make_pair(source_id, destinationsForSource));
        }
        return edge_counter++;
    }


    inline bool edge_exists(int id) const {
        auto iterator = edges.find(id);
        bool doesExist = iterator != edges.end();
        return doesExist;
    }

    inline bool dests_exists(int id) const {
        auto iterator = dests.find(id);
        bool doesExist = iterator != dests.end();
        return doesExist;
    }

    inline void remove_edge(int edge_id) {
        if (edge_exists(edge_id)) {
            edges.erase(edge_id);
            edge_counter--;
        }
    }

    inline void remove_node(int node_id) {
        if (node_exist(node_id)) {
            //delete from edges
            for (std::pair<int, Edge> e: edges) {
                Edge edge = e.second;
                if (edge.source_id == node_id || edge.dest_id == node_id) {
                    remove_edge(edge.edge_id);
                }
            }
            //delete from dests:
            bool doesExist = dests_exists(node_id);
            if (doesExist) {
                dests.erase(node_id);
            }
            nodes.erase(node_id);
            node_counter--;
        }
    }

    inline int search_node(const std::string &m) const {
        for (std::pair<int, Node> p: nodes) {
            if (p.second.data == m) {
                return p.second.node_id;
            }
        }
    }

    inline std::string get_node_data(int node_id) const {
        auto iterator = nodes.find(node_id);
        if (iterator != nodes.end()) {
            return iterator->second.data;
        }
    }

    inline Edge get_edge_obj(int src, int dest) const {
        auto iterator = edges_detailed.find(std::pair(src, dest));
        if (iterator != edges_detailed.end()) {
            return iterator->second;
        } else{
            std::cout<<"ERROR"<<std::endl;
        }
    }

    inline std::string get_edge_data(int edge_id) const {
        auto iterator = edges.find(edge_id);
        if (iterator != edges.end()) {
            return iterator->second.data;
        }
    }

    inline int get_edge_source(int edge_id) const {
        auto iterator = edges.find(edge_id);
        if (iterator != edges.end()) {
            return iterator->second.source_id;
        }
    }

    inline int get_edge_dest(int edge_id) const {
        auto iterator = edges.find(edge_id);
        if (iterator != edges.end()) {
            return iterator->second.dest_id;
        }
    }

    inline Edge get_edge(int edge_id) const {
        auto iterator = edges.find(edge_id);
        if (iterator != edges.end()) {
            return iterator->second;
        }
    }

    std::vector<int> get_successors(int node_id) const {
        auto iterator = dests.find(node_id);

        if (iterator != (dests.end())) {
            return iterator->second;
        } else {
            /**
             * NOTE: If we don't have else part, a really big non sense vector is returned
             */
            std::cout << "no successor!";
            std::vector<int> v;
            return v;
        }
    }

    std::vector<int> get_predecessors(int node_id) const {
        std::vector<int> res;
        for (auto pair: dests) {
            for (auto outgoing_edge: pair.second) {
                if (outgoing_edge == node_id) {
                    res.push_back(pair.first);
                }
            }
        }
        return res;
    }

    using Path = std::vector<int>;

    //------------------------------------------------------------------------------------

    // Prints all paths from 's' to 'd'
    std::vector<Path> all_paths(int s, int d) {

        std::cout << "printing all paths" << std::endl;
        // Mark all the nodes as not visited
        bool *visited = new bool[node_counter];

        // Create an array to store path
        int *path = new int[node_counter];
        int path_index = 0; // Initialize path[] as empty

        // Initialize all nodes as not visited
        for (int i = 0; i < node_counter; i++)
            visited[i] = false;

        // Call the recursive helper function to print all paths
        std::vector<Path> allPaths;
        getAllPathsUtil(s, d, visited, path, path_index, allPaths);
        return allPaths;
    }

    void getAllPathsUtil(int u, int d, bool visited[], int path[], int &path_index, std::vector<Path> &allPaths) {

        // Mark the current node and store it in path[]
        visited[u] = true;
        path[path_index] = u;
        path_index++;

        // If current vertex is same as destination, then print
        // current path[]
        if (u == d) {
            Path p;
            for (int i = 0; i < path_index; i++) {
                p.push_back(i);
                //std::cout << path[i] << " ";
            }
            //std::cout << std::endl;
            allPaths.push_back(p);
        } else // If current vertex is not destination
        {
            // Recur for all the vertices adjacent to current vertex
            auto x = dests.find(u);
            for (auto k: x->second) {
                if (!visited[k]) {
                    getAllPathsUtil(k, d, visited, path, path_index, allPaths);
                }
            }
        }
        // Remove current vertex from path[] and mark it as unvisited
        path_index--;
        visited[u] = false;
    }

    void printPath(Path path) const {
        for (int i: path) {
            std::cout << i << ", ";
        }
        std::cout << std::endl;
    }

    Path shortest_path_naive(int from, int to) {
        std::vector<Path> all = all_paths(from, to);
        if (all.size() > 0) {
            Path shortestPath = all.at(0);
            std::cout << "content of all paths:" << std::endl;
            for (Path path: all) {
                if (path.size() < shortestPath.size()) {
                    shortestPath = path;
                }
                printPath(path);
            }
            std::cout << "content of shortest paths:" << std::endl;
            printPath(shortestPath);
            return shortestPath;
        }
    }


    inline bool node_exist(int id) const {
        auto iterator = nodes.find(id);
        bool doesExist = iterator != nodes.end();
        return doesExist;
    }

    inline int add_node(const N m) {
        Node node(node_counter, m);
        nodes.insert(std::make_pair(node_counter, node));
        return node_counter++;
    }


    int miniDist(int distance[], bool Tset[]) // finding minimum distance
    {
        int minimum = INT_MAX, ind;

        for (int k = 0; k < node_counter; k++) {
            if (Tset[k] == false && distance[k] <= minimum) {
                minimum = distance[k];
                ind = k;
            }
        }
        return ind;
    }

    Path shortest_path(int src, int dest) // adjacency matrix
    // shortest path based on average time
    {
        int graph[this->node_counter][this->node_counter];
        for (int i = 0; i < node_counter; i++) {
            for (int j = 0; j < node_counter; j++) {
                graph[i][j] = 0;
            }
        }
        for (int i = 0; i < node_counter; i++) {
            for (int j: dests[i]) {
                Edge edge = get_edge(j);
                graph[i][j] = 1;
            }
        }

        int distance[node_counter]; // // array to calculate the minimum distance for each node
        Path paths[this->node_counter];
        bool Tset[node_counter];// boolean array to mark visited and unvisited for each node
        for (int k = 0; k < node_counter; k++) {
            distance[k] = INT_MAX;
            //paths[k] = nullptr;
            Tset[k] = false;
        }

        distance[src] = 0;   // Source vertex distance is set 0
        for (int k = 0; k < node_counter; k++) {
            int m = miniDist(distance, Tset);
            Tset[m] = true;
            for (int k = 0; k < node_counter; k++) {
                // updating the distance of neighbouring vertex
                if (!Tset[k] && graph[m][k] && distance[m] != INT_MAX && distance[m] + graph[m][k] < distance[k]) {
                    distance[k] = distance[m] + graph[m][k];
                    for (int p: paths[m]) {
                        paths[k].push_back(p);
                    }
                    paths[k].push_back(m);
                }
            }
        }
        std::cout << "Distance from source vertex" << distance[dest] << std::endl;
        return paths[dest];
    }


    Path shortest_path(int src, int dest, std::function<int(int, int)> getWeightFunc) // adjacency matrix
    {
        int graph[this->node_counter][this->node_counter];
        for (int i = 0; i < node_counter; i++) {
            for (int j = 0; j < node_counter; j++) {
                graph[i][j] = 0;
            }
        }
        for (int i = 0; i < node_counter; i++) {
            for (int j: dests[i]) {
                //ED edge = get_edgeBySrcDest(i, j);
                //int weight = edge.getAverageTime();
                int weight = getWeightFunc(i, j);
                graph[i][j] = weight;
            }
        }

        int distance[node_counter]; // // array to calculate the minimum distance for each node
        Path paths[this->node_counter];
        bool Tset[node_counter];// boolean array to mark visited and unvisited for each node
        for (int k = 0; k < node_counter; k++) {
            distance[k] = INT_MAX;
            //paths[k] = nullptr;
            Tset[k] = false;
        }

        distance[src] = 0;   // Source vertex distance is set 0
        for (int k = 0; k < node_counter; k++) {
            int m = miniDist(distance, Tset);
            Tset[m] = true;
            for (int k = 0; k < node_counter; k++) {
                // updating the distance of neighbouring vertex
                if (!Tset[k] && graph[m][k] && distance[m] != INT_MAX && distance[m] + graph[m][k] < distance[k]) {
                    distance[k] = distance[m] + graph[m][k];
                    for (int p: paths[m]) {
                        paths[k].push_back(p);
                    }
                    paths[k].push_back(m);
                }
            }
        }
        std::cout << "Distance from source vertex" << distance[dest] << std::endl;
        return paths[dest];
    }



};

#endif //GRAPH_GRAPH_SP_HPP
