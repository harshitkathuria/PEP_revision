#include<iostream>
#include<vector>
#include<unordered_map>
#include<queue>

using namespace std;

unordered_map<string, string> encode;
unordered_map<string, string> decode;

class Node{

    public:

        string data = "";
        int freq = 0;
        Node* left = nullptr;
        Node* right = nullptr;

        Node(string data, int freq, Node* left, Node* right){
            this->data = data;
            this->freq = freq;
            this->left = left;
            this->right = right;
        }

        bool operator < (const Node& o)const{
            return this->freq > o.freq;
        }
};

class huffman{

    private:
        void huffmanTree(string str){
            
            priority_queue<Node*> pq; 
            vector<int> freqMap(26, 0);

            for(int i = 0; i < str.size(); i++){
                freqMap[str[i] - 'a']++;
            }

            for(int i = 0; i < freqMap.size(); i++){
                if(freqMap[i] > 0){
                    // cout<<char('a' + i)<< "; ";
                    pq.push(new Node((char)('a' + i) + "", freqMap[i], nullptr, nullptr));
                }
            }

            while(pq.size() > 1){
                Node* n1 = pq.top();
                pq.pop();
                Node* n2 = pq.top();
                pq.pop();

                pq.push(new Node(n1->data + n2->data, n1->freq + n2->freq, n1, n2));
            }

            Node* root = pq.top();
            cout<<root->data<<endl;
            huffmanTraversal(root, "");
        }

        void huffmanTraversal(Node* root, string binaryCode){

            if(root->left == nullptr && root->right == nullptr){
                encode[root->data] = binaryCode;
                decode[binaryCode] = root->data;

                // cout<<decode[binaryCode]<<" ";
                return;
            }

            huffmanTraversal(root->left, binaryCode + "0");
            huffmanTraversal(root->right, binaryCode + "1");
        }

    public:

        huffman(string str){
            huffmanTree(str);
        }

        string encodeString(string str){

            string encoded = "";
            for(int i = 0; i < str.size(); i++){
                encoded += encode[str[i] + ""];
            }
            return encoded;
        }

        string decodeString(string str){

            string decoded = "";
            int i = 0;

            for(int j = 1; j <= str.size(); j++){
                string s = str.substr(i, j);
                if(decode.find(s) != decode.end()){
                    decoded += decode[s];
                    i = j;
                }
            }
            return decoded;
        }
};

int main(){

    huffman hed("hskajdyekuqhowpqowouwytremnzxbcvasaldjsfhjowiqowqojpqsakja");

    // string en = hed.encodeString("harshit");
    // string de = hed.decodeString(en);

    // cout<<en<<" -> "<<de<<endl;

    // cout<<hed.encodeString("j");

    return 0;
}