#include <iostream>
#include<cstdio>
#include<algorithm>
#include<string>
#include<cstring>
#include<vector>
#define INF (1<<30)
using namespace std;
vector<int> G;
char table[10][1050];
char S[105];
int main()
{
    int T;
    scanf("%d",&T);
    for(int kase=1;kase<=T;kase++)
    {
        scanf("%s",S+1);
        int n=strlen(S+1);
        G.clear();
        G.push_back(S[1]-'0');
        int hd=0;
        for(int i=2;i<=n;i++)
        {
            if(S[i]-'0'==G[hd])
            {
                G.push_back(S[i]-'0');
                ++hd;continue;
            }
            while(G[hd]<S[i]-'0')
            {
                G.push_back(G[hd]+1);
                ++hd;
            }
            while(G[hd]>S[i]-'0')
            {
                G.push_back(G[hd]-1);
                ++hd;
            }
        }
        int height=0;
        for(int i=0;i<G.size();i++)
            height=max(height,G[i]);
        for(int i=0;i<G.size();i++)
            for(int j=1;j<=height;j++)
                if(j<=G[i]) table[j][i]='+';
                else table[j][i]='*';
        for(int i=1;i<=height;i++)
            table[i][G.size()]='\0';
        for(int i=height;i>=1;i--)
            printf("%s\n",table[i]);
    }
    return 0;
}
