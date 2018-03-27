#include <iostream>
#define MOD 1000000000000
using namespace std;
typedef long long LL;
int main()
{
    LL a=78;
    LL res=1;

    long long now,pre=0;
    for(long long i=1;i<=96;i++)
    {
        res*=a;
        res%=MOD;
    }
    cout<<res<<endl;
    for(int i=2;i*i<=329209;i++)
        if(329209%i==0) cout<<i<<endl;
    return 0;
}
