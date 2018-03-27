#include <iostream>
#include<string>
using namespace std;
string S[105];
int main()
{
    int n;
    while(cin>>n&&n)
    {
        int cnt=0;
        for(int i=1;i<=n;i++) cin>>S[i];
        while(1){
        bool ok=true;
        for(int i=1;i<=n&&ok;i++)
            for(int j=i+1;j<=n&&ok;j++)
                if(S[i]==S[j]) ok=false;
        for(int i=1;i<=n&&ok;i++)
            if(S[i].size()==0) ok=false;
        if(ok) cnt++;else break;
        for(int i=1;i<=n;i++) S[i].erase(0,1);
        }
        cout<<max(cnt-1,0)<<endl;
    }
    return 0;
}
