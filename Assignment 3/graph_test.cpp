///*
//
//  == Explanation and rational of testing ==
//
//  Explain and justify how you approached testing, the degree
//   to which you're certain you have covered all possibilities,
//   and why you think your tests are that thorough.
//
//*/
//
#include "assignments/dg/graph.h"
#include "catch.h"

// TODO(students): Fill this in.
//InsertNode
SCENARIO("Inserting nodes into a graph") {
WHEN("You have two identical nodes") {
gdwg::Graph<std::string, int> g;
std::string a{"hello"};
std::string b{"hi"};
std::string c{"hello"};
THEN("You would get true if successfully inserts, false otherwise") {
auto t1 = g.InsertNode(a);
auto t2 = g.InsertNode(b);
auto t3 = g.InsertNode(c);
REQUIRE(t1 == true);
REQUIRE(t2 == true);
REQUIRE(t3 == false);
}
}
}

 //InsertEdge
 SCENARIO("Inserting edges into a graph, error case") {
   WHEN("Either src of dst can not be found in the graph") {
     gdwg::Graph<std::string, int> g;
     std::string a{"aaa"};
     std::string b{"bbb"};
     std::string c{"ccc"};
     std::string d{"ddd"};
     g.InsertNode(a);
     g.InsertNode(b);
     THEN("You will get a runtime_error") {
       REQUIRE_THROWS_WITH(g.InsertEdge(a, c, 1),
         "Cannot call Graph::InsertEdge when either src or dst node does not exist");
     }
   }
 }

SCENARIO("Inserting edges into a graph") {
WHEN("Some edges already exist in the graph while others not") {
gdwg::Graph<std::string, int> g;
std::string a{"aaa"};
std::string b{"bbb"};
std::string c{"ccc"};
g.InsertNode(a);
g.InsertNode(b);
g.InsertNode(c);
g.InsertEdge(a, b, 1);
g.InsertEdge(a, c, 2);
THEN("You will get true if successfully inserts, false otherwise") {
auto t1 = g.InsertEdge(a, b, 1);
auto t2 = g.InsertEdge(a, b, 2);
auto t3 = g.InsertEdge(b, c, 3);
REQUIRE(t1 == false);
REQUIRE(t2 == true);
REQUIRE(t3 == true);
}
}
}

// DeteleNode
SCENARIO("Deleting nodes from a graph") {
WHEN("Some nodes exist in the graph while others not") {
gdwg::Graph<std::string, int> g;
std::string a{"aaa"};
std::string b{"bbb"};
std::string c{"ccc"};
g.InsertNode(a);
g.InsertNode(b);
THEN("You will get true if successfully deletes, false otherwise") {
auto t1 = g.DeleteNode(a);
auto t2 = g.DeleteNode(b);
auto t3 = g.DeleteNode(c);
REQUIRE(t1 == true);
REQUIRE(t2 == true);
REQUIRE(t3 == false);
}
}
}

// Replace
SCENARIO("Replace data in a graph, error case") {
WHEN("If no node that contains value oldData can be found") {
gdwg::Graph<std::string, int> g;
std::string a{"aaa"};
std::string b{"bbb"};
std::string c{"ccc"};
std::string d{"ddd"};
g.InsertNode(a);
THEN("You will get a runtime_error") {
REQUIRE_THROWS_WITH(g.Replace(b, c),
"Cannot call Graph::Replace on a node that doesn't exist");
REQUIRE_THROWS_WITH(g.Replace(d, c),
"Cannot call Graph::Replace on a node that doesn't exist");
REQUIRE_THROWS_WITH(g.Replace(c, d),
"Cannot call Graph::Replace on a node that doesn't exist");
}
}
}

SCENARIO("Replace data in a graph") {
WHEN("Some nodes already exist in the graph while others not") {
gdwg::Graph<std::string, int> g;
std::string a{"aaa"};
std::string b{"bbb"};
std::string c{"ccc"};
std::string d{"aaa"};
g.InsertNode(a);
g.InsertNode(b);
THEN("You will get true if successfully replaces, false otherwise") {
auto t1 = g.Replace(b, c);
auto t2 = g.Replace(a, d);
REQUIRE(t1 == true);
REQUIRE(t2 == false);
}
}
}

// Clear
SCENARIO("Remove all the nodes and edges in a graph") {
WHEN("You want to clear a graph") {
gdwg::Graph<std::string, int> g;
std::string a{"aaa"};
std::string b{"bbb"};
g.InsertNode(a);
g.InsertNode(b);
g.InsertEdge(a, b, 1);
THEN("You will get an empty graph") {
g.Clear();
std::vector<std::string> emptyVector{};
REQUIRE(g.GetNodes() == emptyVector);
}
}
}

// IsNode
SCENARIO("Checks the nodes if they are in a graph") {
WHEN("Some nodes exist in the graph while others not") {
gdwg::Graph<std::string, int> g;
std::string a{"aaa"};
std::string b{"bbb"};
std::string c{"ccc"};
std::string d{"ddd"};
g.InsertNode(a);
g.InsertNode(b);
THEN("You will get true if the node is in the graph, false otherwise") {
auto t1 = g.IsNode(a);
auto t2 = g.IsNode(b);
auto t3 = g.IsNode(c);
auto t4 = g.IsNode(d);
REQUIRE(t1 == true);
REQUIRE(t2 == true);
REQUIRE(t3 == false);
REQUIRE(t4 == false);
}
}
}

