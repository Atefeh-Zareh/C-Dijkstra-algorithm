//
// Created by Muhammad Ashfaq on 6/18/22.
//

#include "iostream"
#include "../include/graph_nt.hpp"


void f(int i, Graph g);

int main() {
    std::cout << "start" << std::endl;

//    int graph[6][6]={
//            {0, 1, 2, 0, 0, 0},
//            {1, 0, 0, 5, 1, 0},
//            {2, 0, 0, 2, 3, 0},
//            {0, 5, 2, 0, 2, 2},
//            {0, 1, 3, 2, 0, 1},
//            {0, 0, 0, 2, 1, 0}};

    Graph g;

    /*int a = g.add_node("A");
    int b = g.add_node("B");
    int c = g.add_node("C");
    int d = g.add_node("D");
    int e = g.add_node("E");

    g.add_edge("ab", a, b);
    g.add_edge("ac", a, c);
    g.add_edge("bc", b, c);
    g.add_edge("bd", b, d);
    g.add_edge("cd", c, d);
    g.add_edge("de", d, e);
    g.add_edge("ce", c, e);
    g.add_edge("ae", a, e);*/


    int a = g.add_node("A");
    int b = g.add_node("B");
    int c = g.add_node("C");
    int d = g.add_node("D");
    int e = g.add_node("E");

    g.add_edge("ab", a, b);
    g.add_edge("ac", a, c);
    g.add_edge("bc", b, c);
    g.add_edge("bd", b, d);
    g.add_edge("cd", c, d);
    g.add_edge("de", d, e);
    g.add_edge("ce", c, e);
    g.add_edge("ae", a, e);


    auto path = g.shortest_path(1, 4);
    return 0;

/*    Graph g;

    int a = g.add_node("A");
    int b = g.add_node("B");
    int c = g.add_node("C");
    int d = g.add_node("D");
    int e = g.add_node("E");

    g.add_edge("ab", a, b);
    g.add_edge("ac", a, c);
    g.add_edge("bc", b, c);
    g.add_edge("bd", b, d);
    g.add_edge("cd", c, d);
    g.add_edge("de", d, e);
    g.add_edge("ce", c, e);
    g.add_edge("ad", a, e);

    auto res = g.all_paths(a, e);
    std::cout<<res.size();

    g.shortest_path_naive(a, e);*/
    std::cout << "end" << std::endl;
}

/*void f(int i, Graph g) {
    std::cout << " successors of " << i << std::endl;
    std::vector<int> aa = g.get_successors(i);
    if (aa.size() > 0) {
        for (int i: aa) {
            std::cout << i << ", ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "empty successors";
    }*/

//}
