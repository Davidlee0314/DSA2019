//
// Created by 李得瑋 on 2019-06-16.
//

#include <queue>
#include <cstdio>
#include <vector>
#include <algorithm>
#define REP(i, j, k) for(int i = j; i < k; i++)
using namespace std;
typedef long long ll;
typedef pair<ll, int> P;
ll inf = 1LL << 60;
const int N = 300006;

ll dist[N]; P bst[N]; bool visited[N];
struct edge{
    int to;
    long long cost;
    edge(int v, long long c){
        to = v; cost = c;
    }
};
vector<edge> ed;
vector<int> graph[N];
int n, m, st, num = 0;

void SPT(){
    fill(visited, visited + n + 1, false);
    fill(dist, dist + n + 1, inf);
    REP(i, 1, n + 1){
        bst[i].first = inf;
    }
    priority_queue<P, vector<P>, greater<>>Q;
    Q.push(P(0, st));
    dist[st] = 0; bst[st].first = 0;

    while(!Q.empty()){
        P p = Q.top(); Q.pop();
        int v = p.second; ll c = p.first;
        if(visited[v]) continue;
        visited[v] = true;
        for(int i = 0; i < graph[v].size(); i++){
            edge &e = ed[graph[v][i]];
            if(dist[e.to] > dist[v] + e.cost){
                dist[e.to] = dist[v] + e.cost;
                Q.push(P(dist[e.to], e.to));
                bst[e.to].first = e.cost;
                bst[e.to].second = graph[v][i];
            }else if(dist[e.to] == dist[v] + e.cost && bst[e.to].first > e.cost){
                bst[e.to].first = e.cost;
                bst[e.to].second = graph[v][i];
            }
        }
    }
}

int main(){
    scanf("%d %d", &n, &m);
    int a, b, c;
    REP(i, 0, m){
        scanf("%d %d %d", &a, &b, &c);
        ed.emplace_back(edge(b, c));
        graph[a].push_back(num); num++;
        ed.emplace_back(edge(a, c));
        graph[b].push_back(num); num++;
    }
    scanf("%d", &st);
    SPT();
    ll ans = 0;
    REP(i, 1, n + 1){
        ans += bst[i].first;
    }
    printf("%lld\n", ans);
    REP(i, 1, n + 1){
        if(i != st) printf("%d ", bst[i].second / 2 + 1);
    }
    return 0;
}