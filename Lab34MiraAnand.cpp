// COMSC-210 | Lab 34 | Mira Anand
// Module 13, Lesson: Graphs, Assignment: Network Graph
// IDE used: Visual Studio Code for Mac

#include <iostream>
#include <queue> // needed to use std::queue
#include <stack> // needed to use std::stack
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
    // vector<Edge> is being used as the argument/parameter of this constructor, which is a vector of Edge structs
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
    
    // void printGraph() public member function header
    // DESCRIPTION: this function will print the graph's adjacency list that we just created above to the console
    // ARGUMENTS: no arguments/parameters
    // RETURNS: nothing, void function
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

    // void DFS(int start) public member function header
    // *** this function was generated through an LLM via prompt engineering, as per assignment instructions ***
    // comments are my own, not generated by the LLM
    // DESCRIPTION: this function performs a Depth-First Search (DFS) by utilizing an std::stack
    // - DFS starts from a certain node/vertex and explores each path in depth
    // ARGUMENTS: int start, which represents the starting vertex/node
    // RETURNS: nothing, void function
    void DFS(int start) 
    {
        vector<bool> visited(SIZE, false); // tracks whether each node/vertex has been visited or not, via the use of a bool (true or false)
        stack<int> s; // creation of an std::stack to keep a track of the nodes/vertices
        
        s.push(start); // add the starting node/vertex onto the stack by using .push()
        cout << "DFS starting from vertex " << start << ": "; // output the starting node/vertex #
        
        while (!s.empty()) // while the stack is NOT empty
        {
            int node = s.top(); // access the top node/vertex of the stack by using .top() and store it in a variable
            s.pop(); // remove the top node/vertex from the stack by using .pop()
            
            if (!visited[node]) // if the node/vertex has NOT been visited yet
            {
                visited[node] = true; // set the visited bool to true for the node/vertex, to mark it as now visited
                cout << node << " "; // output the current node/vertex
            }
            
            for (auto &neighbor : adjList[node]) // traverse through all neighboring nodes/vertices of the current node/vertex
            {
                int adjNode = neighbor.first; // access the neighboring node/vertex of the current node/vertex by using .first and store it in a variable
                if (!visited[adjNode]) // if the neighboring node/vertex has NOT been visited
                    s.push(adjNode); // add that node onto the stack by using .push()
            }
        }
        cout << endl;
    }

    // void BFS(int start) public member function header
    // *** this function was generated through an LLM via prompt engineering, as per assignment instructions ***
    // comments are my own, not generated by the LLM
    // DESCRIPTION: this function performs a Breadth-First Search (BFS) by utilizing an std::queue
    // - DFS starts from a certain node/vertex and performs a level-by-level exploration instead of going in depth right from the start
    // ARGUMENTS: int start, which represents the starting vertex/node
    // RETURNS: nothing, void function
    void BFS(int start) 
    {
        vector<bool> visited(SIZE, false); // tracks whether each node/vertex has been visited or not, via the use of a bool (true or false)
        queue<int> q; // creation of an std::queue to keep a track of the nodes/vertices
        
        visited[start] = true; // set the visited bool flag to true for the starting node/vertex
        q.push(start); // add the starting node/vertex into the queue by using .push()
        
        cout << "BFS starting from vertex " << start << ": "; // output the starting node/vertex #
        
        while (!q.empty()) // while the queue is NOT empty
        {
            int node = q.front(); // access the front node/vertex of the queue by using .front() and store it in a variable
            q.pop(); // remove the top node/vertex from the queue by using .pop()
            cout << node << " "; // output the current node/vertex
            
            for (auto &neighbor : adjList[node]) // traverse through all neighboring nodes/vertices of the current node/vertex
            {
                int adjNode = neighbor.first; // access the neighboring node/vertex of the current node/vertex by using .first and store it in a variable
                if (!visited[adjNode]) // if the neighboring node/vertex has NOT been visited
                {
                    visited[adjNode] = true; // set the visited bool flag to true for the neighboring node/vertex
                    q.push(adjNode); // add that node into the queue by using .push()
                }
            }
        }
        cout << endl;
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

    // short driver program to exercise the BFS & DFS functions
    int startingVertex; // to hold the user's choice of which vertex they would like to start from for the DFS & BFS
    // get user input for the vertex they would like to start from when performing the BFS & DFS
    cout << "Enter the vertex you would like to start from: "; 
    cin >> startingVertex;

    graph.DFS(startingVertex); // DFS() public member function call - performs the DFS according to the user's chosen starting vertex
    graph.BFS(startingVertex); // BFS() public member function call - performs the BFS according to the user's chosen starting vertex
    
    return 0;
}