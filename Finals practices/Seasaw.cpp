//
// Created by 李得瑋 on 2019-05-31.
//

#include<cstdio>
#include<vector>
using namespace std;
#define REP(i, j, k) for(long long i = j; i < k; i++)

int main(){
    int N = 0;
    scanf("%d",&N);

    vector<int> arr;
    long long tto = 0, to = 0;
    REP(i, 0, N){
        int temp = 0;
        scanf("%d", &temp);
        to += temp;
        tto += temp * i;
        arr.push_back(temp);
    }
    REP(i, 0, N / 2 + 1){
        if(i == 0){
            if(tto % to == 0){
                printf("%d %lld", 0, tto / to);
                break;
            }
        }else{
            tto = tto - arr[i - 1] * (i - 1) - arr[N - i] * (N - i)
                    + arr[i - 1] * (N - i) + arr[N - i] * (i - 1);
            if(tto % to == 0){
                printf("%d %lld", i, tto / to);
                break;
            }
        }
    }
    return 0;
}