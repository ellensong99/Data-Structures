#include <iostream>
#include <string>
#include <vector>
using namespace std;

//----------------------------------------------------//
// nodes for binary trees                             //                                   
//----------------------------------------------------//
struct Node;
typedef Node* node_pointer;
struct Node{
    node_pointer left;
    node_pointer right;
    unsigned char c;
    int freq;
    Node() {}
    Node(unsigned char c, int f, node_pointer l = nullptr, node_pointer r = nullptr) : left(l), right(r), c(c), freq(f) {}
};

int comp(node_pointer a, node_pointer b){
    return -(a->freq - b->freq);
}

void fixUp(vector<node_pointer>& minheap) {
    int i = minheap.size()-1;
    int parent = (i - 1) / 2;
    while ((parent >= 0) & (minheap[parent]->freq > minheap[i]->freq)) {
        node_pointer tmp = minheap[parent];
        minheap[parent] = minheap[i];
        minheap[i] = tmp;
        i = parent;
        parent = (i - 1) / 2;
    }
}

void fixDown(vector<node_pointer>& minheap) {
    int i = 0;
    while (2 * i + 1 < minheap.size()) {
        int j = 2 * i + 1;
        if ((j + 1 != minheap.size()) & (minheap[j]->freq > minheap[j+1]->freq)) {
            j++;
        }
        if (minheap[i]->freq <= minheap[j]->freq) {
            break;
        }
        node_pointer tmp = minheap[i];
        minheap[i] = minheap[j];
        minheap[j] = tmp;
        i = j;
    }
}

node_pointer deleteMin(vector<node_pointer>& minheap) {
    if (minheap.size() != 0) {
        node_pointer tmp = minheap[0];
        int l = minheap.size() - 1;
        minheap[0] = minheap[l];
        minheap[l] = tmp;
        minheap.pop_back();
        fixDown(minheap);
        return tmp;
    }
}

void printTrie(node_pointer T, vector<string>& charPrint, int k, string word) {
    if (T->c == char(0)) {
        k++;
        if (T->left) {
            printTrie(T->left, charPrint, k, word.append("0")); 
        } 
        if (T->right) {
            word.pop_back();
            printTrie(T->right, charPrint, k, word.append("1"));
        }
    } else {
        cout << T->c << k << " ";
        charPrint[T->c] = word;
    }
}


//----------------------------------------------------//
// main                                               //
//----------------------------------------------------//
int main(){ 
    string text;
    getline(cin, text);
    vector<int> charFreq = vector<int>(256);
    for (int i = 0; i < text.length(); i++) {
        unsigned char c = text[i];
        charFreq[c]++;
    }
    vector<node_pointer> minheap = vector<node_pointer>();
    for (int i = 0; i < charFreq.size(); i++) {
        if (charFreq[i] != 0) {
            node_pointer node = new Node(char(i), charFreq[i], nullptr, nullptr);
            minheap.push_back(node);
            fixUp(minheap);
        }
    }
    while (minheap.size() > 1) {
        node_pointer T1 = deleteMin(minheap);
        node_pointer T2 = deleteMin(minheap);
        node_pointer node = new Node(char(0), T1->freq + T2->freq, T1, T2);
        minheap.push_back(node);
        fixUp(minheap);
    }
    node_pointer Trie = deleteMin(minheap);
    vector<string> charPrint = vector<string>(256, "");
    printTrie(Trie, charPrint, 0, "");
    cout << endl;
    for (int i = 0; i < text.length(); i++) {
        cout << charPrint[text[i]];
    }
}
