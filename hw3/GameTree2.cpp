//
// Created by 李得瑋 on 2019-04-24.
//
#include <iostream>
#include <bitset>
#include <unordered_map>
#include <vector>
#include <utility>
#include <string>
using namespace std;
#define REP(i, j, k) for(int i = j; i < k; i++)
#define BREP(i, j, k) for(size_t i = j; i < k; i++)

//3 DQ H3 H2 D3 HA D6
/* 59 位數的 bits 紀錄
     * -> 1 - 17 Alice 的牌
     * -> 18 - 34 Bob 的牌
     * -> 35 who's turn
     * -> 36 - 37 花色 C D H S
     * -> 38 - 41 牌數
     * -> 42 - 51 (+-)alpha
     * -> 52 - 61 (+-)beta
    */

struct Node{

    bitset<61> hash;
    int turn; // 1 for Alice, 0 for Bob
    Node(int t, int n){
        hash.reset();
        turn = t;
        //set turn
        if(turn == 1){
            hash.set(34);
        }
    }
};

struct Game{
    int N;
    int A;
    int B;
    vector<pair<int, int>>alice;
    vector<pair<int, int>>bob;
    unordered_map<long long unsigned, int>umap;
    Game(int n){
        N = n;A = n;B = n;
        REP(i, 0, 2 * N){
            char* temp = new char[3];
            cin >> temp;
            pair<int, int>p;
            if(temp[0] == 'C'){
                p.first = 0;
            }else if(temp[0] == 'D'){
                p.first = 1;
            }else if(temp[0] == 'H'){
                p.first = 2;
            }else if(temp[0] == 'S'){
                p.first = 3;
            }
            if(temp[1] == 'A'){
                p.second = 1;
            }else if(temp[1] == 'T'){
                p.second = 10;
            }else if(temp[1] == 'J'){
                p.second = 11;
            }else if(temp[1] == 'Q'){
                p.second = 12;
            }else if(temp[1] == 'K'){
                p.second = 13;
            }else{
                p.second = temp[1] - 48;
            }
            if(i < N){
                alice.push_back(p);
            }else{
                bob.push_back(p);
            }
        }
    }
};

int countScore (int n, int turn, bitset<61>& hash, vector<pair<int, int>>& v){
    int res = 0;
    size_t base = (turn == 1) ? 0 : 17;
    BREP(i, 0, n){
        if(hash[i + base] == 1){
            res += v[i].second;
        }
    }
    return res;
}
int ind = 0;

