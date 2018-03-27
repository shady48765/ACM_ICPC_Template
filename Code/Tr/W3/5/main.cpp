#include<iostream>
#include<cstring>
#define MOD 1000000000000
using namespace std;
typedef long long LL;
long long ten[20];
long long k1;
int A[20];
long long multi(long long a,long long b,long long mod)
{
    int A[30],B[30],C[30],d=0;
    while(mod>1) d++,mod/=10;
    int la=0,lb=0;
    memset(C,0,sizeof(C));
    memset(A,0,sizeof(A));
    memset(B,0,sizeof(B));
    while(a)
    {
        A[++la]=a%10;
        a/=10;
    }while(b)
    {
        B[++lb]=b%10;
        b/=10;
    }
    for(int i=1;i<=lb;i++)
        for(int j=1;j<=la;j++)
            C[i+j-1]+=B[i]*A[j];
    for(int i=1;i<=d;i++){
        C[i+1]+=C[i]/10;C[i]%=10;
    }
    long long res=0;
    for(int i=d;i>=1;i--)
    {
        res*=10;
        res+=C[i];
    }
    return res;
}
long long fastpow(LL base,LL pow,LL mod)
{
    long long res=1;
    while(pow!=0)
    {
        if(pow%2)
            res=multi(res,base,mod);
            //res*=base,res%=mod;
        //base*=base,base%=mod;
        base=multi(base,base,mod);
        pow/=2;
    }
    return res;
}
long long get(int d)
{
    long long res=0;
    for(int i=d;i>=1;i--)
    {
        res*=10;
        res+=A[i];
    }
    return res;
}
bool ok;
void dfs(int d)
{
    if(ok) return;
    if(d==13)
    {
        for(int i=12;i>=1;i--) cout<<A[i];
        ok=true;
    }
    for(int i=0;i<10;i++)
    {
        A[d]=i;
        LL temp=get(d);
        //cout<<temp<<endl;
        if(fastpow(k1,temp,ten[d])==temp) dfs(d+1);
    }
}
int main()
{
    //cout<<multi(78,37,10000);
    ten[0]=1;
    for(int i=1;i<=12;i++) ten[i]=ten[i-1]*10;
    int cao=0;
    while(cin>>k1&&k1)
    {//Case 2: Public Key = 99 Private Key = 817245479899
        ++cao;
        cout<<"Case "<<cao<<": Public Key = "<<k1<<" Private Key = ";
        ok=false;//cout<<"now"<<endl;
        for(int i=0;i<10&&!ok;i++){
        A[1]=i;
        dfs(2);
        }
        //cout<<"end"<<endl;
        cout<<endl;
       // cout<<fastpow(78,864916096,1000000000);
    }
    return 0;
}
