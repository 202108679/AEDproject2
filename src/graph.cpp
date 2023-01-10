#include "graph.h"
#include <climits>
#include <queue>
#include <unordered_set>

struct Destino{
    int target;
    list<string> companhias;
};

// Constructor: nr nodes and direction (default: undirected)
Graph::Graph(int num, bool dir) : n(num), hasDir(dir), nodes(num+1) {
}

// Add edge from source to destination with a certain weight
void Graph::addEdge(int src, int dest,vector<string> lines, double weight) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    nodes[src].adj.push_back({dest, weight, lines});
    if (!hasDir) nodes[dest].adj.push_back({src, weight, lines});
}

void Graph::addRestrictedEdge(int src, int dest,vector<string> lines, double weight) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    nodes[src].adj_res.push_back({dest, weight, lines});
    if (!hasDir) nodes[dest].adj.push_back({src, weight, lines});
}

void Graph::cleanRestrictedEdge(int src, int dest) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    nodes[src].adj_res.clear();
    if (!hasDir) nodes[dest].adj_res.clear();
}

void Graph::addArriveEdge(int src, int dest, vector<string> lines, double weight){
    if (src<1 || src>n || dest<1 || dest>n) return;
    nodes[dest].arrive.push_back({src, weight, lines});
    if (!hasDir) nodes[src].arrive.push_back({dest, weight, lines});
}

void Graph::addAirport(int v, Airports s){
    nodes[v].info = s;
}


// Breadth-First Search - BFS
// Traverse the nodes by increasing distance of number of links to reach them

void Graph::bfs(int v) {
    for (int s=1; s<=n; s++){
        nodes[s].visited = false;
        nodes[s].dist = -1;
    }
    nodes[v].dist = 0;
    queue<int> q; // queue of unvisited nodes
    q.push(v);
    nodes[v]. visited = true;
    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front(); q.pop();
        // cout << u << " "; // show node order
        for (auto e : nodes[u].adj) {
            int w = e.dest;
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
                nodes[w].dist = nodes[u].dist + 1;
            }
        }
    }
}

void Graph::bfs_2(int v) {
    for (int s=1; s<=n; s++){
        nodes[s].visited = false;
        nodes[s].dist = -1;
    }
    nodes[v].dist = 0;
    queue<int> q; // queue of unvisited nodes
    q.push(v);
    nodes[v]. visited = true;
    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front(); q.pop();
        // cout << u << " "; // show node order
        for (auto e : nodes[u].adj_res) {
            int w = e.dest;
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
                nodes[w].dist = nodes[u].dist + 1;
            }
        }
    }
}


void Graph::BFS_Min(int s){
    for (int v=1; v<=n; v++) {
        nodes[v].visited = false;
        nodes[v].dist = -1;
        nodes[v].pred.clear();
    }
    queue<int> q; // queue of unvisited nodes
    q.push(s);
    nodes[s].dist = 0;
    nodes[s].visited = true;
    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front();
        q.pop();
        for (auto e: nodes[u].adj) {
            int w = e.dest;
            nodes[w].pred.push_back({u,e.weight,e.lines});
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
                nodes[w].dist = nodes[u].dist + 1;
            }

        }
    }
}



vector<Path> Graph::PathsMin(int s, int d){
    BFS_Min(s);
    if(nodes[d].dist == -1) return {};
    vector<Path> paths;
    queue<Path> q;
    Path path ={{d},{}, 0};
    q.push(path);
    while(!q.empty()){
        path = q.front();
        q.pop();
        int first = path.ord.front();
        for (auto it = nodes[first].pred.begin(); it != nodes[first].pred.end(); it++){
            list<int> newOrd = path.ord;
            newOrd.push_front(it->dest);
            list<vector<string>> newPor = path.ports;
            newPor.push_front(it->lines);
            double newPer= path.per + it->weight;
            Path newPath = {newOrd,newPor,newPer};
            if(it->dest == s){
                paths.push_back(newPath);
            }
            else if(paths.empty() || newOrd.size() < nodes[d].dist + 1){
                q.push(newPath);
            }
        }
    }

    return paths;
}


