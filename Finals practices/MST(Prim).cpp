//
// Created by 李得瑋 on 2019-06-16.
//

#include <cstdio>
#include <limits>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
#define REP(i, j, k) for(int i = j; i < k; i++)
#define F first
#define S second
typedef pair<int, int> P;
const int N = 100005;
bool visited[N];
int m, n;

struct edge{
    int to;
    long long cost;
    edge(int v, long long c){
        to = v; cost = c;
    }
};
vector<edge> graph[N];
int MST(){
    fill(visited, visited + n + 1, false);
    priority_queue<P, vector<P>, greater<>>Q;
    int res = 0, num = 0;
    Q.push(P(0, 1));

    while(!Q.empty()){
        P p = Q.top(); Q.pop();
        int v = p.S;
        if(visited[v]) continue;
        for(int i = 0; i < graph[v].size(); i++){
            edge &e = graph[v][i];
            Q.push(P(e.cost, e.to));
        }
        res += p.F;
        visited[v] = true; num += 1;
    }
    if(num == n){
        return res;
    }
    return -1;
}



int main(){
//    int ind = 0;
    scanf("%d %d", &n, &m);
    while(m != 0 && n != 0){
        int a, b, c;
        REP(i, 0, m){
            scanf("%d %d %d", &a, &b, &c);
//            printf("%d %d %d\n", a, b, c);
            graph[a].emplace_back(edge(b, c));
            graph[b].emplace_back(edge(a, c));
        }
        printf("%d\n", MST());
        scanf("%d %d", &n, &m);
        REP(i, 0, n + 1){
            graph[i].clear();
        }
    }
}