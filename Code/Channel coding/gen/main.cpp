#include <iostream>
#include<cstdio>
#include<algorithm>
#include<ctime>
using namespace std;
char S[55][20];
int n,m,d;
int main()
{
    freopen("24.out","w",stdout);
    srand(time(NULL));
    n=rand()%50;
    m=rand()%15+1;
    d=rand()%m+1;
    printf("%d %d %d\n",n,m,d);
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
    {
        int x=rand()%10+1;
        //if(x<=10)
        S[i][j]='?';
        //if(x>=9) S[i][j]='1';
        //if(x<=2) S[i][j]='0';
    }
    for(int i=0;i<n;i++) S[i][m]=0;
    for(int i=0;i<n;i++)
        printf("%s\n",S[i]);
    return 0;
}
