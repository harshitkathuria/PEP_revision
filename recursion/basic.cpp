#include<iostream>
#include<vector>
#include<climits>

using namespace std;

int factorial(int n){

    if(n == 0)
        return 1;
    
    return n * factorial(n - 1);
}

int power_idiot(int a, int b){

    if(b == 1){
        return a;
    }

    return a * power_idiot(a, b - 1);
}

int power_better(int a, int b){

    if(b == 1){
        return a;
    }

    int recAns = power_better(a, b / 2);
    if((b & 1) != 0)
        return recAns * recAns * a;
    else
        return recAns * recAns;
}

void display(vector<int>& arr, int idx){

    if(idx == arr.size()){
        return;
    }

    cout<<arr[idx]<<" ";

    display(arr, idx + 1);
    // cout<<arr[idx]<<" ";
}

void mirror_idxVal(vector<int>& arr, int idx){

    if(idx == arr.size()){
        return;
    }

    int val = arr[idx];

    mirror_idxVal(arr, idx + 1);

    arr[val] = idx;
}

vector<int> count10(vector<int>& arr, int idx){

    if(idx == arr.size() - 1){
        vector<int> base;
        if(arr[idx] == 10){
            base.push_back(idx);
        }
        return base;
    }

    vector<int> recAns = count10(arr, idx + 1);

    if(arr[idx] == 10){
        recAns.push_back(idx);
    }

    return recAns;
}

int main(){

    int n = 5;
    // vector<int> arr = {2, 3, 4, 0, 5, 6, 1};
    vector<int> arr = {10, 80, 90, -10, 11, 10, 12, 10, 13, 15, 10, 9};

    // cout<<factorial(5)<<endl;
    // cout<<power_idiot(6, 3)<<endl;
    // cout<<power_better(2, 4)<<endl;
    // mirror_idxVal(arr, 0);
    vector<int> ans = count10(arr, 0);
    display(ans, 0);

    return 0;
}