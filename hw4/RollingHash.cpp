#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;
#define REP(i, j, k) for(int i = j; i < k; i++)

int HASH_BASE_1 = 11, HASH_BASE_2 = 23, M = 1000000007;

void initHash(string& s, long long* hashStore_1, long long* hashStore_2, int length){
    hashStore_1[0] = 0;
    hashStore_2[0] = 0;
    REP(i, 1, length + 1){
        hashStore_1[i] = (hashStore_1[i - 1] * HASH_BASE_1 + s[i - 1]) % M;
        hashStore_2[i] = (hashStore_2[i - 1] * HASH_BASE_2 + s[i - 1]) % M;
    }
}

void initExp(vector<long long>& expStore_1, vector<long long>& expStore_2){
    REP(i, 0, 100000){
        if(i == 0){
            expStore_1.push_back(1);
            expStore_2.push_back(1);
        }else{
            expStore_1.push_back((expStore_1.back() * HASH_BASE_1) % M);
            expStore_2.push_back((expStore_2.back() * HASH_BASE_2) % M);
        }

    }
}

long long getHash(const long long* hashStore, vector<long long>& expStore, int i, int j){
//    cout <<expStore[j - i + 1] <<"~~"<< hashStore[i - 1] * expStore[j - i + 1] <<"\n";
    return (hashStore[j] - (hashStore[i - 1] * expStore[j - i + 1] % M) + M) % M;
}

pair<int, int> getAnswer_1(string& s, const long long* hashStore_1,
                           vector<long long>& expStore_1, const long long* hashStore_2,
                           vector<long long>& expStore_2, int m){
    pair<int, int>res;
    int left = 1, right = (int)(s.length()) - m + 1, tryLength = (left + right) / 2;
    bool haveMeetM = false;
    while(left <= right){
        unordered_map<long long, int> umap_1;
        unordered_map<long long, int> umap_2;
        long long hash_1 = 0, hash_2 = 0;
        bool meetM = false;

        REP(i, 0, (int)s.length() - tryLength + 1){
            hash_1 = getHash(hashStore_1, expStore_1, i + 1, i + tryLength);
            hash_2 = getHash(hashStore_2, expStore_2, i + 1, i + tryLength);
            if(umap_1.find(hash_1) != umap_1.end()){
                if(umap_2.find(hash_2) != umap_2.end()){
                    umap_1[hash_1] += 1; umap_2[hash_2] += 1;
                    if(umap_1[hash_1] >= m && umap_2[hash_2] >= m) {
                        meetM = true;
                        haveMeetM = true;
                        break;
                    }
                }
            }else{
                umap_1[hash_1] = 1; umap_2[hash_2] = 1;
                if(m == 1){
                    meetM = true;
                    haveMeetM = true;
                    break;
                }
            }
        }
        if(!meetM){
            right = tryLength - 1;
            tryLength = (left + right) / 2;
        }else{
            left = tryLength + 1;
            tryLength = (left + right) / 2;
        }
    }
    if(!haveMeetM){
        res.first = -1;
    }else{
        res.first = tryLength;
        unordered_map<long long, int> umap_1;
        unordered_map<long long, int> umap_2;
        long long hash_1 = 0, hash_2 = 0;

        REP(i, 0, (int)s.length() - res.first + 1){
            hash_1 = getHash(hashStore_1, expStore_1, i + 1, i + res.first);
            hash_2 = getHash(hashStore_2, expStore_2, i + 1, i + res.first);
            if(umap_1.find(hash_1) != umap_1.end()){
                if(umap_2.find(hash_2) != umap_2.end()){
                    umap_1[hash_1] += 1; umap_2[hash_2] += 1;
                    if(umap_1[hash_1] >= m && umap_2[hash_2] >= m) {
                        res.second = i;
                    }
                }
            }else{
                umap_1[hash_1] = 1; umap_2[hash_2] = 1;
                if(m == 1){
                    res.second = i;
                }
            }
        }
    }
    return res;
}
pair<int, int> getAnswer_2(string& s, const long long* hashStore_1,
                        vector<long long>& expStore_1, const long long* hashStore_2,
                           vector<long long>& expStore_2){
    pair<int, int> res;
    res.first = -1;
    if(s.length() > 2){
        vector<int> possLength;
        REP(i, 1, (int)s.length() - 1){
            if( hashStore_1[i] == getHash(hashStore_1, expStore_1, (int)s.length() - i + 1, (int)s.length()) &&
                    hashStore_2[i] == getHash(hashStore_2, expStore_2, (int)s.length() - i + 1, (int)s.length())){
                possLength.push_back(i);
            }
        }
        if(!possLength.empty()){
            int left = 0, right = (int)possLength.size() - 1, mid = (right + left) / 2;
            while(left <= right){
                int tryLength = possLength[mid];
                bool fulfill = false;
                REP(j, 2, (int)s.length() - tryLength + 1){
                    long long hashtry_1 = getHash(hashStore_1, expStore_1, j, j + tryLength - 1);
                    if(hashtry_1 == hashStore_1[tryLength]){
                        long long hashtry_2 = getHash(hashStore_2, expStore_2, j, j + tryLength - 1);
                        if(hashtry_2 == hashStore_2[tryLength]){
                            res.first = j - 1;
                            res.second = tryLength;
                            fulfill = true;
                            break;
                        }
                    }
                }
                if(!fulfill){
                    right = mid - 1;
                    mid = (left + right) / 2;
                }else{
                    left = mid + 1;
                    mid = (left + right) / 2;
                }
            }
        }
        return res;
    }else{
        return res;
    }
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    string s;
    int m = 0, index = 0;
    cin >> m;
    vector<long long>expStore_1, expStore_2;
    initExp(expStore_1, expStore_2);
    while(m != 0){
        cin >> s;
        int length = (int)(s.length());

//        init two hash store array
        long long* hashStore_1 = new long long[length + 1];
        long long* hashStore_2 = new long long[length + 1];
        initHash(s, hashStore_1, hashStore_2, length);

//        getAnswer one
        pair<int, int>res;
        res = getAnswer_1(s, hashStore_1, expStore_1, hashStore_2, expStore_2, m);
        if(index == 0){
            if(res.first != -1){
                cout << res.first << " " << res.second;
            }else{
                cout << "none";
            }
        }else{
            if(res.first != -1){
                cout << "\n" << res.first << " " << res.second;
            }else{
                cout << "\n" << "none";
            }
        }

//        getAnswer two
        res = getAnswer_2(s, hashStore_1, expStore_1, hashStore_2, expStore_2);
        if(res.first != -1){
            cout << "\n" << s.substr((unsigned long)res.first, (unsigned long)res.second);
        }else{
            cout << "\nJust a legend";
        }

//        start another test
        delete[] hashStore_1;
        delete[] hashStore_2;
        index++;
//        preLength = length;
        cin >> m;
    }
    return 0;
}