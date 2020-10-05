#include<iostream>
#include<vector>

#define vb vector<bool>
#define vi vector<int>

using namespace std;

int nQueens_bool(int r, vb& col, vb& diag, vb& anti_diag, int tnq, string asf){

    if(r == col.size() || tnq == 0){
        if(tnq == 0){
            cout<<asf<<endl;
            return 1;
        }
        return 0;
    }

    int count = 0;

    for(int c = 0; c < col.size(); c++){
        if(!col[c] && !diag[r + c] && !anti_diag[c - r + col.size() - 1]){
            
            col[c] = true;
            diag[r + c] = true;
            anti_diag[c -r + col.size() - 1] = true;
            
            count += nQueens_bool(r + 1, col, diag, anti_diag, tnq - 1, asf + "q" + to_string(r + 1) + ": (" + to_string(r) + " " + to_string(c) + ") ");
            
            col[c] = false;
            diag[r + c] = false;
            anti_diag[c -r + col.size() - 1] = false;
        }
    }

    return count;
}

int nQueens_bits(int n, int r, int col, int diag, int anti_diag, int tnq, string asf){

    if(r == n || tnq == 0){
        if(tnq == 0){
            cout<<asf<<endl;
            return 1;
        }
        return 0;
    }

    int count = 0;

    for(int c = 0; c < n; c++){
        int x = (1 << c);
        int y = (1 << (r + c));
        int z = (1 << (c - r + n - 1));

        if(!(col & x) && !(diag & y) && !(anti_diag & z)){

            col |= x;
            diag |= y;
            anti_diag |= z;

            count += nQueens_bits(n, r + 1, col, diag, anti_diag, tnq - 1, asf + "q" + to_string(r + 1) + ": (" + to_string(r) + " " + to_string(c) + ") ");

            col &= (~x);
            diag &= (~y);
            anti_diag &= (~z);
        }
    }

    return count;
}

int main(){

    int r = 4, c = 4;

    // vb col(c, false);
    // vb diag(r + c - 1, false);
    // vb anti_diag(r + c - 1, false);

    int col = 0, diag = 0, anti_diag = 0;

    // cout<<nQueens_bool(0, col, diag, anti_diag, 4, "")<<endl;
    cout<<nQueens_bits(4, 0, col, diag, anti_diag, 4, "")<<endl;

    return 0;
}