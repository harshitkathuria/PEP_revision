#include<iostream>
#include<vector>
#include<climits>
#include<queue>

using namespace std;

class Node{
    public:
        int data = 0;
        Node* left = nullptr;
        Node* right = nullptr;

        Node(int data){
            this->data = data;
        }

        Node(int data, Node* left, Node* right){
            this->data = data;
            this->left = left;
            this->right = right;
        }

};

Node* createBST(vector<int>& arr, int i, int j){

    if(i > j){
        return nullptr;
    }

    int mid = (i + j) / 2;
    Node* node = new Node(arr[mid]);
    
    node->left = createBST(arr, i, mid - 1);
    node->right = createBST(arr, mid + 1, j);

    return node;
}

void display(Node* node){

    if(node == nullptr){
        return;
    }

    if(node->left == nullptr)
        cout<<".";
    else
        cout<<node->left->data;

    cout<<" -> "<<node->data<<" <- ";

    if(node->right == nullptr)
        cout<<".";
    else
        cout<<node->right->data;
    cout<<endl;

    display(node->left);
    display(node->right);
}

bool find_01(Node* root, int data){
    if(root == nullptr){
        return false;
    }

    if(root->data == data){
        return true;
    }
    else if(root->data > data){
        return find_01(root->left, data);
    }
    else{
        return find_01(root->right, data);
    }
}

bool find_02(Node* root, int data){

    while(root != nullptr){
        
        if(root->data == data){
            return true;
        }
        else if(root->data > data){
            root = root->left;
        }
        else{
            root = root->right;
        }
    }
    return false;
}

Node* addNode(Node* root, int data){

    if(root == nullptr){
        return new Node(data); 
    }

    if(root->data > data){
        root->left = addNode(root->left, data);
    }
    else{
        root->right = addNode(root->right, data);
    }
    
    return root;
}

int minInBST(Node* root){
    
    if(root == nullptr){
        return INT_MAX;
    }

    Node* rnode = root;

    while(rnode->left != nullptr){
        rnode = rnode->left;
    }
    return rnode->data;
}

int maxInTree(Node* root){

    if(root == nullptr){
        return INT_MIN;
    }

    Node* rnode = root;

    while(rnode->right != nullptr){
        rnode = rnode->right;
    }
    return rnode->data;
}

Node* removeNode(Node* root, int data){

    if(root == nullptr){
        return nullptr;
    }

    if(root->data == data){
        
        if(root->left == nullptr || root->right == nullptr){
            return (root->left == nullptr)? root->right : root->left;
        }
        else{
            int max_val = maxInTree(root->left);
            root->data = max_val;
            removeNode(root->left, max_val);
        }
    }
    else if(root->data > data){
        root->left = removeNode(root->left, data);
    }
    else{
        root->right = removeNode(root->right, data);
    }
    return root;
}

void predSuccforBST(Node* root, int data){
    
    Node* pred = nullptr;
    Node* succ = nullptr;

    while(root != nullptr){
        
        if(root->data == data){
            
            if(root->left != nullptr){
                pred = root->left;
                while(pred->right != nullptr){
                    pred = pred->right;
                }
            }

            if(root->right != nullptr){
                succ = root->right;
                while(succ->left != nullptr){
                    succ = succ->left;
                }
            }

            cout<<"Pred: "<<((pred != nullptr)? pred->data : -1)<<endl;
            cout<<"Succ: "<<((succ != nullptr)? succ->data : -1)<<endl;

            return;
        }
        else if(root->data > data){
            succ = root;
            root = root->left;
        }
        else{
            pred = root;
            root = root->right;
        }
    }
}

void morrisInOrder(Node* root){

    Node* curr = root;

    while(curr != nullptr){

        if(curr->left == nullptr){
            cout<<curr->data<<" ";
            curr = curr->right;
        }
        else{
            Node* pred = curr->left;
            while(pred->right != nullptr && pred->right != curr){
                pred = pred->right;
            }

            if(pred->right == nullptr){     //making thread
                // cout<<curr->data<<" ";   //for pre order
                pred->right = curr;
                curr = curr->left;
            }
            else{               
                pred->right = nullptr;      //deleting thread
                cout<<curr->data<<" ";
                curr = curr->right;
            }
        }
    }
}

int leftMost = 0;
int rightMost = 0;

void width(Node* root, int level){

    if(root == nullptr){
        return;
    }
    
    width(root->left, level - 1);
    if(leftMost > level){
        leftMost = level;
    }

    width(root->right, level + 1);
    if(rightMost < level){
        rightMost = level;
    }
}

vector<int> verticalOrder(Node* root){

    width(root, 0);
    // cout<<leftMost<<" "<<rightMost<<endl;

    vector<vector<int>> order(rightMost - leftMost + 1, vector<int>());

    queue<pair<Node*, int>> que;
    que.push({root, -leftMost});

    while(que.size() > 0){
        pair<Node*, int> rnode = que.front();
        que.pop();

        order[rnode.second].push_back(rnode.first->data);

        if(rnode.first->left != nullptr)
            que.push({rnode.first->left, rnode.second - 1});
        if(rnode.first->right != nullptr)
            que.push({rnode.first->right, rnode.second + 1});
    }

    int i = 0;
    for(vector<int> arr : order){
        cout<<i<<" -> ";
        for(int ele : arr){
            cout<<ele<<" ";
        }
        i++;
        cout<<endl;
    }
}

int main(){

    vector<int> arr(10, 0);
    for(int i = 0; i < 10; i++){
        arr[i] = (i + 1) * 10;
    }

    Node* root = createBST(arr, 0, arr.size() - 1);
    // display(root);

    // cout<<(boolalpha)<<find_01(root, 80);
    // cout<<(boolalpha)<<find_02(root, 80);
    
    addNode(root, 55);
    addNode(root, 85);
    // display(root);

    // cout<<"Minimum: "<<minInBST(root)<<endl;
    // cout<<"Maximum: "<<maxInTree(root)<<endl;

    // removeNode(root, 80);
    // display(root);

    // predSuccforBST(root, 55);

    // morrisInOrder(root);

    verticalOrder(root);

    return 0;
}