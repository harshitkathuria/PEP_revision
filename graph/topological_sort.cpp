#include<iostream>
#include<vector>
#include<stack>

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
    // graph[v].push_back(new Edge(u, w));
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

bool topological_sort_(int src, vector<bool>& visited, stack<int>& st, vector<bool>& cycle){

    visited[src] = true;
    cycle[src] = true;
    bool res = false;

    for(Edge* e : graph[src]){
        if(!visited[e->v]){
            res = res || topological_sort_(e->v, visited, st, cycle);
        }
        else if(cycle[src] == true){
            return true;
        }
    }
    st.push(src);
    cycle[src] = false;
}

void topological_sort(){

    vector<bool> visited(n, false);
    vector<bool> cycle(n, false);
    stack<int> st;
    bool res = false;

    for(int i = 0; i < n; i++){
        if(!visited[i]){
            res = res || topological_sort_(i, visited, st, cycle);
        }
    }

    while(res == false && st.size() > 0){
        cout<<st.top()<<" ";
        st.pop();
    }
}

int main(){

    constructGraph();

    topological_sort();

    return 0;
}