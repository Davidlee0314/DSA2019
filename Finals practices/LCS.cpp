//
// Created by 李得瑋 on 2019-05-31.
//

#include<cstdio>
#include<vector>
using namespace std;
#define REP(i, j, k) for(int i = j; i < k; i++)

int ind = 0;

void lcs(const char* a, const char* b, int n, int m){
    int mx [n + 1][m + 1];
    REP(i, 0, n + 1){
        REP(j, 0, m + 1){
            if(i == 0 || j == 0){
                mx[i][j] = 0;
            }else if(a[i - 1] == b[j - 1]){
                mx[i][j] = mx[i - 1][j - 1] + 1;
            }else{
                mx[i][j] = max(mx[i - 1][j], mx[i][j - 1]);
            }
        }
    }
    int index = mx[n][m];
    if(index > 0){
        char res[index + 1];
        res[index] = '\0';

        int i = n, j = m;
        while(i > 0 && j > 0){
            if(a[i - 1] == b[j - 1]){
                res[index - 1] = a[i - 1];
                index--;
                i--;
                j--;
            }else if(mx[i - 1][j] > mx[i][j - 1]){
                i--;
            }else{
                j--;
            }
        }
        if(ind == 0){
            printf("%s", res);
        }else{
            printf("\n%s", res);
        }
    }else{
        if(ind == 0){
            printf("*");
        }else{
            printf("\n*");
        }
    }
}

int main(){
    int T = 0;
    scanf("%d", &T);
    REP(i, 0, T){
        int n = 0, m = 0;
        scanf("%d %d", &n, &m);
        char a[n + 1]; char b[m + 1];

        scanf("%s", a); scanf("%s", b);
        lcs(a, b, n, m);
        ind++;
    }
    return 0;
}