#include<iostream>
#include<vector>
#include<stack>
#include<climits>

using namespace std;

class Node{
    public:
        int data;
        vector<Node*> children;

        Node(int data){
            this->data = data;
        }
};

int idx = 0;

Node* createTree(vector<int>& arr){

    stack<Node*> st;
    for(int i = 0; i < arr.size() - 1; i++){
        if(arr[i] != -1){
            Node* node = new Node(arr[i]);
            st.push(node);
        }
        else{
            Node* child = st.top();
            st.pop();
            st.top()->children.push_back(child);
        }
    }
    return st.top();
}

void display(Node* root){
    
    if(root == nullptr){
        return;
    }

    cout<<root->data<<" -> ";
    for(int i = 0; i < root->children.size(); i++){
        cout<<root->children[i]->data<<" ";
    }
    cout<<endl;

    for(int i = 0; i < root->children.size(); i++){
        display(root->children[i]);
    }
}

int height(Node* root){
    
    if(root == nullptr){
        return -1;
    }   

    int ht = -1;

    for(Node* child : root->children){
        ht = max(ht, height(child));
    }
    
    return ht + 1;
}

int maximum(Node* root){
    if(root == nullptr){
        return -1;
    }

    int maxVal = root->data;
    for(Node* child : root->children){
        maxVal = max(maxVal, maximum(child));
    }

    return maxVal;
}

Node* getTail(Node* node){

    if(node->children.size() == 0){
        return node;
    }

    return getTail(node->children[0]);
}

Node* linearize(Node* root){

    for(Node* node: root->children){
        linearize(node);
    }

    for(int i = root->children.size() - 2; i >= 0; i--){
        Node* last = root->children[i + 1];
        Node* secondLastTail = getTail(root->children[i]);

        secondLastTail->children.push_back(last);
        root->children.pop_back();
    }

    return root;
}

Node* linearize_eff(Node* root){

    if(root->children.size() == 0){
        return root;
    }    

    Node* myTail = linearize_eff(root->children[root->children.size() - 1]);
       
    for(int i = root->children.size() - 2; i >= 0; i--){

        Node* skltail = linearize_eff(root->children[i]);
        skltail->children.push_back(root->children[i + 1]);

        root->children.pop_back();
    }
    return myTail;
}

Node* removeLeaf(Node* root){
    if(root == nullptr){
        return nullptr;
    }

    vector<Node*> update;
    for(int i = 0; i < root->children.size(); i++){
        if(root->children[i]->children.size() != 0){
            update.push_back(root->children[i]);
        }
    }
    root->children = update;

    for(int i = 0; i < root->children.size(); i++){
        removeLeaf(root->children[i]);
    }
    return root;
}

bool isSymmetric(Node* root1, Node* root2){
    
    if(root1->children.size() != root2->children.size()){
        return false;
    }

    for(int i = 0; i < root1->children.size(); i++){
        if(!isSymmetric(root1->children[i], root2->children[i])){
            return false;
        }
    }
    return false;
}

int main(){

    vector<int> arr = {10, 20, 50, -1, 60, -1, -1, 30, 70, -1, 80, 100, -1, 110, -1, -1, 90, -1, -1, 40, -1, -1};

    Node* root = createTree(arr);
    display(root);
    cout<<endl;

    // cout<<"Height: "<<height(root)<<endl;
    // cout<<"Maximum: "<<maximum(root)<<endl;

    // root = linearize(root);
    // linearize_eff(root);

    root = removeLeaf(root);
    display(root);

    return 0;
}