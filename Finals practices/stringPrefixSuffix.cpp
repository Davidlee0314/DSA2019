//
// Created by 李得瑋 on 2019-06-12.
//

#include <iostream>
#include <string>
#include <vector>
using namespace std;
#define REP(i, j, k) for(int i = j; i < k; i++)

int HASH_BASE = 23, M = 1000000007;
long long hashStore[500000];
long long expStore[500000];
pair<int, int>count1 = {0, 0}, count2 = {0, 0}, count3 = {0, 0};

long long getHash(int i, int j){
    return (hashStore[j] - (hashStore[i - 1] * expStore[j - i + 1] % M) + M) % M;
}

void initExp(){
    expStore[0] = 1;
    REP(i, 1, 500000){
        expStore[i] = expStore[i - 1] * HASH_BASE % M;
    }
}

void initHash(string& s, int length){
    hashStore[0] = 0;
    REP(i, 1, length + 1){
        if(s[i - 1] == '0'){
            count2.first += 1;
        }else{
            count2.second += 1;
        }
        hashStore[i] = (hashStore[i - 1] * HASH_BASE + s[i - 1]) % M;
    }
}

int main(){
    string s, t, res;
    cin >> s >> t;
    initExp();
    initHash(t, (int)t.length());

    REP(i, 0, s.length()){
        if(s[i] == '0'){
            count1.first += 1;
        }else{
            count1.second += 1;
        }
    }
    int same = 0;
    for(int i = (int)(t.length() - 1); i >= 1; i--){
//        cout << i << ": " << getHash(1, i) << " " << getHash((int)(t.length() - i + 1), (int)(t.length())) << endl;
        if(getHash(1, i) == getHash((int)(t.length() - i + 1), (int)(t.length()))){
            same = i;
            break;
        }
    }
    REP(i, same, t.length()){
        if(t[i] == '0'){
            count3.first += 1;
        }else{
            count3.second += 1;
        }
    }
//    cout << count3.first << count3.second << same << endl;
//    cout << count1.first << " " << count1.second << " " << count2.first << " " << count2.second << endl;
    if(count1.first < count2.first || count1.second < count2.second){
        cout << s;
    }else{
        res.append(t);
        count1.first -= count2.first;
        count1.second -= count2.second;
        while(count1.first >= count3.first && count1.second >= count3.second){
            res.append(t, same, s.length() - same);
            count1.first -= count3.first;
            count1.second -= count3.second;
        }
//        cout << count1.first << count1.second << endl;
        string temp1(count1.first, '0');
        string temp2(count1.second, '1');
        res.append(temp1); res.append(temp2);
        cout << res;
    }
    return 0;
}