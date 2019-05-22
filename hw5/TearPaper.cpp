//
// Created by 李得瑋 on 2019-05-16.
//

#include <unordered_map>
#include <iostream>
using namespace std;
#define REP(i, j, k) for(int i = j; i < k; i++)

int N = 0, M = 0, mod = 1000000007;
unordered_map<long, unsigned long long> umap;

void printMatrix(char** mx, int rowStart, int rowEnd, int colStart, int colEnd){
    REP(i, 0, rowEnd){
        if(i >= rowStart - 1){
            REP(j, 0, colEnd){
                if(j >= colStart - 1){
                    cout << mx[i][j] << " ";
                }
            }
        }
        cout << "\n";
    }
}

//c(m,n)=c(m-1,n-1)+c(m-1,n)
void initC(long long** C, int K){
    REP(i, 0, K + 1){
        C[i] = new long long[K + 1];
        REP(j, 0, i + 1){
            if(j == i || j == 0) {
                C[i][j] = 1;
            }else if(j == 1){
                C[i][j] = i;
            }else{
                C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
            }
        }
    }
}

/* 1-4 rowStart
 * 5-8 rowEnd
 * 9-12 colStart
 * 13-16 colEnd
 * 17-23 K
 * */
long getKey(int rowStart, int rowEnd, int colStart, int colEnd, int K){
    return (((((((rowStart << 4) + rowEnd) << 4) + colStart) << 4) + colEnd) << 6) + K;
}

unsigned long long splitMx(char** mx, int rowStart, int rowEnd,
        int colStart, int colEnd, int K, long long** C){
    unsigned long long res = 0;
    long key = getKey(rowStart, rowEnd, colStart, colEnd, K);
//    cout << key << "\n";
    if(K == 0){
        return 1;
    }else if(rowEnd == rowStart && colStart == colEnd){
        return 0;
    }else if(umap.find(key) != umap.end()){
//        cout << "find" << umap[key] << "\n";
        return umap[key];
    }else{
//        cout << "else\n";
        //根據 row 切
        if(rowStart != rowEnd){
            REP(i, rowStart, rowEnd + 1){
                bool can = true;
                REP(j, colStart, colEnd + 1){
                    if(mx[i - 1][j - 1] == 'X'){
                        can = false;
                        break;
                    }
                }
//                cout << i << "===" << can << "\n";
                if(can){
//                    res += 1;
                    if(i == rowStart){
                        res += splitMx(mx, rowStart + 1, rowEnd, colStart, colEnd, K - 1, C) % mod;
                    }else if(i == rowEnd){
                        res += splitMx(mx, rowStart, rowEnd - 1, colStart, colEnd, K - 1, C) % mod;
                    }else{
                        REP(k, 0, K){
                            unsigned long long r = 0;
                            r += C[K - 1][k] * splitMx(mx, rowStart, i - 1, colStart, colEnd, k, C) % mod;
                            r = r * splitMx(mx, i + 1, rowEnd, colStart, colEnd, K - k - 1, C) % mod;
                            if(r > 0 && i == 2 && K == 67){
                                cout << k << "\n";
                                cout << splitMx(mx, rowStart, i - 1, colStart, colEnd, k, C) << " " << splitMx(mx, i + 1, rowEnd, colStart, colEnd, K - k - 1, C) << "\n";
                            }
                            res += r;
                        }
                    }
                }
            }
        }

        if(colStart != colEnd){
//            cout << "row\n";
            REP(j, colStart, colEnd + 1){
                bool can = true;
                REP(i, rowStart, rowEnd + 1){
//                    cout << (mx[i - 1][j - 1]) << "\n";
                    if(mx[i - 1][j - 1] == 'X'){
                        can = false;
                        break;
                    }
                }
//                cout << j << "===" << can << "\n";
                if(can){
//                    res += 1;
                    if(j == colStart){
                        res += splitMx(mx, rowStart, rowEnd, colStart + 1, colEnd, K - 1, C) % mod;
                    }else if(j == colEnd){
                        res += splitMx(mx, rowStart, rowEnd, colStart, colEnd - 1, K - 1, C) % mod;
                    }else{
                        REP(k, 0, K){
                            unsigned long long r = 0;
                            r += C[K - 1][k] * splitMx(mx, rowStart, rowEnd, colStart, j - 1, k, C) % mod;
                            r = r * splitMx(mx, rowStart, rowEnd, j + 1, colEnd, K - k - 1, C) % mod;
//                            if(r > 0 && K == 67){
//                                cout << "col--"<< j << "---" << r << "\n";
//                            }
                            res += r;
                            res = res % mod;
                        }
                    }
                }
            }
        }
    }
    umap[key] = res % mod;
    return res % mod;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    //init everything
    cin >> N >> M;
    char** mx = new char*[N];
    REP(i, 0, N){
        mx[i] = new char[M];
        char temp = 0;
        REP(j, 0, M){
            cin >> temp;
            mx[i][j] = temp;
        }
    }

    //init permutation
    int K = M * N;
    long long** C = new long long*[K + 1];
    initC(C, K);

//    REP(i, 0, N){
//        REP(j, 0, M){
//            cout << int(mx[i][j]) << " ";
//        }
//        cout << "\n";
//    }

    //calc
    unsigned long long res = 0;
    REP(i, 0, K + 1){
        cout << "i---" <<  i << "\n";
        cout << splitMx(mx, 1, N, 1, M, i, C) << "\n";
        unsigned long long r = splitMx(mx, 1, N, 1, M, i, C);
        res += r;
        if(r == 0){
            break;
        }
    }
//    cout << res % mod;
//    cout << splitMx(mx, 1, N, 1, M, 67, C);
    return 0;
}