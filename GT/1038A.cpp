#include<iostream>
#include<vector>

using namespace std;

int main(){

    int n, k;
    cin>>n>>k;
    
    string s;
    cin>>s;

    string str;
    for(int i = 0; i < k; i++){
        str += 'A' + i;
    }
    cout<<str<<endl;
    int maxLength = 0, length = 0, z = 0;

    for(int i = 0; i < s.length(); i++){
        for(int j = z; j < str.length(); j++){
            if(s[i] == str[j]){
                cout<<i<<":"<<z<<" ";
                z++;
                length++;
                if(length % k == 0){
                    cout<<"hit"<<endl;
                    z = 0;
                }
                break;
            }
        }
    }
    cout<<length<<endl;
    if(length < k){
        cout<<0;
    }
    else{
        length = length - (length % k);
        cout<<length;
    }
    return 0;
}