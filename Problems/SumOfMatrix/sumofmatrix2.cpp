#include<stdio.h>
int s[301][301],n,m,k;
int main(){
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++){
            int a;
            scanf("%d", &a);
            s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i-1][j-1] + a;
        }
    }
    scanf("%d", &k);
    for (int i = 1; i <= k; i++){
        int x1,y1,x2,y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        printf("%d\n", s[x2][y2] - s[x1-1][y2] - s[x2][y1-1] + s[x1-1][y1-1]);
    }
    return 0;
}
