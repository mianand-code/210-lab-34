// COMSC-210 | Lab 34 | Mira Anand
// Module 13, Lesson: Graphs, Assignment: Network Graph
// IDE used: Visual Studio Code for Mac

#include <iostream>
#include <vector> // needed to use std::vector
using namespace std;

// declaration and initialization of global const variables section
const int SIZE = 7; // represents the # of vertices/nodes in the graph

struct Edge // creation of a struct named "Edge" to represent edges in the graph
{
    // int src - to hold a source vertex/node
    // int dest - to hold a destination vertex/node
    // int weight - to hold a weight value of the edge
    int src, dest, weight;
};

typedef pair<int, int> Pair; // creation of an alias named "Pair" that references a pair of 2 ints

class Graph // creation of a class named "Graph", to represent the creation of the graph
{
// public member functions/methods
public:
    // creation of a vector of vectors of Pairs to represent an adjacency list
    // the first/outer vector will hold all of the vertices/nodes
    // the second/inner vector will hold "Pairs"
    // within these Pairs, there will be a destination vertex/node and a weight value of the edge
    vector<vector<Pair>> adjList;
    
    // Graph Constructor
    Graph(vector<Edge> const &edges) {
        // resize the vector to hold SIZE elements of type vector<Edge>
        adjList.resize(SIZE);
        
        // add edges to the directed graph
        for (auto &edge: edges) {
            int src = edge.src;
            int dest = edge.dest;
            int weight = edge.weight;
            // insert at the end
            adjList[src].push_back(make_pair(dest, weight));
            // for an undirected graph, add an edge from dest to src also
            adjList[dest].push_back(make_pair(src, weight));
        }
    }
    
    // Print the graph's adjacency list
    void printGraph() {
        cout << "Graph's adjacency list:" << endl;
        for (int i = 0; i < adjList.size(); i++) {
            cout << i << " --> ";
            for (Pair v : adjList[i])
                cout << "(" << v.first << ", " << v.second << ") ";
            cout << endl;
        }
    }
};

int main() 
{
    // Creates a vector of graph edges/weights
    vector<Edge> edges = {
        // (x, y, w) —> edge from x to y having weight w
        {0,1,12},{0,2,8},{0,3,21},{2,3,6},{2,6,2},{5,6,6},{4,5,9},{2,4,4},{2,5,5}
    };
    
    // Creates graph
    Graph graph(edges);
    
    // Prints adjacency list representation of graph
    graph.printGraph();
    
    return 0;
}