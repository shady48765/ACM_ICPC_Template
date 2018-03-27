#include <iostream>
#include<string>
using namespace std;
string S;
int ten[11];
int solve()
{
    int len=S.size();
    int pre=0,lst=0;
    for(int i=len/2-1;i>=0;i--)
    {
        pre*=10;
        pre+=(S[i]-'0');
    }
    for(int i=len/2+len%2;i<len;i++)
    {
        lst*=10;
        lst+=(S[i]-'0');
    }
   // cout<<"####"<<" "<<pre<<" "<<lst<<endl;
    if(pre==lst) return 0;
    if(pre>lst) return pre-lst;
    else
    {
        if(len%2)
        {
            if(S[len/2]!='9')
                return ten[len/2]+pre-lst;
            else
            {
                for(int i=len/2;i>=0;i--)
                {
                    if(S[i]=='9') S[i]='0';
                    else {S[i]=S[i]+1;break;}
                }
                pre=0,lst=0;
                for(int i=len/2-1;i>=0;i--)
                {
                    pre*=10;
                    pre+=(S[i]-'0');
                }
                for(int i=len/2+len%2;i<len;i++)
                {
                    lst*=10;
                    lst+=(S[i]-'0');
                }
                return ten[len/2]+pre-lst;
            }
        }
        else
        {
            if(S[len/2-1]!='9')
            {
                int ans=ten[len/2]-lst;
                S[len/2-1]+=1;
                pre=0;
                for(int i=len/2-1;i>=0;i--)
                {
                    pre*=10;
                    pre+=(S[i]-'0');
                }
                return ans+pre;
            }
            else
            {
                for(int i=len/2-1;i>=0;i--)
                {
                    if(S[i]=='9') S[i]='0';
                    else {S[i]=S[i]+1;break;}
                }
                pre=0,lst=0;
                for(int i=len/2-1;i>=0;i--)
                {
                    pre*=10;
                    pre+=(S[i]-'0');
                }
                for(int i=len/2+len%2;i<len;i++)
                {
                    lst*=10;
                    lst+=(S[i]-'0');
                }
                return ten[len/2]+pre-lst;
            }
        }
    }

}
int main()
{
    ten[0]=1;
    for(int i=1;i<=10;i++) ten[i]=ten[i-1]*10;
    while(cin>>S)
    {
        if(S.size()==1) break;
        cout<<solve()<<endl;
    }
    return 0;
}
