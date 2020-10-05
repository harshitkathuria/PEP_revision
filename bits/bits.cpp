#include<iostream>
#include<vector>
#include<cstring>

using namespace std;

int noOfOne_left(int num){
    int mask, count = 0;

    for(int i = 0; i < 32; i++){
        mask = (1 << i);
        if((num & mask) != 0)
            count++;
    }
    return count;
}

int noOfOne_right(int num){
    int mask, count = 0, bit = 0;

    while(num != 0 && bit < 32){
        if((num & 1) != 0)
            count++;
        
        num = (num >> 1);
        bit++;
    }
    return count;
}

int noOfOne_optimized(int num){
    int count = 0;

    while(num != 0){
        num = (num & (num - 1));
        count++;
    }
    return count;
}

int unique_forK(vector<int>& arr, int k){
    vector<int> bits(32, 0);

    for(int ele : arr){
        for(int i = 0; i < 32; i++){
            int mask = (1 << i);
            if((ele & mask) != 0)
                bits[i]++; 
        }
    }

    int ans = 0;
    for(int i = 0; i < 32; i++){
        if((bits[i] % k) != 0){
            ans = (ans | (1 << i));
        }
    }
    return ans;
}

int main(){

    vector<int> arr = {1, 3, 5, 5, 3, 4, 6, 6, 1, 3, 1, 5, 6};

    // cout<<noOfOne_left(32)<<endl;
    // cout<<noOfOne_right(-1)<<endl;
    // cout<<noOfOne_optimized(-2)<<endl;
    cout<<unique_forK(arr, 3)<<endl;

    return 0;
}