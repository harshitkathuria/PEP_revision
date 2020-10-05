#include<iostream>
#include<vector>

using namespace std;

class Edge{
    public:
        int v = 0;
        int w = 0;
    
    Edge(int v, int w){
        this->v = v;
        this->w = w;
    }
};

int n = 7;
vector<vector<Edge*>> graph(n, vector<Edge*>());

void addEdge(int u, int v, int w){

    graph[u].push_back(new Edge(v, w));
    graph[v].push_back(new Edge(u, w));
}

void display(){

    for(int i = 0; i < graph.size(); i++){
        cout<<i<<" -> ";
        for(Edge* e : graph[i]){
            cout<<"("<<e->v<<", "<<e->w<<") ";
        }
        cout<<endl;
    }
}

void constructGraph(){
    
    addEdge(0, 1, 10);
    addEdge(0, 3, 10);
    addEdge(1, 2, 10);
    addEdge(2, 3, 10);
    addEdge(3, 4, 10);
    addEdge(4, 5, 10);
    addEdge(4, 6, 10);
    addEdge(5, 6, 10);

    display();
}

void removeEdge(int u, int v){

    int i = 0;
    while(i < graph[u].size()){
        Edge* e = graph[u][i];
        if(e->v == v)
            break;
        i++;
    }

    int j = 0;
    while(j < graph[v].size()){
        Edge* e = graph[v][j];
        if(e->v == u)
            break;
        j++;
    }

    graph[u].erase(graph[u].begin() + i);
    graph[v].erase(graph[v].begin() + j);
}

void remove_vtx(int u){

    while(graph[u].size() != 0){
        Edge* e = graph[u][graph[u].size() - 1];
        removeEdge(u, e->v);
    }
}

void hasPath(int src, int des, vector<bool>& visited, string psf){

    cout<<psf<<endl;
    visited[src] = true;

    for(Edge* e : graph[src]){
        if(!visited[e->v]){
            hasPath(e->v, des, visited, psf + to_string(e->v));
        }
    }
}

void allPath(int src, int des, vector<bool>visited, string psf){

    // if(src == des)2
    cout<<psf<<endl;
    visited[src] = true;

    for(Edge* e : graph[src]){
        if(!visited[e->v]){
            allPath(e->v, des, visited, psf + to_string(e->v));
        }
    }
    visited[src] = false;
}

int swsf = 1e8;
string spsf = "";

int lwsf = -1e8;
string lpsf = "";

void allSolution(int src, int des, vector<bool>& visited, int wsf, string psf){

    if(src == des){
        if(wsf < swsf){
            swsf = wsf;
            spsf = psf;
        }
        if(wsf > lwsf){
            lwsf = wsf;
            lpsf = psf;
        }
    }

    visited[src] = true;

    for(Edge* e : graph[src]){
        if(!visited[e->v]){
            allSolution(e->v, des, visited, wsf + e->w, psf + to_string(e->v));
        }
    }
    visited[src] = false;
}

/*
        DFS

    ALGORITHM:
    1. visited[src] = true;
    2. call for unvisited neighbour 

    */

void dfs(int src, vector<bool>& visited){

    visited[src] = true;

    for(Edge* e : graph[src]){
        if(!visited[e->v])
            dfs(e->v, visited);
    }
}

void GetConnectedComponents(){

    vector<bool> visited(n, false);
    int comp = 0;
    for(int i = 0; i < graph.size(); i++){
        if(!visited[i]){
            comp++;
            dfs(i, visited);
        }
    }
    
    cout<<"No of component: "<<comp<<endl;
}

int main(){

    vector<bool> visited(n, false);

    constructGraph();
    // removeEdge(3, 4);
    // remove_vtx(3);
    cout<<endl;

    // hasPath(0, 6, visited, "0");
    // allPath(0, 6, visited, "0");

    // allSolution(0, 6, visited, 0, "0")
    
    GetConnectedComponents();

    // display();

    return 0;
}