#include<iostream>
#include<vector>

#define vi vector<int>
#define vvi vector<vi>

using namespace std;

vi row(9, 0);
vi col(9, 0);
vvi mat(3, vi(3, 0));

void display(vvi& board){
    
    for(vi arr : board){
        for(int ele : arr){
            cout<<ele<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

int sudoku_bit(vvi& board, vi& calls, int idx){

    if(idx == calls.size()){
        display(board);
        return 1;
    }

    int x = calls[idx] / 9;
    int y = calls[idx] % 9;

    int count = 0;
    for(int num = 1; num <= 9; num++){

        int mask = (1 << num);
        if(!(row[x] & mask) && !(col[y] & mask) && !(mat[x / 3][y / 3] & mask)){

            board[x][y] = num;
            row[x] ^= mask;
            col[y] ^= mask;
            mat[x / 3][y / 3] ^= mask;

            count += sudoku_bit(board, calls, idx + 1);

            board[x][y] = 0;
            row[x] ^= mask;
            col[y] ^= mask;
            mat[x / 3][y / 3] ^= mask;
        }
    }
    return count;
}

void sudoku(){

    vvi board = {{7, 0, 9, 0, 1, 0, 0, 5, 0},

                 {8, 0, 0, 5, 3, 9, 0, 0, 4},

                 {0, 0, 5, 7, 4, 0, 2, 0, 0},

                 {4, 0, 0, 0, 0, 3, 0, 0, 5},

                 {0, 0, 0, 9, 0, 1, 0, 0, 0},

                 {6, 0, 0, 8, 0, 0, 0, 0, 2},

                 {0, 0, 4, 0, 6, 0, 8, 0, 0},

                 {9, 0, 0, 1, 8, 7, 0, 0, 3},

                 {0, 1, 0, 0, 0, 0, 5, 0, 6}};
    vi calls;

    for(int i = 0; i < board.size(); i++){
        for(int j = 0; j < board[0].size(); j++){
            if(board[i][j] == 0){
                calls.push_back(i * 9 + j);
            }
            else
            {
                int mask = (1 << board[i][j]);
                row[i] |= mask;
                col[j] |= mask;
                mat[i / 3][j / 3] |= mask;
            }
            
        }
    }

    cout<<sudoku_bit(board, calls, 0)<<endl;
}

int main(){

    sudoku();

    return 0;
}