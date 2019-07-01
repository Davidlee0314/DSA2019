//
// Created by 李得瑋 on 2019-06-06.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
#define LOOP(i, j, k) for(int i = j; i < k; i++)

int da[4][4][4][4], db[4][4][4][4];

inline int tran(char a){
    if(a == 'M'){
        return 1;
    }else if(a == 'F'){
        return 2;
    }else{
        return 3;
    }
}

inline int score(int a, int b, int c){
    int r = 0;
    LOOP(i, 1, 4){
        if(a == i || b == i || c == i){
            r++;
        }
    }
    return r;
}

int main(){
    int N = 0;
    cin >> N;
    getchar();
    memset(da, -1, sizeof(da));
    memset(db, -1, sizeof(db));
    da[0][0][0][0] = 0;

    LOOP(i, 0, N){
        char a = 0;
        cin >> a;
        int temp = tran(a);
        LOOP(q, 0, 4){
            LOOP(r, 0, 4){
                LOOP(s, 0, 4){
                    int mx = -1;
                    LOOP(t, 0, 4){
                        int y = da[t][q][r][s] + score(t, q, temp);
                        if(da[t][q][r][s] != -1 && y > mx){
                            mx = y;
                        }
                    }
                    db[q][temp][r][s] = max(db[q][temp][r][s], mx);
                    mx = -1;
                    LOOP(t, 0, 4){
                        int y = da[q][r][t][s] + score(t, s, temp);
                        if(da[q][r][t][s] != -1 && y > mx){
                            mx = y;
                        }
                    }
                    db[q][r][s][temp] = max(db[q][r][s][temp], mx);
                }
            }
        }
        memcpy(da, db, sizeof(db));
    }

    int ans = -1;
    LOOP(i, 0, 4){
        LOOP(j, 0, 4){
            LOOP(k, 0, 4){
                LOOP(l, 0, 4){
                    if(da[i][j][k][l] > ans){
                        ans = da[i][j][k][l];
                    }
                }
            }
        }
    }
    cout << ans;
    return 0;
}