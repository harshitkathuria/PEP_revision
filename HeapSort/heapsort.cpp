#include <iostream>
#include <vector>

using namespace std;

int compareTo(vector<int>& arr, int ci, int pi, bool isMax)
{
    if(isMax){
        return arr[ci] - arr[pi];
    }
    else{
        return arr[pi] - arr[ci];
    }
}

void downheapify(vector<int>& arr, int pi, int lidx, bool isMax)
{
    int lci = (2 * pi) + 1;
    int rci = (2 * pi) + 2;
    int maxi = pi;

    if(lci <= lidx && compareTo(arr, lci, maxi, isMax) > 0){
        maxi = lci;
    }

    if(rci <= lidx && compareTo(arr, rci, maxi, isMax) > 0){
        maxi = rci;
    }

    if(maxi != pi){
        swap(arr[maxi], arr[pi]);
        downheapify(arr, maxi, lidx, isMax);
    }
}

void heapsort()
{
    vector<int> arr = {10, 20, 30, -2, -3, -4, 5, 6, 7, 8, 9, 22, 11, 13};
    bool isMax = true;

    for(int i = arr.size() - 1; i >= 0; i--)
    {
        downheapify(arr, i, arr.size() - 1, isMax);
    }

    for (int i = 0; i < arr.size(); i++)
    {
        swap(arr[0], arr[arr.size() - i - 1]);
        downheapify(arr, 0, arr.size() - i - 2, isMax);
    }

    cout<<endl;
    for(int i = 0; i < arr.size(); i++){
        cout<<arr[i]<<" ";
    }
}

int main()
{
    heapsort();

    return 0;
}