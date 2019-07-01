//
// Created by 李得瑋 on 2019-06-13.
//
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
using namespace std;
#define REP(i, j, k) for(int i = j; i < k; i++)

int HASH_BASE = 41, M = 1000000007;
long long hashStore[2101];
long long hashStoreRev[2101];
long long hashStoret[2101];
long long expStore[2101];

long long getHash(int i, int j){
    return (hashStore[j] - (hashStore[i - 1] * expStore[j - i + 1] % M) + M) % M;
}

long long getHasht(int i, int j){
    return (hashStoret[j] - (hashStoret[i - 1] * expStore[j - i + 1] % M) + M) % M;
}

//輸入反過來的index
long long getHashRev(int i, int j){
    return (hashStoreRev[j] - (hashStoreRev[i - 1] * expStore[j - i + 1] % M) + M) % M;
}

void initExp(){
    expStore[0] = 1;
    REP(i, 1, 2101){
        expStore[i] = expStore[i - 1] * HASH_BASE % M;
    }
}

void initHash(string& s, int length){
    hashStore[0] = 0;

    //
    hashStoreRev[0] = 0;

    REP(i, 1, length + 1){
        //
        hashStoreRev[i] = (hashStoreRev[i - 1] * HASH_BASE + s[length - i]) % M;

        hashStore[i] = (hashStore[i - 1] * HASH_BASE + s[i - 1]) % M;
    }
}

void initHasht(string& s, int length){
    hashStoret[0] = 0;
    REP(i, 1, length + 1){
        hashStoret[i] = (hashStoret[i - 1] * HASH_BASE + s[i - 1]) % M;
    }
}

int main(){
    string s, t;
    cin >> s >> t;
    initExp();
    initHash(s, (int)s.length());
    initHasht(t, (int)t.length());
//    REP(i, 0, (int)s.length() + 1){
//        cout << hashStore[i] << endl;
//    }
//    REP(i, 0, (int)t.length() + 1){
//        cout << hashStoret[i] << endl;
//    }
//    unordered_map<long long, int> map;
    vector<int>res; bool solve = false; int pos = 0;
    while(!solve){
        int limit = min((int)(t.length() - pos), (int)s.length()); bool re = false;
        for(int i = limit; i > 0; i--){
            if(i == 1){
                string::size_type temp = s.find(t[pos]);
                if(temp == s.npos){
                    solve = true;
                }else{
                    res.push_back((int)temp + 1);
                    res.push_back((int)temp + 1);
                    pos += i;
                    if(pos == t.length()){
                        solve = true;
                    }
                    break;
                }
            }else{
                int time = (int)s.length() - i + 1;
                REP(j, 0, time){
//                    long long hash = getHash(j + 1, j + i);
                    if(getHash(j + 1, j + i) == getHasht(pos + 1, pos + i)){
                        res.push_back(j + 1);
                        res.push_back(j + i);
                        pos += i; re = true;
                        break;
                    }else if(getHashRev(j + 1, j + i) == getHasht(pos + 1, pos + i)){
                        res.push_back((int)s.length() - j);
                        res.push_back((int)s.length() - j - i + 1);
                        pos += i; re = true;
                        break;
                    }
                }
//                if(!renew){
//                    REP(j, 0, time){
//                        if(getHashRev(j + 1, j + i) == getHasht(pos + 1, pos + i)){
//                            res.push_back((int)s.length() - j);
//                            res.push_back((int)s.length() - j - i + 1);
//                            pos += i; re = true;
//                            break;
//                        }
//                    }
//                }
                if(pos == t.length()){
                    solve = true;
                }
                if(re){
                    break;
                }
            }

        }
    }
    if(res.empty() || pos != t.length()){
        cout << -1;
    }else{
        cout << res.size() / 2;
        REP(i, 0, res.size()){
            if(i % 2 == 0){
                cout << "\n" << res[i];
            }else{
                cout << " " << res[i];
            }
        }
    }

    return 0;
}