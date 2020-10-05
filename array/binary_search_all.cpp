#include<iostream>
#include<vector>

using namespace std;

void binarySearch(vector<int>& arr, int data, int i, int j){

    // int i = 0, j = arr.size() - 1;
    while(i <= j){
        int mid = (i + j) / 2;

        if(arr[mid] == data){
            cout<<"FOUND : "<<mid<<endl;
            return;
        }
        else if(arr[mid] < data){
            i = mid + 1;
        }
        else{
            j = mid - 1;
        }
    }
    cout<<"NOT FOUND"<<endl;
}

int BS_UB(vector<int>& arr, int data){

    int lb = 0, ub = arr.size() - 1;

    while(lb <= ub){
        int mid = (lb + ub) / 2;

        if(arr[mid] == data){
            if(mid + 1 < arr.size() && arr[mid + 1] == arr[mid]){
                lb = mid + 1;
            }
            else
                return mid;
        }
        else if(arr[mid] < data){
            lb = mid + 1;
        }
        else
            ub = mid - 1;
    }
    return -1;
}

int BS_closest(vector<int>& arr, int data){

    int lb = 0, ub = arr.size() - 1;

    while(lb <= ub){
        int mid = (lb + ub) / 2;

        if(arr[mid] == data){
            return mid;
        }
        else if(arr[mid] < data){
            lb = mid + 1;
        }
        else{
            ub = mid - 1;
        }
    }

    return ((data - arr[ub]) <= (arr[lb] - data))? arr[ub] : arr[lb];
}

int fulctuatingPoint(vector<int>& arr){

    int i = 0, j = arr.size() - 1;

    if(i == j){
        return arr[0];
    }

    if(arr[j] > arr[j - 1]){
        return arr[j];
    }
    else if(arr[i] > arr[i + 1]){
        return arr[i];
    }

    while(i <= j){
        int mid = (i + j) / 2;

        if(arr[mid] > arr[mid - 1] && arr[mid] > arr[mid + 1]){
            return arr[mid];
        }
        else if(arr[mid] < arr[mid - 1]){
            j = mid - 1;
        }
        else{
            i = mid + 1;
        }
    }
}

int main(){

    // vector<int> arr = {-2, -2, -2, -1, 0, 2, 2, 2, 2, 4, 4, 5, 6, 6, 6, 8};
        //              0, 1,  2,  3,  4, 5, 6, 7, 8, 9, 10,11,12,13,14,15

    vector<int> arr = {50};

    // binarySearch(arr, 2, 0, arr.size() - 1);
    // cout<<BS_UB(arr, 6)<<endl;
    // cout<<BS_closest(arr, 3)<<endl;
    cout<<fulctuatingPoint(arr)<<endl;

    return 0;
}