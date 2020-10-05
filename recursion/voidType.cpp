#include<iostream>
#include<vector>

using namespace std;

void subseq(string str, string asf){
    
    if(str.length() == 0){
        cout<<asf<<endl;
        return;
    }

    subseq(str.substr(1), asf);
    subseq(str.substr(1), asf + str[0]);
}

void permutation(string str, string asf){

    if(str.length() == 0){
        cout<<asf<<endl;
        return;
    }

    for(int i = 0; i < str.length(); i++){
        string new_str = str.substr(0, i) + str.substr(i + 1, str.length() - i);
        permutation(new_str, asf + str[i]);
    }
}

vector<string> encoder = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz", "/#", "$^!", "*()", "%@-"};

void keypad(string str, string asf){

    if(str.length() == 0){
        cout<<asf<<endl;
        return;
    }

    int wordCode = str[0] - '0';
    for(int i = 0; i < encoder[wordCode].length(); i++){
        keypad(str.substr(1), asf + encoder[wordCode][i]);
    }
}

int main(){

    // subseq("abc", "");
    // permutation("abc", "");
    keypad("456", "");

    return 0;
}