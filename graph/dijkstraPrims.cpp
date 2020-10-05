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

void display(vector<vector<Edge*>>& gp){

    for(int i = 0; i < gp.size(); i++){
        cout<<i<<" -> ";
        for(Edge* e : gp[i])
            cout<<"("<<e->v<<", "<<e->w<<") ";
        cout<<endl;
    }
    cout<<endl;
}

void addEdge(vector<vector<Edge*>>& gp, int u, int v, int w){

    gp[u].push_back(new Edge(v, w));
    gp[v].push_back(new Edge(u, w));
}

void constructGraph(){

    addEdge(graph, 0, 1, 11);
    addEdge(graph, 0, 3, 10);
    addEdge(graph, 1, 2, 20);
    addEdge(graph, 2, 3, 40);
    addEdge(graph, 3, 4, 2);
    addEdge(graph, 4, 5, 2);
    addEdge(graph, 4, 6, 3);
    addEdge(graph, 5, 6, 8);
    // addEdge(0, 6, 10);
    // addEdge(7, 8, 10);
    // addEdge(8, 9, 20);
    // addEdge(9, 7, 30);

    display(graph);
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

class dpair{

    public:
        int vtx = 0;
        int pvtx = 0;
        int wsf = 0;

        dpair(int vtx, int pvtx, int wsf){
            this->vtx = vtx;
            this->pvtx = pvtx;
            this->wsf = wsf;
        }

        bool operator < (const dpair& o)const{
            return this->wsf > o.wsf;
        }
};

vector<vector<Edge*>> dgraph(n,vector<Edge*>());
vector<int> shortestDistance(n, 0);

void dijkstra(int src){

    priority_queue<dpair> que;
    vector<bool> visited(n, false);

    que.push(dpair(src, -1, 0));

    while(que.size() > 0){
        dpair rpair = que.top();
        que.pop();

        if(visited[rpair.vtx])
            continue;

        visited[rpair.vtx] = true;
        
        if(rpair.pvtx != -1){    //so that there is no edge from source;
            addEdge(dgraph, rpair.vtx, rpair.pvtx, rpair.wsf);
            shortestDistance[rpair.vtx] = rpair.wsf;
        } 

        for(Edge* e : graph[rpair.vtx]){
            if(!visited[e->v])
            que.push(dpair(e->v, rpair.vtx, rpair.wsf + e->w));
        }
    }

    display(dgraph);
    cout<<endl;
    for(int ele : shortestDistance){
        cout<<ele<<" ";
    }
}

vector<vector<Edge*>> pgraph(n, vector<Edge*>());

class primsPair{
    public:
        int vtx = 0;
        int pvtx = 0;
        int wt = 0;
        int wsf = 0;

        primsPair(int vtx, int pvtx, int wt, int wsf){
            this->vtx = vtx;
            this->pvtx = pvtx;
            this->wt = wt;
            this->wsf = wsf;
        }

        bool operator < (const primsPair& o)const{
            return this->wt - o.wt;
        }
};

void prims(int src){

    priority_queue<primsPair> que;
    que.push(primsPair(src, -1, 0, 0));
    vector<int> visited(n, false);

    while(que.size() > 0){

        primsPair rpair = que.top();
        que.pop();

        if(visited[rpair.vtx]){
            continue;
        }

        visited[rpair.vtx] = true;

        if(rpair.pvtx != -1){
            addEdge(pgraph, rpair.vtx, rpair.pvtx, rpair.wt);
            shortestDistance[rpair.vtx] = rpair.wsf;
        }

        for(Edge* e : graph[rpair.vtx]){
            if(!visited[e->v]){
                que.push(primsPair(e->v, rpair.vtx, e->w, rpair.wsf + e->w));
            }
        }
    }
}

int main(){

    constructGraph();

    // dijkstra(0);
    prims(4);

    return 0;
}