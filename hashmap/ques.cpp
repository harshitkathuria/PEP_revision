#include<iostream>
#include<vector>
#include<unordered_map>

using namespace std;

void longestSeries(vector<int> arr){

    unordered_map<int, bool> map;

    for(int ele : arr){
        map[ele] = false;
    }

    for(auto key : map){
        if(map.find(key.first - 1) != map.end()){
            map[key.first] = true;
        }
    }

    int size = -1;
    int number = -1;

    for(auto key : map){
        if(key.second == true){
            
            int smallsize = 1;
            int num = key.first + 1;

            while(map.find(num) != map.end()){
                smallsize++;
                num++;
            }
            
            if(smallsize > size){
                size = smallsize;
                number = key.first;
            }
        }
    }

    for(int i = 0; i < size; i++){
        cout<<number + i<<" ";
    }

}

int main(){

    vector<int> arr = {1, 10, 0, 5, 6, 100, 99, 98, 97, 95, 94, 7, 11, 8, 9, 13};
    longestSeries(arr);

    return 0;
}