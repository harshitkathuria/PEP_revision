#include<iostream>
#include<vector>
#include<stack>
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
    // graph[v].push_back(new Edge(u, w));
}

void constructGraph(){

    addEdge(0, 1, 10);
    addEdge(3, 0, 10);
    addEdge(1, 2, 10);
    addEdge(2, 3, 40);
    addEdge(3, 4, 2);
    addEdge(4, 5, 2);
    addEdge(6, 4, 3);
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

void topological_sort_(int src, vector<bool>& visited, stack<int>& st){

    visited[src] = true;

    for(Edge* e : graph[src]){
        if(!visited[e->v]){
            topological_sort_(e->v, visited, st);
        }
    }
    st.push(src);
}

stack<int> topological_sort(){

    vector<bool> visited(n, false);
    stack<int> st;

    for(int i = 0; i < n; i++){
        if(!visited[i])
            topological_sort_(i, visited, st);
    }

    // while(st.size() > 0){
    //     cout<<st.top()<<" ";
    //     st.pop();
    // }
    
    return st;
}

vector<vector<Edge*>> inv_graph(n, vector<Edge*>());

void inverse_graph(){

    for(int i = 0; i < n; i++){
        for(Edge* e : graph[i]){
            inv_graph[e->v].push_back(new Edge(i, e->w));
        }
    }
}

void dfs(int src, vector<bool>& visited){
    
    visited[src] = true;

    for(Edge* e : inv_graph[src]){
        if(!visited[e->v]){
            dfs(e->v, visited);
        }
    }
}

void kosaraju_algo(){

    stack<int> st = topological_sort();
    vector<bool> visited(n, false);
    inverse_graph();
    int ssc = 0;

    while(st.size() != 0){
        int rvtx = st.top();
        st.pop();

        if(visited[rvtx]){
            continue;
        }

        ssc++;
        dfs(rvtx, visited);
    }

    cout<<"Number of SSC: "<<ssc<<endl;
}

int main(){

    constructGraph();

    kosaraju_algo();

    return 0;
}