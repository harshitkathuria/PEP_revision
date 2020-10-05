#include<iostream>
#include<vector>

using namespace std;

int max_WC(vector<int> arr){

    int height, width, maxVol = 0;
    int i = 0, j = arr.size() - 1;

    while(i <= j){

        if(arr[i] <= arr[j]){
            height = arr[i];
            width = j - i;
            
            maxVol = max(maxVol, height * width);
            i++;
        }
        else{
            height = arr[j];
            width = j - i;

            maxVol = max(maxVol, height * width);
            j--;
        }
    }
    return maxVol;
}

int main(){

    vector<int> arr = {3, 2, 1, 3, 5, 2, 2, 1, 4}; 
    
    cout<<max_WC(arr)<<endl;

    return 0;
}