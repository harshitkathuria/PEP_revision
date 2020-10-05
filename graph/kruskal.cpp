#include<iostream>
#include<vector>
#include<algorithm>

#define pii pair<int, int>
#define piii pair<int, pii>

using namespace std;

void display(vector<vector<pii>>& graph){

    int i = 0;

    for(vector<pii> arr: graph){
        cout<<i<<" -> ";
        for(pii p : arr){
            cout<<"("<<p.first<<", "<<p.second<<") ";
        }
        cout<<endl;
        i++;
    }
}

void merge(int p1, int p2, vector<int>& par, vector<int>& size){

    if(size[p1] > size[p2]){
        par[p2] = p1;
        size[p1] += size[p2];
    }
    else{
        par[p1] = p2;
        size[p2] += size[p1];
    }
}

int findPar(int vtx, vector<int>& par){

    if(par[vtx] == vtx){
        return vtx;
    }

    par[vtx] = findPar(par[vtx], par);
    return par[vtx];
}

void kruskal(vector<piii>& arr, int n, vector<int>& par, vector<int>& size){

    vector<vector<pii>> graph(n, vector<pii>());

    for(int i = 0; i < n; i++){
        piii rp = arr[i];

        int p1 = findPar(rp.second.first, par);
        int p2 = findPar(rp.second.second, par);

        if(p1 != p2){
            merge(p1, p2, par, size);
            graph[rp.second.first].push_back({rp.second.second, rp.first});
            graph[rp.second.second].push_back({rp.second.first, rp.first});
        }
    }
    display(graph);
}

int main(){

    int n = 7;
    vector<piii> arr;

    arr.push_back({10, {0, 1}});
    arr.push_back({10, {0, 3}});
    arr.push_back({10, {1, 2}});
    arr.push_back({10, {0, 1}});
    arr.push_back({40, {2, 3}});
    arr.push_back({2, {3, 4}});
    arr.push_back({2, {4, 5}});
    arr.push_back({3, {4, 6}});
    arr.push_back({3, {5, 6}});

    sort(arr.begin(), arr.end(), [](piii a, piii b){
        return a.first < b.first; //a ka first should be small than b ka first
    });

    vector<int> par(n, 0);
    vector<int> size(n, 1);
    for(int i = 0; i < n; i++){
        par[i] = i;
    }

    kruskal(arr, n, par, size);

    return 0;
}