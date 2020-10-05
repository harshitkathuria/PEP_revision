#include<iostream>
#include<vector>

using namespace std;

vector<vector<int>> dir = {{0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};
vector<string> dir_name = {"R", "4", "D", "3", "L", "2", "U", "1"};

bool isSafeToPlace(int x, int y, int er, int ec, vector<vector<bool>>& board){

    if(x > er || y > er || x < 0 || y < 0 || board[x][y])
        return false;
    
    return true;
}

int floodfill(int sr, int sc, int er, int ec, vector<vector<bool>>& board, string asf){

    if(sr == er && sc == ec){
        cout<<asf<<endl;
        return 1;
    }

    int count = 0;
    board[sr][sc] = true;
    for(int i = 0; i < 8; i++){
        
        int x = sr + dir[i][0];
        int y = sc + dir[i][1];
        
        if(isSafeToPlace(x, y, er, ec, board))
            count += floodfill(x, y, er, ec, board, dir_name[i] + asf);
    }
    board[sr][sc] = false;
    return count;
}

int main(){

    vector<vector<bool>> board(3, vector<bool>(3, false));
    cout<<floodfill(0, 0, 2, 2, board, "")<<endl;

    return 0;
}