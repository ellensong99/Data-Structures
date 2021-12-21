#include <vector>    
#include <iostream>
#include <sstream>
#include <string>
using namespace std;


struct Node;
typedef Node* node_pointer;
struct Node{
    node_pointer left;
    node_pointer right;
    unsigned char c;
    string word;
    Node() {}
    Node(unsigned char c, string word = "", node_pointer l = nullptr, node_pointer r = nullptr) : left(l), right(r), c(c), word(word) {}
};

struct llNode;
typedef llNode* llnode_pointer;
struct llNode {
    node_pointer trie;
    int depth;
    int maxDpth;
    llnode_pointer prev;
    llnode_pointer next;
    llNode() {}
    llNode(node_pointer trie, int depth, int maxDpth, llnode_pointer prev, llnode_pointer next) : trie(trie), depth(depth), maxDpth(maxDpth), prev(prev), next(next) {}
};

void buildTree(llnode_pointer llnode) {
    llnode_pointer cur = llnode;
    while (cur->depth != 0) {
        while (cur->next) {
            if (cur->depth == cur->maxDpth) {
                node_pointer node = new Node(char(0), cur->trie->word.append(cur->next->trie->word), cur->trie, cur->next->trie);
                llnode_pointer lnode = new llNode(node, cur->depth-1, 0, cur->next->next, cur->prev);
                if (cur->prev) {
                    cur->prev->next = lnode;
                }
                if (cur->next->next) {
                    cur->next->next->prev = lnode; 
                }
                if (llnode == cur) {
                    llnode = lnode;
                }
                cur = lnode;
            } 
            if (cur->next) {
                cur = cur->next;
            }
        }
        cur = llnode;
        llnode->maxDpth--;
    }
}

void decodePrint(node_pointer T, string code) {
    int len = code.length();
    node_pointer cur = T;
    for (int i = 0; i < len; i++) {
        if (text[i] == '0') {
            if (!cur->left->left) {
                cout << cur->left->c;
                cur = T;
            }
        } else if (text[i] == '1') {
            if (!cur->right->left) {
                cout << cur->right->c;
                cur = T;
            }
        }
    }
}

//----------------------------------------------------//
// main                                               //
//----------------------------------------------------//
int main(){ 
    string tree, code;
    getline(cin, tree);
    getline(cin, code);
    node_pointer node = new Node(tree[0], string(tree[0]), nullptr, nullptr);
    int pos = 1;
    char s = tree[pos];
    while (s != ' ') {
        pos++;
        s = tree[pos];
    }
    int depth = stoi(tree.substr(1, pos-1));
    llnode_pointer head = new llNode(node, depth, depth, nullptr, nullptr);
    int len = tree.length();
    llnode_pointer cur = head;
    int maxDpth = depth;
    for (int i = pos + 1; i < len; i++) {
        node_pointer node = new Node(tree[i], string(tree[i]), nullptr, nullptr);
        s = tree[i+1];
        int count = 0;
        while (s != ' ') {
            s = tree[i+2];
            count++;
        }
        depth = stoi(tree.substr(i+1, count));
        if (depth > maxDpth) {
            maxDpth = depth;
        }
        llnode_pointer lnode = new llNode(node, depth, 0, cur, nullptr);
        cur->next = lnode;
        cur = lnode;
        i = i + count + 2;
    }
    head->maxDpth = maxDpth;
    buildTree(head);
    decodePrint(head->trie, code);
}
