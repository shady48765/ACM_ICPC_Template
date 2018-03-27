#include <iostream>
#include <cstdio>
#define maxn 1000

using namespace std;

int l[maxn][maxn],r[maxn][maxn];

int main()
{
    int h,w,n;
    scanf("%d%d%d",&h,&w,&n);
    for (int k=1;k<=w;k++)
        if ((k+1)%2==0) l[1][k]=k,r[1][k]=k+1;
    for (int i=1;i<=w;i++)
        for (int j=1;j<=h;j++)
        if ((i+j)%2==0)
        {
            if (j==1) l[i][j]=r[i-2][2];else l[i][j]=l[i-1][j-1];
            if (j==w) r[i][j]=l[i-2][w-1];else r[i][j]=r[i-1][j+1];
        }
    for (int k=1;k<=w;k++)
        if ((k+h)%2==0)
        {
            int i=h,j=k;
            printf("( %d , %d ): %d , %d   ",i,j,l[i][j],r[i][j]);
        }
    return 0;
}
