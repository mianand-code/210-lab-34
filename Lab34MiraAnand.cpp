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
    // the Pairs are made up of a destination vertex/node and a weight value of the associated edge
    vector<vector<Pair>> adjList;
    
    // graph Constructor
    // vector<Edge> is the argument/parameter of this constructor, which is a vector of Edge structs
    Graph(vector<Edge> const &edges) 
    {
        // resize the vector to hold SIZE elements (to hold each individual vertex/node)
        adjList.resize(SIZE);
        
        for (auto &edge: edges) // for each Edge struct in the vector
        {
            // access edge data and store it for our adjacency list
            int src = edge.src; // access source vertex/node
            int dest = edge.dest; // access destination vertex/node
            int weight = edge.weight; // access weight value

            // add an edge from src to dest along with its associated weight to the adjacency list
            adjList[src].push_back(make_pair(dest, weight));
            // for an undirected graph (where edges do not have a direction), add an edge in the opposite direction from dest to src also
            adjList[dest].push_back(make_pair(src, weight));
        }
    }
    
    // creation of a public member function, printGraph()
    // this function will print the graph's adjacency list that we just created above to the console
    void printGraph() 
    {
        cout << "Graph's adjacency list:" << endl;
        for (int i = 0; i < adjList.size(); i++) // for each vertex/node
        {
            cout << i << " --> "; // output the vertex/node #
            for (Pair v : adjList[i]) // iterates over each of the Pairs for each vertex/node
                cout << "(" << v.first << ", " << v.second << ") "; // v.first accesses the destination vertex/node, v.second accesses the weight value of the edge
            cout << endl;
        }
    }
};

int main() 
{
    // create a vector of Edge structs that will hold a list of edges
    vector<Edge> edges = 
    {
        // (x, y, w) —> edge from x to y having weight w
        {0,1,12},{0,2,8},{0,3,21},{2,3,6},{2,6,2},{5,6,6},{4,5,9},{2,4,4},{2,5,5}
    };
    
    // creates graph by using the Graph class
    // constructor within the Graph class is utilized here
    // edges vector is used as the argument/parameter
    Graph graph(edges);
    
    // printGraph() public member function call - prints the graph's adjacency list
    graph.printGraph();
    
    return 0;
}