int minmax(Node* parent, Game* g){
    ind ++;
    int turn = (int)parent->hash[34];
//    cout << parent->hash << "before" << endl;
//    cout << ind << ".==================" << turn << "=====" << g->A << "====" << g->B << endl;

    //one's turn while the other does't have cards
    if(turn == 1 && g->B == 0){
        int resFast = countScore(g->N, turn, parent->hash, g->alice);
//        cout << "Bob win" << 0 - resFast<< endl;
        return 0 - resFast;
    }else if(turn == 0 && g->A == 0){
        int resFast = countScore(g->N, turn, parent->hash, g->bob);
//        cout << "Alice win" << resFast << endl;
        return resFast;
    }

    //check umap value
    if(g->umap.find(parent->hash.to_ullong()) != g->umap.end()){
//        cout << "find";
        return g->umap[parent->hash.to_ullong()];
    }

    //copy the card outside
    bitset<2>colorbit; bitset<4>numbit;
    BREP(i, 35, 37){
        colorbit[i - 35] = parent->hash[i];
    }
    BREP(i, 37, 41){
        numbit[i - 37] = parent->hash[i];
    }
    int color = (int)colorbit.to_ulong(); int num = (int)numbit.to_ulong();
    bool firstOut = num == 0;

    //clone alpha and beta
    bitset<9>alpha; bitset<9>beta;
    BREP(i, 42, 51){
        alpha[i - 42] = parent->hash[i];
    }
    BREP(i, 52, 61){
        beta[i - 52] = parent->hash[i];
    }
    int alphaOrigin = (int)alpha.to_ulong();
    if(parent->hash[41] == 1){
        alphaOrigin = 0 - alphaOrigin;
    }
    int betaOrigin = (int)beta.to_ulong();
    if(parent->hash[51] == 1){
        betaOrigin = 0 - betaOrigin;
    }

    //check card to go after
    //init child node
    Node* child = new Node(0, g->N);
    BREP(j, 0 , 61){
        if(j != 34){
            if(parent->hash[j] == 1){
                child->hash.set(j);
            }else{
                child->hash.reset(j);
            }
        }else{
            if(parent->hash[j] == 1){
                child->hash.reset(j);
            }else{
                child->hash.set(j);
            }
        }
    }

    int res = (turn == 1) ? 0 : 1000;
    bool pass = true;
    BREP(i, 0, g->N){
        int resChild = 0;
        //max node
        if(turn == 1){
            if(parent->hash[i] == 1 && (g->alice[i].first == color ||
                                        g->alice[i].second == num || firstOut)){
                //取消 pass
                pass = false;

                //出 i 張牌
                bitset<2>colorbit2((unsigned long long)g->alice[i].first);
                bitset<4>numbit2((unsigned long long)g->alice[i].second);
                BREP(j, 35, 37){
                    if(colorbit2[j - 35] == 1){
                        child->hash.set(j);
                    }else{
                        child->hash.reset(j);
                    }
                }
                BREP(j, 37, 41){
                    if(numbit2[j - 37] == 1){
                        child->hash.set(j);
                    }else{
                        child->hash.reset(j);
                    }
                }

                //pass alpha beta to child
                if(alphaOrigin < 0){
                    bitset<9>alpha2((unsigned long long)(0 - alphaOrigin));
                    BREP(j, 42, 51){
                        child->hash[j] = alpha2[j - 42];
                    }
                    child->hash.set(41);
                }else{
                    bitset<9>alpha2((unsigned long long)(alphaOrigin));
                    BREP(j, 42, 51){
                        child->hash[j] = alpha2[j - 42];
                    }
                    child->hash.reset(41);
                }
                BREP(j, 51, 61){
                    child->hash[j] = parent->hash[j];
                }

                //出牌調整hash
                g->A -= 1; child->hash.reset(i);
                resChild = minmax(child, g);
                g->A += 1; child->hash.set(i);

                //update alpha
                if(resChild > alphaOrigin){
                    alphaOrigin = resChild;
                }

                //update the max value
                if(res == 0){
                    res = resChild;
                }else{
                    if(resChild > res){
                        res = resChild;
                    }
                }

                //pruning
                if(alphaOrigin >= betaOrigin){
                    g->umap[parent->hash.to_ullong()] = res;
                    return res;
                }
            }
            //min node
        }else{
            if(parent->hash[i + 17] == 1 && (
                    g->bob[i].first == color || g->bob[i].second == num || firstOut)){
                //取消 pass
                pass = false;

                //出 i 張牌
                bitset<2>colorbit2((unsigned long long)g->bob[i].first);
                bitset<4>numbit2((unsigned long long)g->bob[i].second);
                BREP(j, 35, 37){
                    if(colorbit2[j - 35] == 1){
                        child->hash.set(j);
                    }else{
                        child->hash.reset(j);
                    }
                }
                BREP(j, 37, 41){
                    if(numbit2[j - 37] == 1){
                        child->hash.set(j);
                    }else{
                        child->hash.reset(j);
                    }
                }

                //pass alpha beta to child
                BREP(j, 41, 51){
                    child->hash[j] = parent->hash[j];
                }
                if(betaOrigin < 0){
                    bitset<9>beta2((unsigned long long)(0 - betaOrigin));
                    BREP(j, 52, 61){
                        child->hash[j] = beta2[j - 52];
                    }
                    child->hash.set(51);
                }else{
                    bitset<9>beta2((unsigned long long)betaOrigin);
                    BREP(j, 52, 61){
                        child->hash[j] = beta2[j - 52];
                    }
                    child->hash.reset(51);
                }

                //出牌調整hash
                g->B -= 1; child->hash.reset(i + 17);
                resChild = minmax(child, g);
                g->B += 1; child->hash.set(i + 17);

                //update beta
                if(resChild < betaOrigin){
                    betaOrigin = resChild;
                }

                //update the min value
                if(res == 1000){
                    res = resChild;
                }else{
                    if(resChild < res){
                        res = resChild;
                    }
                }

                //pruning
                if(alphaOrigin >= betaOrigin){
//                        cout << "prune";
                    g->umap[parent->hash.to_ullong()] = res;
                    return res;
                }
            }
        }
    }
//    cout << alphaOrigin << ": " << betaOrigin << endl;
    if(pass){
        BREP(i, 35, 41){
            child->hash.reset(i);
        }
//        cout << "PASS"<< child->hash << endl;
        int resChild = minmax(child, g);
        g->umap[parent->hash.to_ullong()] = resChild;
        return resChild;
    }else{
        g->umap[parent->hash.to_ullong()] = res;
//        cout << parent->hash << "after" << endl;
        return res;
    }
}

int main(){
    //declare ,cin N
    int N = 0; cin >> N;

    //init game and cin cards
    Game* g = new Game(N);

    //init root node and its hash
    Node* root = new Node(1, N);
    BREP(i, 0, 2 * N){
        if(i < N){
            root->hash.set(i);
        }else{
            root->hash.set(i - N + 17);
        }
    }
    //set alpha -511, beta 511
    BREP(i, 0, 20){
        if(i != 10){
            root->hash.set(i + 41);
        }
    }
//    cout << root->hash << endl;
//    REP(i, 0, N * 2){
//        if(i < N){
//            cout << g->alice[i].second << endl;
//        }else{
//            cout << g->bob[i - N].second << endl;
//        }
//    }
    int res = minmax(root, g);
    if(res < 0){
        cout << "Bob" << endl << 0 - res;
    }else{
        cout << "Alice" << endl << res;
    }
    return 0;
}