#include <cstdio>
#include<algorithm>
#include<stack>
#include<cstring>
#include<map>
#include<ctime>
using namespace std;
char S[2][105];
stack<char> G[2];
map<char,unsigned long long> mp;
void deal(int d)
{
    srand((int)time(0));
    int n;
    n=strlen(S[d]);
    stack<char> tp;
    stack<char> ma;
    for(int i=0;i<n;i++)
    {
        if(S[d][i]<='Z'&&S[d][i]>='A') S[d][i]=S[d][i]-'A'+'a';

        if(S[d][i]==' '||S[d][i]=='\t')continue;
        else if(S[d][i]<='z'&&S[d][i]>='a')
        {
            ma.push(S[d][i]);
        }
        else if(S[d][i]<='9'&&S[d][i]>='0')
        {
            ma.push(S[d][i]);
        }
        else if(S[d][i]=='+'||S[d][i]=='-'||S[d][i]=='*')
        {
            if(S[d][i]=='*')
            {
                while(!tp.empty()&&tp.top()=='*')
                {
                    ma.push(tp.top());
                    tp.pop();
                }
                tp.push('*');
            }
            else
            {
                while(!tp.empty()&&(tp.top()=='+'||tp.top()=='-'||tp.top()=='*'))
                {
                    ma.push(tp.top());
                    tp.pop();
                }
                tp.push(S[d][i]);
            }
        }
        else if(S[d][i]=='(')
        {
            tp.push('(');
        }
        else if(S[d][i]==')')
        {
            while(!tp.empty()&&tp.top()!='(')
            {
                ma.push(tp.top());
                tp.pop();
            }
            tp.pop();
        }
    }
    while(!tp.empty())
    {
        ma.push(tp.top());
        tp.pop();
    }
    while(!ma.empty()){
        G[d].push(ma.top());
        ma.pop();
    }
}
bool check()
{
    stack<char> op1(G[0]),op2(G[1]);
    stack<unsigned long long> tp1,tp2;
    unsigned long long res1=0,res2=0;
    for(char x='a';x<='z';x++) mp[x]=rand()%1331;
    for(char x='0';x<='9';x++) mp[x]=x-'0';
   /* while(!G[0].empty())
    {
        printf("%c",G[0].top());G[0].pop();
    }
    printf("\n");while(!G[1].empty())
    {
        printf("%c",G[1].top());G[1].pop();
    }
    printf("\n");*/
    while(!op1.empty())
    {
        if(op1.top()=='*')
        {
            op1.pop();
            int a=tp1.top();tp1.pop();
            int b=tp1.top();tp1.pop();
            tp1.push(a*b);
        }
        else if(op1.top()=='+')
        {
            op1.pop();
            int a=tp1.top();tp1.pop();
            int b=tp1.top();tp1.pop();
            tp1.push((a+b));
        }
        else if(op1.top()=='-')
        {
            op1.pop();
            int a=tp1.top();tp1.pop();
            int b=tp1.top();tp1.pop();
            tp1.push(b-a);
        }
        else{
            tp1.push(mp[op1.top()]);
            op1.pop();
        }
    }
    res1=tp1.top();
    while(!op2.empty())
    {
        if(op2.top()=='*')
        {
            op2.pop();
            int a=tp2.top();tp2.pop();
            int b=tp2.top();tp2.pop();
            tp2.push(a*b);
        }
        else if(op2.top()=='+')
        {
            op2.pop();
            int a=tp2.top();tp2.pop();
            int b=tp2.top();tp2.pop();
            tp2.push(a+b);
        }
        else if(op2.top()=='-')
        {
            op2.pop();
            int a=tp2.top();tp2.pop();
            int b=tp2.top();tp2.pop();
            tp2.push(b-a);
        }
        else{
            tp2.push(mp[op2.top()]);
            op2.pop();
        }
    }
    res2=tp2.top();
 //   printf("%llu %llu\n",res1,res2);
    return res1==res2;
}
int main()
{
   // freopen("data.in","r",stdin);
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%s%s",S[0],S[1]);
        while(!G[0].empty()) G[0].pop();
        while(!G[1].empty()) G[1].pop();
        deal(0);
        deal(1);
        if(check())
            printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}
