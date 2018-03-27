#include <cstdio>
#include<vector>
#include<algorithm>
using namespace std;
vector<int> S[5010];
int sum[5010][55];
int main()
{
    int n,k,x;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&k);
        for(int j=0;j<k;j++)
        {
            scanf("%d",&x);
            S[i].push_back(x);
        }
        sort(S[i].begin(),S[i].end());
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<S[i].size();j++)
            sum[i][S[i][j]]++;
        for(int j=1;j<=50;j++)
            sum[i][j]+=sum[i][j-1];
    }
    int Win=0;
    int tp;
    for(int i=1;i<=n-1;i++)
        for(int j=i+1;j<=n;j++)
    {
        int cnt=0;
        for(int k=0;k<S[j].size();k++)
        {
            if(k==0)
                tp=sum[i][S[j][k]];
            else
                tp=sum[i][S[j][k]]-sum[i][S[j][k-1]];
            if(tp)
                cnt++;
        }
        if(cnt%2) Win++;
    }
    printf("%d",Win);
    return 0;
}
