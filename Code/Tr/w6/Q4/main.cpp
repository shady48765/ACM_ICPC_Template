#include <iostream>
#include<algorithm>
using namespace std;
int a,b,c,t,s;
int main()
{
    int n;
    while(cin>>n&&n)
    {
        s=0;
        a=b=c=9999999;
        for(int i=1;i<=n;i++)
        {
            cin>>t;
            s+=t;
            a=min(a,50/t);
            b=min(b,60/t);
            c=min(c,70/t);
        }
        a++,b++,c++;
        if(s*2>50) a=0;
        if(s*2>60) b=0;
        if(s*2>70) c=0;
        cout<<a<<" "<<b<<" "<<c<<endl;
    }
    return 0;
}
