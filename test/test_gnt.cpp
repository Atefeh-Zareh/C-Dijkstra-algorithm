#include <catch2/catch.hpp>
#include "graph_nt.hpp"
#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

SCENARIO("Graph properties", "[graph nt]")
{
    GIVEN("A graph with some items") {
        Graph g;
        int a = g.add_node("A");
        int b = g.add_node("B");
        int c = g.add_node("C");
        int d = g.add_node("D");
        int ab = g.add_edge("msg-ab", a,b);
        int ac = g.add_edge("msg-ac", a,c);
        int bd = g.add_edge("msg-bd", b,d);
        int cd = g.add_edge("msg-cd", c,d);

        REQUIRE(g.get_node_data(a) == "A");
        REQUIRE(g.get_node_data(b) == "B");
        REQUIRE(g.get_node_data(c) == "C");
        REQUIRE(g.get_node_data(d) == "D");

        REQUIRE(ab == 0);
        REQUIRE(ac == 1);

        REQUIRE(g.get_edge_data(ab) == "msg-ab");
        REQUIRE(g.get_edge_data(ac) == "msg-ac");
        REQUIRE(g.get_edge_data(cd) == "msg-cd");
        REQUIRE(g.get_edge_data(bd) == "msg-bd");

        vector<int> succ_a = {b, c};
        REQUIRE(g.get_successors(a) == succ_a);
        vector<int> succ_b = {d};
        REQUIRE(g.get_successors(b) == succ_b);
        vector<int> prec_d = {b, c};
        REQUIRE(g.get_predecessors(d) == prec_d);

        WHEN("Copying the graph") {
            Graph g1(g);
            THEN ("We obtain the same graph, with the same indexes") {
                REQUIRE(g1.get_predecessors(d) == prec_d);
            }
        }
        WHEN("Changing the copy") {
            Graph g2(g);
            g2.add_edge("msg-bc", b,c);
            THEN ("The original is not changed") {
                REQUIRE(g.get_successors(b).size() == 1);
                REQUIRE(g2.get_successors(b).size() == 2);
            }
        }
    }
}

SCENARIO("Computing paths", "[graph nt]")
{
    GIVEN("A graph with some elements and no loops") {
        Graph g;
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

        WHEN ("Computing all paths") {
            auto paths = g.all_paths(a, e);
            REQUIRE(paths.size() == 5);
        }
    }
}

SCENARIO("Shortest path", "[graph nt]")
{
    GIVEN("A graph with some elements and no loops") {
        Graph g;
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

        WHEN ("Computing shortest path") {
            auto shortestPath = g.shortest_path_naive(a, b);
            REQUIRE(shortestPath.size() == 6);
//            REQUIRE(shortestPath == );//e
        }
    }
}

