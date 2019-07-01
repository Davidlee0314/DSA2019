//
// Created by 李得瑋 on 2019-06-14.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int N = 200005;
#define LP(i, j, k) for(int i = j; i < k; i++)
typedef long long ll;
const ll INF = 1LL << 60;
ll sum[N], dp[N], v[N];
vector<int>map[N];
ll output = -INF;

ll dfs_sum(int u, int from){
    if(sum[u] == -INF){
        sum[u] = v[u];
        LP(i, 0, map[u].size()){
            int v = map[u][i];
            if(v == from) continue;
            sum[u] += dfs_sum(v, u);
        }
        return sum[u];
    }else{
        return sum[u];
    }
}

void dfs_dp(int u, int from){
    LP(i, 0, map[u].size()){
        int v = map[u][i];
        if(v == from) continue;
        dfs_dp(v, u);

        if(dp[u] != -INF && dp[v] != -INF){
            output = max(output, dp[u] + dp[v]);
        }
        dp[u] = max(dp[u], dp[v]);
    }
    dp[u] = max(dp[u], sum[u]);
}

int main(){
    int n = 0;
    cin >> n;
    LP(i, 1, n + 1){
        cin >> v[i];
        sum[i] = -INF;
        dp[i] = -INF;
    }
    LP(i, 0, n - 1){
        int x = 0, y = 0;
        cin >> x >> y;
        map[x].push_back(y);
        map[y].push_back(x);
    }
    dfs_sum(1, -1); dfs_dp(1, -1);
    if(output == -INF) cout << "Impossible\n";
    else cout << output << "\n";
    return 0;
}