// IsConnected
SCENARIO("Check the nodes if they are connected in a graph, error case") {
WHEN("If either src or dst is not in the graph") {
gdwg::Graph<std::string, int> g;
std::string a{"aaa"};
std::string b{"bbb"};
std::string c{"ccc"};
std::string d{"ddd"};
g.InsertNode(a);
THEN("You will get a runtime_error") {
REQUIRE_THROWS_WITH(g.IsConnected(a, b),
"Cannot call Graph::IsConnected if src or dst node don't exist in the graph");
REQUIRE_THROWS_WITH(g.IsConnected(c, a),
"Cannot call Graph::IsConnected if src or dst node don't exist in the graph");
REQUIRE_THROWS_WITH(g.IsConnected(c, d),
"Cannot call Graph::IsConnected if src or dst node don't exist in the graph");
}
}
}

SCENARIO("Check the nodes if they are connected in a graph") {
WHEN("Some nodes are connected in the graph while others not") {
gdwg::Graph<std::string, int> g;
std::string a{"aaa"};
std::string b{"bbb"};
std::string c{"ccc"};
g.InsertNode(a);
g.InsertNode(b);
g.InsertNode(c);
g.InsertEdge(a, b, 1);
THEN("You will get true if the edge src -> dst exists in the graph, false otherwise") {
auto t1 = g.IsConnected(a, b);
auto t2 = g.IsConnected(b, a);
auto t3 = g.IsConnected(a, c);
REQUIRE(t1 == true);
REQUIRE(t2 == false);
REQUIRE(t3 == false);
}
}
}

// GetNodes
SCENARIO("Get all the nodes in a graph") {
WHEN("The nodes are unordered") {
gdwg::Graph<std::string, int> g;
std::string a{"aaa"};
std::string b{"bbb"};
std::string c{"ccc"};
g.InsertNode(a);
g.InsertNode(c);
g.InsertNode(b);
THEN("You will get a sorted vector containing all the nodes") {
auto t = g.GetNodes();
std::vector<std::string> v{};
v.push_back("aaa");
v.push_back("bbb");
v.push_back("ccc");
REQUIRE(t == v);
}
}
}

// GetConnected
SCENARIO("Get all the nodes that connect to the src node in a graph, error case") {
WHEN("If src is not in the graph") {
gdwg::Graph<std::string, int> g;
std::string a{"aaa"};
std::string b{"bbb"};
std::string c{"ccc"};
std::string d{"ddd"};
g.InsertNode(a);
THEN("You will get a out_of_range") {
REQUIRE_THROWS_WITH(g.GetConnected(b),
"Cannot call Graph::GetConnected if src doesn't exist in the graph");
REQUIRE_THROWS_WITH(g.GetConnected(c),
"Cannot call Graph::GetConnected if src doesn't exist in the graph");
REQUIRE_THROWS_WITH(g.GetConnected(d),
"Cannot call Graph::GetConnected if src doesn't exist in the graph");
}
}
}

SCENARIO("Get all the nodes that connect to the src node in a graph") {
WHEN("The nodes are unordered") {
gdwg::Graph<std::string, int> g;
std::string a{"aaa"};
std::string b{"bbb"};
std::string c{"ccc"};
std::string d{"ddd"};
g.InsertNode(a);
g.InsertNode(b);
g.InsertNode(c);
g.InsertNode(d);
g.InsertEdge(a, c, 2);
g.InsertEdge(a, b, 1);
g.InsertEdge(b, a, 3);
THEN("You will get a sorted vector containing all the nodes that connects to the src") {
auto t = g.GetConnected(a);
std::vector<std::string> v{};
v.push_back("bbb");
v.push_back("ccc");
REQUIRE(t == v);
}
}
}

// GetWeights
SCENARIO("Get all the weights between two nodes, error case") {
WHEN("If either src or dst is not in the graph") {
gdwg::Graph<std::string, int> g;
std::string a{"aaa"};
std::string b{"bbb"};
std::string c{"ccc"};
std::string d{"ddd"};
g.InsertNode(a);
g.InsertNode(b);
THEN("You will get a out_of_range") {
REQUIRE_THROWS_WITH(g.GetWeights(a, c),
"Cannot call Graph::GetWeights if src or dst node don't exist in the graph");
REQUIRE_THROWS_WITH(g.GetWeights(c, b),
"Cannot call Graph::GetWeights if src or dst node don't exist in the graph");
REQUIRE_THROWS_WITH(g.GetWeights(c, d),
"Cannot call Graph::GetWeights if src or dst node don't exist in the graph");
}
}
}

SCENARIO("Get all the weights between two nodes") {
WHEN("The weights are unordered") {
gdwg::Graph<std::string, int> g;
std::string a{"aaa"};
std::string b{"bbb"};
g.InsertNode(a);
g.InsertNode(b);
g.InsertEdge(a, b, 3);
g.InsertEdge(a, b, 2);
g.InsertEdge(a, b, 1);
THEN("You will get a sorted vector containing all the weights between two nodes") {
auto t = g.GetWeights(a, b);
std::vector<int> v{};
v.push_back(1);
v.push_back(2);
v.push_back(3);
REQUIRE(t == v);
}
}
}


// erase
SCENARIO("Deletes an edge from src to dst with weight w") {
WHEN("Some edges exist in the graph while others not") {
gdwg::Graph<std::string, int> g;
std::string a{"aaa"};
std::string b{"bbb"};
std::string c{"ccc"};
g.InsertNode(a);
g.InsertNode(b);
g.InsertNode(c);
g.InsertEdge(a, b, 1);
g.InsertEdge(a, c, 2);
THEN("You will get true if successfully deletes, false otherwise") {
auto t1 = g.erase(a, b,1);
auto t2 = g.erase(a, c,2);
auto t3 = g.erase(b, c,0);
REQUIRE(t1 == true);
REQUIRE(t2 == true);
REQUIRE(t3 == false);
}
}
}


