#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main(){

    int t;
    cin>>t;

    while(t-- > 0){
        int n, k;
        cin>>n>>k;
        vector<int> a(n, 0);
        vector<int> b(n, 0);

        for(int i = 0; i < n; i++){
            cin>>a[i];
        }
        for(int i = 0; i < n; i++){
            cin>>b[i];
        }

        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        int j = b.size() - 1;

        for(int i = 0; i < k; i++){
            if(b[j] > a[i]){
                a[i] = b[j];
            }
            j--;
        }
        int sum = 0;
        for(int i = 0; i < n; i++){
            sum += a[i];
        }

        cout<<sum<<endl;
    }

    return 0;
}