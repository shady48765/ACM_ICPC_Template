#include <cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<string>
using namespace std;
string S[10],ans;
int A[10];
void add(int x)
{
    int i;
    if(ans.size()>S[x].size())
        i=ans.size()-S[x].size();
    else
        i=0;
    for(;i<ans.size();i++)
    {
        bool ok=true;
        for(int j=i,k=0;j<ans.size();j++,k++)
            if(ans[j]!=S[x][k]) ok=false;
        if(ok) break;
    }
    for(int j=ans.size()-i;j<S[x].size();j++)
        ans.push_back(S[x][j]);
}
int main()
{
    int T,n;
    cin>>T;
    for(int kase=1;kase<=T;kase++)
    {
        cin>>n;
        for(int i=0;i<n;i++) cin>>S[i],A[i]=i;
        int res=9999999;
        do
        {
            ans="";
            for(int i=0;i<n;i++)
                add(A[i]);
            res=min(res,(int)ans.size());

        }while(next_permutation(A,A+n));
        cout<<"Case "<<kase<<": "<<res<<endl;
    }
    return 0;
}
