#include<iostream>
#include<vector>
#include<queue>

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

void display(){

    for(int i = 0; i < graph.size(); i++){
        cout<<i<<" -> ";
        for(Edge* e : graph[i])
            cout<<"("<<e->v<<", "<<e->w<<") ";
        cout<<endl;
    }
    cout<<endl;
}

void addEdge(int u, int v, int w){

    graph[u].push_back(new Edge(v, w));
    graph[v].push_back(new Edge(u, w));
}

void constructGraph(){

    addEdge(0, 1, 10);
    addEdge(0, 3, 10);
    addEdge(1, 2, 10);
    addEdge(2, 3, 40);
    addEdge(3, 4, 2);
    addEdge(4, 5, 2);
    addEdge(4, 6, 3);
    addEdge(5, 6, 8);
    // addEdge(0, 6, 10);
    // addEdge(7, 8, 10);
    // addEdge(8, 9, 20);
    // addEdge(9, 7, 30);

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

    graph[u].erase(graph[u].begin() + i);

    int j = 0;
    while(j < graph[u].size()){
        Edge* e = graph[u][j];
        if(e->v == u)
            break;  
        j++;
    }

    graph[v].erase(graph[v].begin() + j);
}

void removeVtx(int u){

    while(graph[u].size() != 0){
        Edge* e = graph[u][graph[u].size() - 1];
        removeEdge(u, e->v);
    }
}

int hamiltonian_cycle(int src, int osrc, int EdgeCount, vector<bool>& visited, string psf){

    // cout<<EdgeCount<<" ";
    if(EdgeCount == graph.size() - 1){
        bool flag = false;
        for(Edge* e : graph[src]){
            if(e->v == osrc){
                flag = true;
                cout<<"Cycle: "<<psf<<endl;
                
                return 1;
            }
        }
        cout<<"Path: "<<psf<<endl;
        return 0;
    }

    visited[src] = true;
    int count = 0;

    for(Edge* e : graph[src]){
        if(!visited[e->v]){
            count += hamiltonian_cycle(e->v, osrc, EdgeCount + 1, visited, psf + to_string(e->v) + " ");
        }
    }
    visited[src] = false;

    return count;
}

bool isBipartite(int src, vector<int>& visited){

    queue<pair<int, int>> que;
    que.push({src, 0});
    bool flag = true;

    while(que.size() > 0){
        pair<int, int> rpair = que.front();
        que.pop();

        int rvtx = rpair.first;

        if(visited[rvtx] != -1){
            if(rpair.second != visited[rvtx]){
                cout<<"Conflict: "<<rvtx<<endl;
                flag = false;
            }
            continue;
        }

        visited[rvtx] = rpair.second;

        for(Edge* e : graph[rvtx]){
            if(visited[e->v] == -1){
                que.push({e->v, (rpair.second + 1) % 2});
            }
        }
    }
    return flag;
}

void bipartite(){
    
    int comp = 1;
    vector<int> visited(n, -1);

    for(int i = 0; i < graph.size(); i++){
        if(visited[i] == -1){
            cout<<comp<<": "<<(boolalpha)<<isBipartite(i, visited)<<endl;
        }
    }
}

int main(){

    constructGraph();

    vector<bool> visited(n, false);

    // cout<<hamiltonian_cycle(0, 0, 0, visited, "0 ")<<endl;
    bipartite();

    return 0;
}