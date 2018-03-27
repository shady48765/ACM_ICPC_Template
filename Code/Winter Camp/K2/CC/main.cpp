#include <cstdio>
#include<cstring>
#include<algorithm>
#include<map>
#include<vector>
using namespace std;
char s[200010],t[200010],tp[200010],ttp[200010];
int l=0,r=0,lens,lent,lentp;
int next[200010];
vector<int> G;
map<int,int> mp;
bool special_check()
{
    int cnt=0;
    for(int i=1;i<=lent;i++) if(t[i]=='b') ++cnt;
    if(cnt==0)
    {
        int min_=9999999;
        for(int i=0;i<G.size();i++)
        {
            int ts=G[i],now=0;
            if(i!=G.size()-1)
            while(ts<lent)
            {
                ts=ts*2+1;
                now++;
            }
            else
            while(ts<lent)
            {
                ts=ts*2;
                now++;
            }
            min_=min(min_,now);
        }
        printf("%d",min_);
        return true;
    }
    else if(cnt==1)
    {
        int ccc=0;
        for(int i=1;i<=lens;i++)
            if(s[i]=='b') ccc++;
        if(ccc==0)
        {
            printf("-1");return true;
        }
        int min_=9999999;
        for(int i=0;i<G.size()-1;i++)
        {
            int ts1=G[i],ts2=G[i+1],now=0;
            if(i!=G.size()-2)
            while(ts1<l||ts2<r)
            {
                ts1=ts1*2+1;
                ts2=ts2*2+1;
                now++;
            }
            else
            while(ts1<l||ts2<r)
            {
                ts1=ts1*2+1;
                ts2=ts2*2;
                now++;
            }
            min_=min(min_,now);
        }
        printf("%d",min_);
        return true;
    }
    return false;
}
void deal()
{
    int ct=0;
    for(int i=1;i<=lens;i++)
    {
        if(s[i]=='b')
        {
            G.push_back(ct);
            ct=0;
        }
        else
        {
            ++ct;
        }
    }
    G.push_back(ct);
    int nnnn=0;
    for(int i=1;i<=lens;i++)
    {
        if(s[i]=='b') mp[i]=nnnn++;
    }
    int i,j;
    for(i=1;i<=lent;i++)
        if(t[i]=='b') break;
    l=i-1;
    for(j=lent;j>=1;j--)
        if(t[j]=='b') break;
    r=lent-i;
    for(int k=i;k<=j;k++)
        tp[k-i+1]=t[k];
    lentp=j-i+1;
}
bool iT()
{
    int now=0;
    int j;
    for(int i=1;i<=lentp;)
    {
        ttp[++now]='b';
        for(j=i+1;j<=lentp;j+=2)
        {
            if(tp[j]=='b') return false;
            if(tp[j]=='a'&&tp[j+1]=='a') ttp[++now]='a';
            else if(tp[j]=='a'&&tp[j+1]=='b')
            {
                ttp[++now]='a';
                i=j;
                break;
            }
        }
        ++i;
    }
    for(int i=1;i<=now;i++) tp[i]=ttp[i];
    tp[now+1]='0';
    lentp=now;
    return true;
}
int main()
{
    scanf("%s%s",&s+1,&t+1);
    lens=strlen(s+1);
    lent=strlen(t+1);
    deal();
    int i,j;
    if(!special_check())
    {
        int time_=0,ans;
        bool ok=false;
        do{
        j=0;
        for (int i=2;i<=lentp;i++){
            while (j!=0 && tp[j+1]!=tp[i]) j=next[j];
            if (tp[i]==tp[j+1]) j++;
            next[i]=j;
        }
        j=0;
        for (int i=1;i<=lens;i++){
            while (j!=0 && tp[j+1]!=s[i]) j=next[j];
            if (tp[j+1]==s[i]) j++;
            if (j==lentp) {
                int right=G[mp[i]+1];
                int left=G[mp[i-lentp+1]];
                if(right>=r&&left>=l)
                {
                    printf("%d",time_);
                    return 0;
                }
                j=next[j];
            }
        }

            ++time_;
        }while(iT());
    }
    return 0;
}
