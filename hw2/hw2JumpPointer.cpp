//
// Created by 李得瑋 on 2019-03-30.
//
#include <iostream>
using namespace std;
#define REP(i, j, k) for(int i = j; i < k; i++)

//input format
/*

10
0 e
0 f
2 f
2 f
2 e
0 e
3 e
2 f
1 f
6 f
10
1 1
8 10
10 9
1 3
10 2
7 2
7 4
1 6
1 5
6 3

*/

struct TrieNode{
    TrieNode* sons[26];
    int depth;
    int tin;
    int tout;
    int num;
    TrieNode(){
        this->depth = 0;
        this->tin = 0;
        this->tout = 0;
        this->num = 0;
        REP(i, 0, 26){
            this->sons[i] = nullptr;
        }
    }
    TrieNode* append(int a){
        this->sons[a - 97] = new TrieNode();
        return this->sons[a - 97];
    }
};

int timer = 0;
int log2(int n){
    int i = 0;
    while(1 << i <= n){
        i++;
    }
    return i - 1;
}

struct Trie{
    TrieNode** nodeList;
    TrieNode*** parent;
    TrieNode* trieRoot;
    int nodeNum;
    int lengthPar;

    Trie(int N){
        trieRoot = new TrieNode();
        nodeList = new TrieNode* [N];
        nodeNum = 0;

        int tempNode = 0;
        char tempChar = 0;
        REP(i, 0, N){
            cin >> tempNode >> tempChar;
            if(tempNode == 0){
                if(!trieRoot->sons[(int)tempChar - 97]){
                    nodeList[i] = trieRoot->append((int)tempChar);
                    nodeNum++;
                    nodeList[i]->num = nodeNum;
                }else{
                    nodeList[i] = trieRoot->sons[(int)tempChar - 97];
                }
            }else{
                if(!nodeList[tempNode - 1]->sons[(int)tempChar - 97]){
                    nodeList[i] = nodeList[tempNode - 1]->append((int)tempChar);
                    nodeNum++;
                    nodeList[i]->num = nodeNum;
                }else{
                    nodeList[i] = nodeList[tempNode - 1]->sons[(int)tempChar - 97];
                }
            }
        }
        parent = new TrieNode** [nodeNum + 1];
        lengthPar = log2(nodeNum);
        REP(i, 0, nodeNum + 1){
            parent[i] = new TrieNode* [lengthPar];
            REP(j, 0, lengthPar){
                parent[i][j] = nullptr;
            }
        }
        calcDepth(trieRoot, nullptr);
    }
    void calcDepth(TrieNode* root, TrieNode* par){
        root->tin = timer++;
        if(par){
            parent[root->num][0] = par;
            REP(i, 1, lengthPar){
                if(parent[root->num][i - 1] &&
                    parent[parent[root->num][i - 1]->num][i - 1]){
                    parent[root->num][i] = parent[parent[root->num][i - 1]->num][i - 1];
                }
            }
        }else{
            parent[root->num][0] = root;
        }
        REP(i, 0, 26){
            if(root->sons[i]){
                root->sons[i]->depth = root->depth + 1;
                calcDepth(root->sons[i], root);
            }
        }
        root->tout = timer++;
        return;
    }
    // x 是否為 y 的父親
    bool isAncestor(TrieNode* x, TrieNode* y){
        return x->tin <= y->tin && x->tout >= y->tout;
    }
    int LCA(TrieNode* x, TrieNode* y){
        if(isAncestor(x, y)){
            return x->depth;
        }
        if(isAncestor(y, x)){
            return y->depth;
        }
        for(int i = lengthPar - 1; i >= 0; i--){
            if(parent[x->num][i]){
                if(!isAncestor(parent[x->num][i], y)){
                    x = parent[x->num][i];
                }
            }
        }
        return parent[x->num][0]->depth;
    }
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int N = 0;
    cin >> N;

    Trie* t = new Trie(N);
//    REP(i, 0, t->nodeNum + 1){
//        REP(j, 0, t->lengthPar){
//            if(t->parent[i][j])
//                cout << t->parent[i][j]->num;
//        }
//        cout << "\n";
//    }
    int Q = 0, x = 0, y = 0;
    cin >> Q;
    REP(i, 0, Q){
        cin >> x >> y;
        if(i == Q - 1){
            cout << t->LCA(t->nodeList[x - 1], t->nodeList[y - 1]);
        }else{
            cout << t->LCA(t->nodeList[x - 1], t->nodeList[y - 1]) << "\n";
        }
    }
}