int Graph::distance(int a, int b , bool complete) {
    if(a == b) return 0;
    if(complete){
        bfs(a);
    }
    else{
        bfs_2(a);
    }

    if(nodes[b].dist == -1)
        return -1;
    return nodes[b].dist;
}

vector<pair<int,int>> Graph::distance_2(int a, list<int> b, bool complete){
    int min = INT_MAX;
    vector<pair<int,int>> res;
    if(complete){
        bfs(a);
    }
    else{
        bfs_2(a);
    }
    for(int d : b){
        if(a == d) continue;
        if(nodes[d].dist < min && nodes[d].dist > 0){
            res.clear();
            min = nodes[d].dist;
        }
        if(nodes[d].dist == min){
            res.push_back({a,d});
        }
    }

    return res;
}

void Graph::distance_3(int a, list<int> &b, int &min, vector<pair<int,int>> &result, bool complete){
    if(complete){
        bfs(a);
    }
    else{
        bfs_2(a);
    }
    for(int d : b){
        if(a == d) continue;
        if(nodes[d].dist < min && nodes[d].dist > 0){
            result.clear();
            min = nodes[d].dist;
        }
        if(nodes[d].dist == min){
            result.push_back({a,d});
        }
    }

}

void Graph::BFS_Cond(int s){
    for (int v=1; v<=n; v++) {
        nodes[v].visited = false;
        nodes[v].dist = -1;
        nodes[v].pred.clear();
    }
    queue<int> q; // queue of unvisited nodes
    q.push(s);
    nodes[s].dist = 0;
    nodes[s].visited = true;
    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front();
        q.pop();
        for (auto e: nodes[u].adj_res) {
            int w = e.dest;
            nodes[w].pred.push_back({u,e.weight,e.lines});
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
                nodes[w].dist = nodes[u].dist + 1;
            }

        }
    }
}



vector<Path> Graph::PathsCond(int s, int d){
    BFS_Cond(s);
    if(nodes[d].dist == -1) return {};
    vector<Path> paths;
    queue<Path> q;
    Path path ={{d},{}, 0};
    q.push(path);
    while(!q.empty()){
        path = q.front();
        q.pop();
        int first = path.ord.front();
        for (auto it = nodes[first].pred.begin(); it != nodes[first].pred.end(); it++){
            list<int> newOrd = path.ord;
            newOrd.push_front(it->dest);
            list<vector<string>> newPor = path.ports;
            newPor.push_front(it->lines);
            double newPer= path.per + it->weight;
            Path newPath = {newOrd,newPor,newPer};
            if(it->dest == s){
                paths.push_back(newPath);
            }
            else if(paths.empty() || newOrd.size() < nodes[d].dist + 1){
                q.push(newPath);
            }
        }
    }

    return paths;
}


vector<int> Graph::targetAirports(int v){
    vector<int> final;
    for(Edge e : nodes[v].adj){
        final.push_back(e.dest);
    }
    return final;
}

unordered_set<string> Graph::leaveAirlines(int v){
    unordered_set<string> final;
    for(Edge e : nodes[v].adj){
        for(string s: e.lines)
        final.insert(s);
    }
    return final;
}

vector<int> Graph::arriveAirports(int v){
    vector<int> final;
    for(Edge e : nodes[v].arrive){
        final.push_back(e.dest);
    }
    return final;
}

unordered_set<string> Graph::arriveAirlines(int v){
    unordered_set<string> final;
    for(Edge e : nodes[v].arrive){
        for(string s: e.lines)
            final.insert(s);
    }
    return final;
}

void Graph::bfs_airports(int v, int max, vector<pair<int, int>> &distancia){
    for (int s=1; s<=n; s++){
        nodes[s].visited = false;
        nodes[s].dist = -1;
    }
    nodes[v].dist = 0;
    queue<int> q;
    q.push(v);
    nodes[v].visited = true;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        // cout << u << " "; // show node order
        for (auto e : nodes[u].adj) {
            int w = e.dest;
            if (!nodes[w].visited) {
                nodes[w].visited = true;
                nodes[w].dist = nodes[u].dist + 1;
                distancia.push_back({w,nodes[w].dist});
                if(nodes[w].dist < max) {
                    q.push(w);
                }
            }
        }
    }


}






