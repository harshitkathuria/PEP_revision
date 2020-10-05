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

/*
    BFS

    ALGORITHM

    1. que <- src
    2. while(que.size() != 0){
        2.1 remove front from queue
        2.2 visited[front] = true;
        2.3 add all unvisited neighbour
    }
*/

void bfs(int src, int des, vector<bool>& visited){

    queue<int> que;
    que.push(src);
    que.push(-1);

    int cycle = 0, level = 0;

    while(que.size() != 1){
        int rvtx =  que.front();
        que.pop();

        if(rvtx == -1){
            level++;
            que.push(-1);
            continue;
        }

        if(visited[rvtx]){
            cycle++;
            cout<<"Cycle: "<<cycle<<" @ "<<rvtx<<endl;
            continue;
        }

        visited[rvtx] = true;

        if(rvtx == des){
            cout<<"Goal: "<<level<<endl;
        }

        for(Edge* e : graph[rvtx]){
            if(!visited[e->v]){
                que.push(e->v);
            }
        }
    }
}

void bfs2(int src, int des, vector<bool>& visited){

    queue<int> que;
    que.push(src);
    
    int level = 0, cycle = 0; 

    while(que.size() > 0){
        int size = que.size();
        while(size-- > 0){

            int rvtx = que.front();
            que.pop();

            if(visited[rvtx]){
                cout<<"Cycle: "<<++cycle<<" @ "<<rvtx<<endl;
                continue;
            }

            visited[rvtx] = true;

            if(rvtx == des){
                cout<<"Goal: "<<level<<endl;
            }

            for(Edge* e: graph[rvtx]){
                if(!visited[e->v]){
                    que.push(e->v);
                }
            }
        }
        level++;
    }
}

void bfs3(int src, int des, vector<bool>& visited){

    queue<pair<int, int>> que;
    que.push({src, 0});
    int cycle = 0;

    while(que.size() > 0){

        pair<int, int> rp = que.front();
        que.pop();

        int rvtx = rp.first;
        int rlevel = rp.second;

        if(visited[rvtx]){
            cout<<"Cycle: "<<++cycle<<" @ "<<rvtx<<endl;
            continue;
        }

        visited[rvtx] = true;

        if(rvtx == des){
            cout<<"Goal: "<<rlevel<<endl;
        }

        for(Edge* e : graph[rvtx]){
            if(!visited[e->v]){
                que.push({e->v, (rlevel + 1)});
            }
        }
    }
}

int main(){

    constructGraph();
    vector<bool> visited(n, false);

    // bfs(0, 6, visited);
    // bfs2(0, 6, visited);
    bfs3(0, 6, visited);

    return 0;
}