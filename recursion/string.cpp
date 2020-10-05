#include<iostream>
#include<vector>

using namespace std;

void removeHi(string str, int idx, string asf){
    
    if(idx == str.length()){
        cout<<asf<<endl;
        return;
    }

    if(idx + 1 < str.length() && str.substr(idx, 2) == "hi"){
        removeHi(str, idx + 2, asf);
    }
    else
        removeHi(str, idx + 1, asf + str[idx] + "");
}

string removeHi(string str){
    
    if(str.length() == 0){
        return "";
    }

    if(str.length() > 1 && str.substr(0, 2) == "hi"){
        return removeHi(str.substr(2));
    }
    else
        return str[0] + removeHi(str.substr(1));
}

string removeHi_HIT(string str){

    if(str.length() == 0){
        return "";
    }

    if(str.length() > 2 && str.substr(0, 3) == "hit"){
        return "hit" + removeHi_HIT(str.substr(3));
    }
    else if(str.length() > 1 && str.substr(0, 2) == "hi"){
        return removeHi_HIT(str.substr(2));
    }
    else
        return str[0] + removeHi_HIT(str.substr(1));
}

string rem_dup(string str){

    if(str.length() == 0){
        return "";
    } 

    if(str.length() > 1 && str[0] == str[1]){
        return rem_dup(str.substr(1));
    }
    else{
        return str[0] + rem_dup(str.substr(1));
    }
}

vector<string> subseq(string str){

    if(str.length() == 0){
        vector<string> base;
        base.push_back("");
        return base;
    }

    vector<string> recAns = subseq(str.substr(1));
    vector<string> myAns(recAns);
    
    for(string s : recAns){
        myAns.push_back(str[0] + s);
    }

    return myAns;
}

vector<string> permutation(string str){

    if(str.length() == 0){
        vector<string> base;
        base.push_back("");
        return base;
    }

    vector<string> recAns = permutation(str.substr(1));
    vector<string> myAns;

    for(string s : recAns){
        for(int i = 0; i <= s.length(); i++){
            string new_str = s.substr(0, i) + str[0] + s.substr(i, s.length() - i);
            myAns.push_back(new_str);        
        }
    }

    return myAns;
}

vector<string> keypad = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz", "/#", "$^!"};
vector<string> encoder = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz", "/#", "$^!", "*()", "%@-"};

vector<string> keypad_comb(string str){

    if(str.length() == 0){
        vector<string> base;
        base.push_back("");
        return base;
    }
    
    vector<string> recAns = keypad_comb(str.substr(1));
    vector<string> myAns;

    for(string s : recAns){
        int wordCode = str[0] - '0';
        for(int i = 0; i < keypad[wordCode].length(); i++){
            myAns.push_back(keypad[wordCode][i] + s);
        }
    }
    return myAns;
}

vector<string> encoding(string str){
    
    if(str.length() == 0){
        vector<string> base;
        base.push_back("");
        return base;
    }

    vector<string> myAns;

    if(str.length() > 1 && str[0] != '0'){ 
        int num = (str[0] - '0') * 10 + (str[1] - '0');
        if(num < 12){
            vector<string> twoChar = encoding(str.substr(2));

            for(string s : twoChar){
                for(int i = 0; i < encoder[num].length(); i++)
                    myAns.push_back(encoder[num][i] + s);
            }
        }
    }

    vector<string> oneChar = encoding(str.substr(1));
    for(string s : oneChar){
        for(int i = 0; i < encoder[str[0] - '0'].length(); i++)
            myAns.push_back(encoder[str[0] - '0'][i] + s);
    }

    return myAns;
}

int main(){
    
    // removeHi("ihiihihihihh", 0, "");
    // cout<<removeHi("ihiihihihihh")<<endl;
    // cout<<removeHi_HIT("ihihitiihit")<<endl;
    // cout<<rem_dup("aaabccdefghha")<<endl;

    // for(string s : subseq("abcd")){
    //     cout<<s<<" ";
    // }

    // for(string s : permutation("abc")){
    //     cout<<s<<" ";
    // }

    // for(string s : keypad_comb("342")){
    //     cout<<s<<" ";
    // }

    for(string s : encoding("1024")){
        cout<<s<<" ";
    }

    return 0;
}