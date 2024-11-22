// COMSC-210 | Lab 34 | Mira Anand
// Module 13, Lesson: Graphs, Assignment: Network Graph
// IDE used: Visual Studio Code for Mac

// Step #3 (wrapping a real-world application around the graph) was generated through an LLM via prompt engineering, as per assignment instructions
// - The real-world application I generated through the LLM was an "airport walking network"
// - The vertices/nodes are different areas within an airport and the edges are walking paths to these areas
// - The weights for each edge are walking times for each path in minutes

#include <iostream>
#include <queue> // needed to use std::queue
#include <stack> // needed to use std::stack
#include <vector> // needed to use std::vector
using namespace std;

// declaration and initialization of global const variables section
const int SIZE = 11; // represents the # of vertices/nodes in the graph
const int INF = 999999; // used to represent a type of "infinity" value, will be utilized in the shortestPath() public member function
const int STARTING_NODE = 0; // used to represent the starting node for the graph's functionalities (DFS, BFS, shortest path, minimum spanning tree)

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

    // creation of an std::vector that will hold the names of the different areas within the airport
    vector<string> areaNames = 
    {
        "Terminal 1", "Gate A1", "Gate A2", "Terminal 2", "Lounge 1",
        "Baggage Claim", "Duty-Free Shop", "Lounge 2", "Gate B1", "Gate B2", "Food Court"
    };
    
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
        cout << "Airport Walking Network:" << endl;
        cout << "--------------------------" << endl;
        for (int i = 0; i < adjList.size(); i++) // for each vertex/node
        {
            cout << "Area " << i << " (" << areaNames[i] << ") connects to:" << endl; // output the vertex/node # and its associated area name
            for (Pair v : adjList[i]) // iterates over each of the Pairs for each vertex/node
                cout << "  → Area " << v.first << " (" << areaNames[v.first] << ") - Walk Time: " << v.second << " minutes" << endl; // v.first accesses the destination vertex/node, v.second accesses the weight value of the edge
            cout << endl;
        }
    }

    // void DFS(int start) public member function header
    // *** this function was generated through an LLM via prompt engineering, as per assignment instructions ***
    // comments are my own, not generated by the LLM
    // DESCRIPTION: this function traverses the graph by performing a Depth-First Search (DFS)
    // - DFS utilizes an std::stack
    // - DFS starts from a certain node/vertex and explores each path in depth
    // ARGUMENTS: int start, which represents the starting vertex/node
    // RETURNS: nothing, void function
    void DFS(int start) 
    {
        vector<bool> visited(SIZE, false); // tracks whether each node/vertex has been visited or not, via the use of a bool (true or false)
        stack<int> s; // creation of an std::stack to keep a track of the nodes/vertices
        
        s.push(start); // add the starting node/vertex onto the stack by using .push()
        cout << "** Depth-First Search (DFS) Starting from Area " << start << " (" << areaNames[start] << ") **:" << endl;
        cout << "Purpose: Exploring the connected areas of the airport." << endl;
        cout << "----------------------------------------------------" << endl;
        
        while (!s.empty()) // while the stack is NOT empty
        {
            int node = s.top(); // access the top node/vertex of the stack by using .top() and store it in a variable
            s.pop(); // remove the top node/vertex from the stack by using .pop()
            
            if (!visited[node]) // if the node/vertex has NOT been visited yet
            {
                visited[node] = true; // set the visited bool to true for the node/vertex, to mark it as now visited
                cout << endl << "Exploring Area " << node << " (" << areaNames[node] << ")." << endl; // output the current node/vertex and its associated area name
            
                for (auto &neighbor : adjList[node]) // traverse through all neighboring nodes/vertices of the current node/vertex
                {
                    int adjNode = neighbor.first; // access the neighboring node/vertex of the current node/vertex by using .first and store it in a variable
                    int weight = neighbor.second; // access the edge weight of the current node/vertex by using .second and store it in a variable
                    if (!visited[adjNode]) // if the neighboring node/vertex has NOT been visited
                    {
                        cout << "  → Potential walk to Area " << adjNode << " (" << areaNames[adjNode] << ") - Walk Time: " << weight << " minutes." << endl;
                        s.push(adjNode); // add that node onto the stack by using .push()
                    }  
                } 
            }
        }
        cout << endl;
    }

    // void BFS(int start) public member function header
    // *** this function was generated through an LLM via prompt engineering, as per assignment instructions ***
    // comments are my own, not generated by the LLM
    // DESCRIPTION: this function traverses the graph by performing a Breadth-First Search (BFS)
    // - BFS utilizes an std::queue
    // - BFS starts from a certain node/vertex and performs a level-by-level exploration instead of going in depth right from the start
    // ARGUMENTS: int start, which represents the starting vertex/node
    // RETURNS: nothing, void function
    void BFS(int start) 
    {
        vector<bool> visited(SIZE, false); // tracks whether each node/vertex has been visited or not, via the use of a bool (true or false)
        queue<int> q; // creation of an std::queue to keep a track of the nodes/vertices
        
        visited[start] = true; // set the visited bool flag to true for the starting node/vertex
        q.push(start); // add the starting node/vertex into the queue by using .push()
        cout << "** Breadth-First Search (BFS) Starting from Area " << start << " (" << areaNames[start] << ") **:" << endl;
        cout << "Purpose: Analyzing all reachable areas level by level from the starting point." << endl;
        cout << "-----------------------------------------------------------------------------" << endl;
        
        while (!q.empty()) // while the queue is NOT empty
        {
            int node = q.front(); // access the front node/vertex of the queue by using .front() and store it in a variable
            q.pop(); // remove the top node/vertex from the queue by using .pop()
            cout << endl << "Visiting Area " << node << " (" << areaNames[node] << ")." << endl; // output the current node/vertex and its associated area name
            
            for (auto &neighbor : adjList[node]) // traverse through all neighboring nodes/vertices of the current node/vertex
            {
                int adjNode = neighbor.first; // access the neighboring node/vertex of the current node/vertex by using .first and store it in a variable
                int weight = neighbor.second; // access the edge weight of the current node/vertex by using .second and store it in a variable
                if (!visited[adjNode]) // if the neighboring node/vertex has NOT been visited
                {
                    cout << "  → Next reachable area: Area " << adjNode << " (" << areaNames[adjNode] << ") - Walk Time: " << weight << " minutes." << endl;
                    visited[adjNode] = true; // set the visited bool flag to true for the neighboring node/vertex
                    q.push(adjNode); // add that node into the queue by using .push()
                }
            }
        }
        cout << endl;
    }

    // void shortestPath(int start) public member function header
    // *** this function was generated through an LLM via prompt engineering, as per assignment instructions ***
    // comments are my own, not generated by the LLM
    // DESCRIPTION: this function finds the shortest path from a starting node to all other nodes in the graph by using Dijkstra's Algorithm
    // - Dijkstra's Algorithm works with non-negative edge weights, which is ideal for our current graph setup and the algorithm utilizes a priority queue data structure
    // ARGUMENTS: int start, which represents the starting vertex/node
    // RETURNS: nothing, void function
    void shortestPath(int start) 
    {
        vector<int> dist(SIZE, INF); // creation of an std::vector that will track shortest distances, starting out by initializing all node distances to the "INF" value
        // creation of a priority queue data structure
        // this data structure will hold nodes and distances - the priority queue ensures that shortest distances are given "priority" and placed at the top of the queue
        priority_queue<Pair, vector<Pair>, greater<Pair>> pq;
        
        dist[start] = 0; // the shortest distance to the starting node should be set to 0, because this represents the distance of the node to itself
        pq.push({0, start}); // the starting node and its distance is added to the priority queue by using .push()
        
        cout << "Shortest path from node " << start << ":" << endl;
        cout << "---------------------------------" << endl;

        while (!pq.empty()) // as long as the priority queue is NOT empty
        {
            // for lines 191-192, we are able to use .top() because the priority queue always gives "priority" to the shortest distances
            // - this means that the node with the shortest distance will always be at the "top" of the priority queue
            int node = pq.top().second; // access the node with the shortest distance (by using .top() & .second) and store it in a variable
            int d = pq.top().first; // access the shortest distance value itself (by using .top() & .first) and store it in a variable
            pq.pop(); // remove the node and its distance from the priority queue by using .pop()

            // perform a check to ensure that the shortest distance possible is being processed for a node
            if (d > dist[node]) 
                continue;

            for (auto &neighbor : adjList[node]) // traverse through all neighboring nodes of the current node
            {
                int adjNode = neighbor.first; // access the neighboring node of the current node by using .first and store it in a variable
                int weight = neighbor.second; // access the edge weight of the current node by using .second and store it in a variable

                if (dist[node] + weight < dist[adjNode]) // check if there is a shorter path to a neighboring node
                {
                    dist[adjNode] = dist[node] + weight; // if a shorter path was calculated, update the distance
                    pq.push({dist[adjNode], adjNode}); // add the neighboring node and its newly calculated distance to the priority queue by using .push()
                }
            }
        }

        // output the shortest paths from the starting node to all other nodes
        for (int i = 0; i < SIZE; i++) 
        {
            if (dist[i] == INF) 
                cout << start << " -> " << i << " : No path" << endl; // if a path has not been updated even after performing calculations
            else
                cout << start << " -> " << i << " : " << dist[i] << endl; // output the calculated shortest paths
        }
    }

    // void minimumSpanningTree() public member function header
    // *** this function was generated through an LLM via prompt engineering, as per assignment instructions ***
    // comments are my own, not generated by the LLM
    // DESCRIPTION: this function forms a minimum spanning tree of the graph by utilizing Prim's Algorithm
    // - a minimum spanning tree is formed by creating a "tree" of all of the graph's edges that show a connection to all of the graph's nodes, via the minimum total edge weight
    // ARGUMENTS: no arguments/parameters
    // RETURNS: nothing, void function
    void minimumSpanningTree() 
    {
        vector<int> parent(SIZE, -1); // creation of an std::vector to store parent nodes (parent nodes are used to form tree connections), starting out by initializing all nodes to -1
        vector<int> key(SIZE, INF); // creation of an std::vector that will store minimum edge weights, starting out by initializing all nodes to the "INF" value
        vector<bool> inMST(SIZE, false); // creation of an std::vector that will track if a node is a part of the minimum spanning tree yet or not, via the use of a bool (true or false)
        
        key[STARTING_NODE] = 0; // start with node 0 
        // creation of a priority queue data structure
        // the priority queue ensures that a node with the smallest minimum edge weight is given "priority" and placed at the top of the queue
        priority_queue<Pair, vector<Pair>, greater<Pair>> pq;
        pq.push({0, STARTING_NODE}); // the starting node and its minimum edge weight is added to the priority queue by using .push()
        
        while (!pq.empty()) // as long as the priority queue is NOT empty
        {
            int u = pq.top().second; // access the node with the smallest minimum edge weight (by using .top() & .second) and store it in a variable
            pq.pop(); // remove the node and its minimum edge weight from the priority queue by using .pop()
            
            inMST[u] = true; // the current node is now included in the minimum spanning tree so set the bool flag to true
            
            for (auto &neighbor : adjList[u]) // traverse through all neighboring nodes of the current node
            {
                int v = neighbor.first; // access the neighboring node of the current node by using .first and store it in a variable
                int weight = neighbor.second; // access the edge weight of the current node by using .second and store it in a variable
                
                // if the neighboring node is not yet included in the minimum spanning tree and if a smaller minimum edge weight has been found
                if (!inMST[v] && weight < key[v]) 
                {
                    parent[v] = u; // update the tree structure
                    key[v] = weight; // update the minimum edge weight
                    pq.push({key[v], v}); // add the neighboring node and its newly calculated minimum edge weight to the priority queue by using .push()
                }
            }
        }

        // output the minimum spanning tree structure that has been formed
        cout << endl << "Minimum Spanning Tree edges:" << endl;
        cout << "---------------------------------" << endl;
        for (int i = 1; i < SIZE; i++) 
        {
            cout << "Edge from " << parent[i] << " to " << i << " with walk time: " << key[i] << " minutes" << endl;
        }
    }
};

int main() 
{
    // create a vector of Edge structs that will hold a list of edges
    vector<Edge> edges = 
    {
        // (x, y, w) —> edge from x to y having weight w
        {0,1,15},{0,2,10},{0,3,25},{1,4,7},{1,5,11},{2,5,8},{2,6,12},{3,6,4},{3,7,6},{4,8,9},{5,9,5},{6,10,2},{7,8,13},{8,9,16},{9,10,14}
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
    cout << "Enter the area you would like to start from for the DFS, BFS, and shortest path: "; 
    cin >> startingVertex;
    cout << endl;

    graph.DFS(startingVertex); // DFS() public member function call - performs the DFS according to the user's chosen starting vertex
    graph.BFS(startingVertex); // BFS() public member function call - performs the BFS according to the user's chosen starting vertex
    graph.shortestPath(startingVertex); // shortestPath() public member function call - calculates the shortest path from the starting node to all other nodes

    graph.minimumSpanningTree(); // minimumSpanningTree() public member function call - generates a minimum spanning tree structure of the graph
    
    return 0;
}