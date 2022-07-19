//
// Created by 39351 on 6/25/2022.
//
#include "iostream"
#include "../include/graph_t.hpp"

using namespace std;

Graph <std::string, EdgeData<RouteLength>> mygraph;

int getWeightFunc(int src, int dest){
    EdgeData<RouteLength> data = mygraph.get_edge_obj(src, dest);
    return data.getAverageTime(); //making decision: time, length, ...
}

int main() {
    cout<<"hello";

    EdgeData<RouteLength> ab;
    ab.set_string("A-B");
    ab.set_length(44.14);
    ab.setAverageTime(1);

    EdgeData<RouteLength> bc;
    bc.set_string("B-C");
    bc.set_length(4.14);
    bc.setAverageTime(2);

    EdgeData<RouteLength> cd;
    cd.set_string("C-D");
    cd.set_length(4.14);
    cd.setAverageTime(3);


    EdgeData<RouteLength> ac;
    ac.set_string("A-C");
    ac.set_length(4.14);
    ac.setAverageTime(100);

    int a = mygraph.add_node("A");
    int b = mygraph.add_node("B");
    int c = mygraph.add_node("C");
    int d = mygraph.add_node("D");


    mygraph.add_edge(ab, a, b);
    mygraph.add_edge(bc, b, c);
    mygraph.add_edge(cd, c, d);
    mygraph.add_edge(ac, a, c);

    auto path = mygraph.shortest_path(a, d, &getWeightFunc);
//
//    Graph<Node, Edge> g;
//    int a = g.add_node("A");
//    int b = g.add_node("B");
//    int c = g.add_node("C");
//    int d = g.add_node("D");
//    int e = g.add_node("E");
//
//    g.add_edge("ab", a, b);
//    g.add_edge("ac", a, c);
//    g.add_edge("bc", b, c);
//    g.add_edge("bd", b, d);
//    g.add_edge("cd", c, d);
//    g.add_edge("de", d, e);
//    g.add_edge("ce", c, e);
//    g.add_edge("ae", a, e);
//
//
//    auto path = g.shortest_path(1, 4);
    return 0;
}

