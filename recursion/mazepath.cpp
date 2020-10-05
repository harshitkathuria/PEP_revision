#include<iostream>
#include<vector>

using namespace std;

vector<string> mazePath_HVD(int sr, int sc, int er, int ec){

    if(sc == ec && sr == er){
        vector<string> base;
        base.push_back("");
        return base;
    }

    vector<string> myAns;

    if(sc + 1 <= ec){
        vector<string> hor = mazePath_HVD(sr, sc + 1, er, ec);
        for(string s : hor)
            myAns.push_back("h" + s);
    }

    if(sr + 1 <= er){
        vector<string> ver = mazePath_HVD(sr + 1, sc, er, ec);
        for(string s : ver)
            myAns.push_back("v" + s);
    }

    if(sr + 1 <= er && sc + 1 <= ec){
        vector<string> diag = mazePath_HVD(sr + 1, sc + 1, er, ec);
        for(string s : diag)
            myAns.push_back("d" + s);
    }

    return myAns;
}

vector<string> mazePath_jump(int sr, int sc, int er, int ec){

    if(sr == er && sc == ec){
        vector<string> base;
        base.push_back("");
        return base;
    }

    vector<string> myAns;

    for(int jump = 1; sc + jump <= ec; jump++){
        vector<string> hor = mazePath_jump(sr, sc + jump, er, ec);
        for(string s : hor){
            myAns.push_back("h" + to_string(jump) + s);
        }
    }

    for(int jump = 1; sr + jump <= er; jump++){
        vector<string> ver = mazePath_jump(sr + jump, sc, er, ec);
        for(string s : ver){
            myAns.push_back("v" + to_string(jump) + s);
        }
    }

    for(int jump = 1; sr + jump <= er && sc + jump <= ec; jump++){
        vector<string> diag = mazePath_jump(sr + jump, sc + jump, er, ec);
        for(string s : diag){
            myAns.push_back("d" + to_string(jump) + s);
        }
    }

    return myAns;
}

int main(){

    // for(string s : mazePath_HVD(0, 0, 2, 2)){
    //     cout<<s<<" ";
    // }
    for(string s : mazePath_jump(0, 0, 2, 2)){
        cout<<s<<" ";
    }

    cout<<endl;

    return 0;
}