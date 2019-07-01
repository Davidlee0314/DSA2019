//
// Created by 李得瑋 on 2019-06-14.
//

#include <iostream>
#include <limits>
#include <algorithm>
using namespace std;
const int N = 201;
int arr[N], dp[N][N];
#define REP(i, j, k) for(int i = j; i < k; i++)
#define RREP(i, j, k) for(int i = j; i > k; i--)

int main(){
    int t = 0;
    int INF = numeric_limits<int>::max();
    cin >> t;
    REP(r, 0, t){
        int n = 0, m = 0;
        cin >> n >> m;
        REP(i, 1, n + 1){
            cin >> arr[i];
        }
        REP(i, 1, n + 1) dp[i][i] = 1;
        RREP(i, n, 0){
            REP(j, i + 1, n + 1){
                dp[i][j] = INF;
                REP(k, i, j){
                    int tmp = dp[i][k] + dp[k + 1][j];
                    if(arr[i] == arr[k+1] || arr[k] == arr[j]){
                        tmp--;
                    }
                    dp[i][j] = min(dp[i][j], tmp);
                }
//                if(arr[i] == arr[j]) dp[i][j]--;
            }
        }
        cout << dp[1][n] << "\n";
    }
}