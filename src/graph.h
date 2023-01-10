#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <vector>
#include <list>
#include <iostream>
#include <map>
#include <unordered_set>
#include "Airlines.h"
#include "Path.h"
#include "Airports.h"


using namespace std;

class Graph {
    struct Edge {
        int dest;   // Destination node
        double weight; // An integer weight
        vector<string> lines; //
    };

    struct Node {
        list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        int dist;
        list<Edge> pred;
        bool visited;
        Airports info;

        list<Edge> adj_res; // ailines restritas

        list<Edge> arrive; // The list of ingoing edges (to adjacent nodes)
    };

    int n;              // Graph size (vertices are numbered from 1 to n)
    bool hasDir;        // false: undirect; true: directed
    vector<Node> nodes; // The list of nodes being represented

public:
    // Constructor: nr nodes and direction (default: undirected)
    Graph(int nodes = 0, bool dir = false);

    // Add edge from source to destination with a certain weight
    void addEdge(int src, int dest, vector<string> lines, double = 1);
    void addRestrictedEdge(int src, int dest, vector<string> lines, double weight = 1);
    void addArriveEdge(int src, int dest, vector<string> lines, double weight = 1);
    void cleanRestrictedEdge(int src, int dest);


    vector<int> targetAirports(int v);
    unordered_set<string> leaveAirlines(int v);
    vector<int> arriveAirports(int v);
    unordered_set<string> arriveAirlines(int v);


    void BFS_Cond(int s);
    vector<Path> PathsCond(int s, int d);

    void BFS_Min(int s);
    vector<Path> PathsMin(int s, int d);


    void bfs(int v);
    void bfs_2(int v);


    int distance(int a, int b, bool complete = true);
    vector<pair<int,int>> distance_2(int a, list<int> b, bool complete = true);
    void distance_3(int a, list<int> &b, int &n, vector<pair<int,int>> &result, bool complete = true);

    void bfs_airports(int i,int max, vector<pair<int, int>> &v);

    void addAirport(int v, Airports s);

};

#endif