#include<iostream>
#include<vector>
#include<climits>

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

int idx = 0;

Node* createTree(vector<int>& arr){

    if(idx == arr.size() || arr[idx] == -1){
        idx++;
        return nullptr;
    }

    Node* node = new Node(arr[idx]);
    // cout<<idx<<" ";
    idx++;
    node->left = createTree(arr);
    node->right = createTree(arr);

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

int maximum(Node* root){

    if(root == nullptr){
        return INT_MIN;
    }

    int left_max = maximum(root->left);
    int right_max = maximum(root->right);

    return max(root->data, max(left_max, right_max));
}

int minimum(Node* root){
    
    if(root == nullptr){
        return INT_MAX;
    }

    int left_min = minimum(root->left);
    int right_min = minimum(root->right);

    return min(root->data, min(left_min, right_min));
}

int height(Node* root){
    
    if(root == nullptr){
        return -1;
    }

    int left_height = height(root->left);
    int right_height = height(root->right);

    return max(left_height, right_height) + 1;
}

bool find(Node* root, int data){

    if(root == nullptr){
        return false;
    }

    if(root->data == data){
        return true;
    }

    return find(root->left, data) || find(root->right, data);
}

vector<Node*> rootToNodePath(Node* node, int data){

    if(node == nullptr){
        return vector<Node*>();
    }

    if(node->data == data){
        vector<Node*> arr;
        arr.push_back(node);
        return arr;
    }

    vector<Node*> leftarr = rootToNodePath(node->left, data);
    if(leftarr.size() != 0){
        leftarr.push_back(node);
        return leftarr;
    }

    vector<Node*> rightarr = rootToNodePath(node->right, data);
    if(rightarr.size() != 0){
        rightarr.push_back(node);
        return rightarr;
    }

    return vector<Node*>();
}

int LCA(Node* root, int data1, int data2){   //with RTNP

    vector<Node*> list1 = rootToNodePath(root, data1);
    vector<Node*> list2 = rootToNodePath(root, data2);

    int i = list1.size() - 1, j = list2.size() - 1;

    while(i > 0 && j > 0){
        if(list1[i] != list2[j])
            break;
        i--;
        j--;
    }
    return list1[++i]->data;
}

void kDown(Node* node, Node* pnode, int k){

    if(node == nullptr || node == pnode || k < 0){
        return;
    }

    if(k == 0){
        cout<<node->data<<" ";
        return;
    }

    kDown(node->left, pnode, k - 1);
    kDown(node->right, pnode, k - 1);
}

void kAway_01(Node* root, int data, int k){     //with RTNP

    if(k < 0){
        return;
    }

    vector<Node*> list = rootToNodePath(root, data);
    Node* pnode = nullptr;

    for(int i = 0; i < list.size(); i++){
        kDown(list[i], pnode, k - i);
        pnode = list[i];
    }
}

int kAway_02(Node* node, int data, int k){     //withour RTNP

    if(node == nullptr || k < 0){
        return 0;
    }

    if(node->data == data){
        kDown(node, nullptr, k);
        return 1;
    }

    int left = kAway_02(node->left, data, k);
    
    if(left != 0){
        kDown(node, node->left, k - left);
        return left + 1;
    }

    int right = kAway_02(node->right, data, k);

    if(right != 0){
        kDown(node, node->right, k - right);
        return right + 1;
    }

    return 0;
}

int diameter_01(Node* node){
    
    if(node == nullptr){
        return 0;
    }

    int ld = diameter_01(node->left);
    int rd = diameter_01(node->right);

    int lh = height(node->left);
    int rh = height(node->right);

    return max(lh + rh + 2, max(ld, rd));
}

vector<int> diameter_02(Node* node){
    if(node == nullptr){
        vector<int> base(2, 0);
        base[0] = 0;    //diameter
        base[1] = -1;   //height
        return base;
    }

    vector<int> left = diameter_02(node->left);
    vector<int> right = diameter_02(node->right);

    vector<int> ans(2, 0);
    ans[0] = max(left[1] + right[1] + 2, max(left[0], right[0]));
    ans[1] = max(left[1], right[1]) + 1;

    return ans;
}

int leafMaxSum = INT_MIN;

int maxLeafToLeafSum(Node* root){
    if(root == nullptr){
        return 0;
    }

    if(root->left == nullptr && root->right == nullptr){
        return root->data;
    }

    int leftmaxLeafSum = maxLeafToLeafSum(root->left);
    int rightmaxLeafSum = maxLeafToLeafSum(root->right);

    if(root->left != nullptr && root->right != nullptr){
        if(leftmaxLeafSum + rightmaxLeafSum + root->data > leafMaxSum){
            leafMaxSum = leftmaxLeafSum + rightmaxLeafSum + root->data;
        }
    }

    return max(leftmaxLeafSum, rightmaxLeafSum) + root->data;
}

int nodeMaxsum = INT_MIN;

int nodeToNodeSum(Node* root){
    if(root == nullptr){
        return 0;
    }

    int leftmaxSum = nodeToNodeSum(root->left);
    int rightmaxSum = nodeToNodeSum(root->right);
    int maxBranch = max(leftmaxSum, rightmaxSum);

    nodeMaxsum = max(nodeMaxsum, max(leftmaxSum + rightmaxSum + root->data, max(maxBranch + root->data, root->data)));

    return max(maxBranch + root->data, root->data);
}

int main(){

    // vector<int> arr = {10, 20, 30, 40, -1, -1, 50, -1, -1, 60, -1, 70, -1, -1, 80, 90, 100, 120, -1, -1, 130, -1, -1, 110, -1, -1, 140, 150, -1, -1 , -1};
    vector<int> arr = {10, 20, 40, -1, -1, 50, 60, -1, -1, 70, -1, -1, 30, 80, -1, -1, 90, 100, -1, -1, 120, -1, -1};
    Node* root = createTree(arr);

    display(root);
    cout<<endl;

    // cout<<"Maximum: "<<maximum(root)<<endl;
    // cout<<"Minimum: "<<minimum(root)<<endl;
    // cout<<"Height: "<<height(root)<<endl;
    // cout<<(boolalpha)<<find(root, 140)<<endl;

    // for(Node* node : rootToNodePath(root, 140)){
    //     cout<<node->data<<" ";
    // }

    // cout<<"LCA: "<<LCA_01(root, 100, 100)<<endl;

    // kDown(root, nullptr, 3);
    // kAway_01(root, 90, 2);
    // kAway_02(root, 90, 2);

    // cout<<"Diameter: "<<diameter_01(root)<<endl;
    // cout<<"Diameter: "<<diameter_02(root)[0]<<endl;

    // maxLeafToLeafSum(root);
    // cout<<"Maximum leaf to leaf sum: "<<leafMaxSum<<endl;
    nodeToNodeSum(root);
    cout<<"Maximum node to node sum: "<<nodeMaxsum<<endl;

    return 0;
}