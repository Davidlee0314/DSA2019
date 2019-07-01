#include <cstdio>
#include <limits>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
#define REP(i, j, k) for(int i = j; i < k; i++)
using namespace std;
const int N = 100500;
typedef long long ll;
typedef pair<long long, int> P;
long long inf = numeric_limits<long long>::max();

struct edge{
    int to;
    long long cost;
    edge(int v, long long c){
        to = v; cost = c;
    }
};
vector<edge> graph[N];
int m, n, st, en;
long long dist1[N], dist2[N];

long long dijkstra(){
    REP(i, 0, n) {
        dist1[i] = inf;
        dist2[i] = inf;
    }
    dist1[st] = 0;
    priority_queue<P, vector<P>, greater<>>Q;
    Q.push(P(0, st));

    while(!Q.empty()){
        P p = Q.top(); Q.pop();
        int v = p.second; long long c = p.first;
        if(dist2[v] < c) continue;
        for(int i = 0; i < graph[v].size(); i++){
            edge &e = graph[v][i];
            long long d2 = c + e.cost;
            //如果d2比較小
            if(dist1[e.to] > d2){
                //swap
                swap(dist1[e.to], d2);
                Q.push(P(dist1[e.to], e.to));
            }
            //如果d2介於中間
            if(dist2[e.to] > d2 && dist1[e.to] < d2){
                dist2[e.to] = d2;
                Q.push(P(dist2[e.to], e.to));
            }
        }
    }
    return dist2[en] - dist1[en];
}

int main() {
    int t;
    scanf("%d", &t);
    REP(r, 0, t) {

        int a, b; long long c;
        scanf("%d %d\n%d %d", &n, &m, &st, &en);
        REP(i, 0, m) {
            scanf("%d %d %lld", &a, &b, &c);
            edge e = edge(b, c);
            graph[a].push_back(e);
        }
        if(r == 0)
            printf("%lld", dijkstra());
        else
            printf("\n%lld", dijkstra());
        REP(i, 0, n){
            graph[i].clear();
        }
    }
}