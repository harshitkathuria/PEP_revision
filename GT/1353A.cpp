#include<iostream>
#include<vector>

using namespace std;

int main(){

    int t;
    cin>>t;

    while(t-- > 0){
        int n, m;
        cin>>n>>m;

        if(n == 1){
            cout<<0<<endl;
        }
        else if(n == 2){
            cout<<m<<endl;
        }
        else{
            cout<<m * 2<<endl;
        }
    }

    return 0;
}