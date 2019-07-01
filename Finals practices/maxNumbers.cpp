#include <cstdio>
#include <algorithm>
using namespace std;
#define LOOP(i, j, k) for(int i = j; i < k; i++)
typedef long long ll;
const ll INF = 1LL << 60;
const int N = 1000000;
ll a[N], b[N], c[N];

int main() {
    int n = 0;
    scanf("%d\n", &n);
    LOOP(i, 0, n) {
        if (i == 0) scanf("%lld", &a[i]);
        else scanf(" %lld", &a[i]);
    }

    //i=2~N-2時，B[ i ]=max(A[ i ], B[ i-1 ], A[ i ]+B[ i-1 ])
    b[0] = a[0];
    for(int i = 1; i < n; i++) {
        ll temp = max(a[i], b[i - 1]);
        ll temp2 = a[i] + b[i - 1];
        b[i] = max(temp, temp2);
    }

    //C[3]=A[1]+A[3]，i=4~N時，C[ i ]=max(C[ i-1 ], B[ i-2 ])+A[ i ]
    c[0] = -INF; c[1] = -INF;
    LOOP(i, 2, n){
        c[i] = max(c[i - 1], b[i - 2]) + a[i];
    }
    ll ans = -INF;
    for(int i = 0; i < n; i++) {
        ans = max(ans, c[i]);
    }
    printf("%lld", ans);
    return 0;
}