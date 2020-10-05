#include<iostream>
#include<vector>

using namespace std;

class Node{
    public: 
        int data = 0;
        Node* left = nullptr;
        Node* right = nullptr;

        int bal = 0;
        int height = 0;
};

Node updateHeightAndBalance(Node* node){
    int lh = -1;
    int rh = -1;

    if(node->left != nullptr){
        lh = node->left->height;
    }

    if(node->right != nullptr){
        rh = node->right->height;
    }

    node->height = max(lh, rh) + 1;
    node->bal = lh - rh;
}

Node* ll(Node* x){
    Node* y = x->left;
    Node* yright = y->right;

    y->right = x;
    x->left = yright;

    updateHeightAndBalance(x);
    updateHeightAndBalance(y);

    return y;
}

Node* rr(Node* x){
    Node* y = x->right;
    Node* yright = y->left;

    y->left = x;
    x->right = yright;

    updateHeightAndBalance(x);
    updateHeightAndBalance(y);

    return y;
}

Node* rotation(Node* node){

    updateHeightAndBalance(node);

    if(node->bal == 2){ //ll, lr
        if(node->left->bal == 1){   //ll
            return ll(node);
        }
        else{   //lr
            node->left = rr(node->left); 
            return ll(node);
        }
    }
    else if(node->bal == -2){   //rr, rl
        if(node->right->bal == -1){ //rr
            return rr(node);
        }
        else{   //rl
            node->right = ll(node->right);
            return rr(node);
        }
    }
}

int main(){

    return 0;
}