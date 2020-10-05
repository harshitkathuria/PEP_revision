#include<iostream>
#include<vector>

using namespace std;

//without subseq..............................................................

int permu_infi(vector<int>& arr, int tar, string asf){

    if(tar == 0){
        cout<<asf<<endl;
        return 1;
    }

    int count = 0;
    for(int i = 0; i < arr.size(); i++){
        if(tar - arr[i] >= 0){
            count += permu_infi(arr, tar - arr[i], asf + to_string(arr[i]));
        }
    }
    return count;
}

int permu_noRep(vector<int>& arr, int tar, vector<bool>& vis, string asf){

    if(tar == 0){
        cout<<asf<<endl;
        return 1;
    }
    
    int count = 0;
    for(int i = 0; i < arr.size(); i++){
        if(tar - arr[i] >= 0 && !vis[i]){
            vis[i] = true;
            count += permu_noRep(arr, tar - arr[i], vis, asf + to_string(arr[i]));
            vis[i] = false;
        }
    }
    return count;
}

int combi_infi(vector<int>& arr, int lidx, int tar, string asf){

    if(tar == 0){
        cout<<asf<<endl;
        return 1;
    }

    int count = 0;
    for(int i = lidx; i < arr.size(); i++){
        if(tar - arr[i] >= 0){
            count += combi_infi(arr, i, tar - arr[i], asf + to_string(arr[i]));
        }
    }
    return count;
}

int comb_noRep(vector<int>& arr, int lidx, int tar, string asf){

    if(tar == 0){
        cout<<asf<<endl;
        return 1;
    }

    int count = 0;
    for(int i = lidx ; i < arr.size(); i++){
        if(tar - arr[i] >= 0){
            count += comb_noRep(arr, i + 1, tar - arr[i], asf + to_string(arr[i]));
        }
    }
    return count;
}

//subseq..............................................................

int permu_infi_S(vector<int>& arr, int idx, int tar, string asf){

    if(tar == 0 || idx == arr.size()){
        if(tar == 0){
            cout<<asf<<endl;
            return 1;
        }
        else
            return 0;
    }

    int count = 0;
    if(tar - arr[idx] >= 0){
        count += permu_infi_S(arr, 0, tar - arr[idx], asf + to_string(arr[idx]));
    }
    count += permu_infi_S(arr, idx + 1, tar, asf);
    return count;
}

int combi_infi_S(vector<int>& arr, int idx, int tar, string asf){

    if(tar == 0 || idx == arr.size()){
        if(tar == 0){
            cout<<asf<<endl;
            return 1;
        }
        else
            return 0;
    }

    int count = 0;
    if(tar - arr[idx] >= 0){
        count += combi_infi_S(arr, idx, tar - arr[idx], asf + to_string(arr[idx]));
    }
    count += combi_infi_S(arr, idx + 1, tar, asf);

    return count;
}

int permu_noRep_S(vector<int>& arr, int idx, int tar, vector<bool>& vis, string asf){

    if(tar == 0 || idx == arr.size()){
        if(tar == 0){
            cout<<asf<<endl;
            return 1;
        }
        else
            return 0;
    }

    int count = 0;
    if(tar - arr[idx] >= 0 && !vis[idx]){
        vis[idx] = true;
        count += permu_noRep_S(arr, 0, tar - arr[idx], vis, asf + to_string(arr[idx]));
        vis[idx] = false;
    }
    count += permu_noRep_S(arr, idx + 1, tar, vis, asf);
    return count;
}

int combi_noRep_S(vector<int>& arr, int idx, int tar, string asf){

    if(tar == 0 || idx == arr.size()){
        if(tar == 0){
            cout<<asf<<endl;
            return 1;
        }
        else
            return 0;
    }

    int count = 0;
    if(tar - arr[idx] >= 0){
        count += combi_infi_S(arr, idx + 1, tar - arr[idx], asf +  to_string(arr[idx]));
    }
    count += combi_infi_S(arr, idx + 1, tar, asf);

    return count;
}

int main(){

    vector<int> arr = {2, 3, 5, 7};
    vector<bool> vis(arr.size(), false);
    // cout<<permu_infi(arr, 10, "")<<endl;
    // cout<<permu_noRep(arr, 10, vis, "")<<endl;
    // cout<<combi_infi(arr, 0, 10, "")<<endl;
    // cout<<comb_noRep(arr, 0, 10, "")<<endl;

    // cout<<permu_infi_S(arr, 0, 10, "")<<endl;
    // cout<<combi_infi_S(arr, 0, 10, "")<<endl;
    // cout<<combi_noRep_S(arr, 0, 10, "")<<endl;
    cout<<permu_noRep_S(arr, 0, 10, vis, "")<<endl;

    return 0;
}