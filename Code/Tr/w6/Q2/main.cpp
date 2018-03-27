#include <iostream>
#include<string>
#include<cstring>
using namespace std;
string S;
bool f;
int l,r;
int n;
bool A[10010];
void deal()
{
    int i=0,j;
    for(j=0;j<S.size();j++)
    {
        if(S[j]==',')
        {
            f=false;
            for(int k=i;k<j;k++)
                if(S[k]=='-') f=true;
            if(!f)
            {
                int tp=0;
                for(int k=i;k<j;k++)
                {
                    tp*=10;tp+=(S[k]-'0');
                }
                A[tp]=true;
            }
            else
            {
                l=r=0;
                int tt;
                for(tt=i;tt<j;tt++)
                {
                    if(S[tt]=='-') break;
                }
                for(int k=i;k<tt;k++)
                {
                    l*=10;l+=(S[k]-'0');
                }
                for(int k=tt+1;k<j;k++)
                {
                    r*=10;r+=(S[k]-'0');
                }
                if(l<=r)
                {
                    for(int k=l;k<=r&&k<=n;k++) A[k]=true;
                }
            }
        i=j+1;
        }
    }
            j=S.size();
            f=false;
            for(int k=i;k<j;k++)
                if(S[k]=='-') f=true;
            if(!f)
            {
                int tp=0;
                for(int k=i;k<j;k++)
                {
                    tp*=10;tp+=(S[k]-'0');
                }
                A[tp]=true;
            }
            else
            {
                l=r=0;
                int tt;
                for(tt=i;tt<j;tt++)
                {
                    if(S[tt]=='-') break;
                }
                for(int k=i;k<tt;k++)
                {
                    l*=10;l+=(S[k]-'0');
                }
                for(int k=tt+1;k<j;k++)
                {
                    r*=10;r+=(S[k]-'0');
                }
                if(l<=r)
                {
                    for(int k=l;k<=r&&k<=n;k++) A[k]=true;
                }
            }
}
int main()
{
    while(cin>>n)
    {
        memset(A,false,sizeof(A));
        if(n==0) break;
        cin>>S;
        deal();
        int cnt=0;
        for(int i=1;i<=n;i++) if(A[i]) ++cnt;
        cout<<cnt<<endl;
    }
    return 0;
}
