#include<algorithm>
#include<map>
#include<vector>
#include<cstring>
#include<cstdio>
#include<iostream>
#include<string>
using namespace std;
char buff[200];
string name1,v,name2;
int p1,p2,n,m,ucnt;
map<string,int> mp;
int three[21];
int des[15];
struct match_unknown
{
    string name1,name2;
    match_unknown(){}
    match_unknown(string a,string b):name1(a),name2(b){}
};
int additional_table[22];
struct team
{
    string name;
    int score;
    int id;
    int low,high;
    team(){}
    team(string name,int score,int id):name(name),score(score),id(id){low=999;high=-999;}
};
vector<match_unknown> U;
vector<team> T;
bool cmp(team a,team b)
{
    return a.score+additional_table[a.id]>b.score+additional_table[b.id];
}
bool cmp2(team a,team b)
{
    return a.id<b.id;
}
void getrank()
{
    sort(T.begin(),T.end(),cmp);
   // printf("add\n");
   // for(int i=0;i<n;i++)
  //      printf("%d ",additional_table[i]);
  //  printf("\n");
  ////  for(int i=0;i<n;i++)
  //      cout<<T[i].name<<" "<<T[i].score+additional_table[T[i].id]<<" ";
 //   cout<<endl;
    for(int i=0;i<T.size();i++)
    {
        int j=i;
        while(j-1>=0&&T[j-1].score+additional_table[T[j-1].id]==T[i].score+additional_table[T[i].id]) j--;
        T[i].low=min(T[i].low,j+1);
        T[i].high=max(T[i].high,j+1);
    }
}
void out(int x)
{
    if(x==1) printf("1st");
    else if(x==2) printf("2nd");
    else if(x==3) printf("3rd");
    else printf("%dth",x);
}
int main()
{
    int f=0;
    three[0]=1;
    for(int i=1;i<=14;i++) three[i]=three[i-1]*3;
    while(scanf("%d%d",&n,&m)&&(n+m))
    {
        if(f)printf("\n");
        f++;
        U.clear();T.clear();mp.clear();ucnt=0;
        for(int i=0;i<n;i++)
        {
            scanf("%s",buff);
            name1=buff;
            mp[name1]=i;
            T.push_back(team(name1,0,i));
        }
        for(int i=1;i<=m;i++)
        {
            scanf("%s",buff);
            name1=buff;
            scanf("%s",buff);
            scanf("%s",buff);
            buff[strlen(buff)-1]=0;
            name2=buff;
            scanf("%d%d",&p1,&p2);
            if(p1==-1)
            {
                U.push_back(match_unknown(name1,name2));ucnt++;
            }
            else if(p1>p2)
            {
                T[mp[name1]].score+=3;
            }
            else if(p1<p2)
            {
                T[mp[name2]].score+=3;
            }
            else
            {
                T[mp[name1]].score+=1;T[mp[name2]].score+=1;
            }
        }
       // printf("origin\n");
 //       for(int i=0;i<n;i++)
     //       printf("%d ",T[i].score);
    //    printf("\n");
        for(int S=0;S<three[ucnt];S++)
        {
            int tt=S;
            for(int q=1;q<=ucnt;q++)
                des[q]=tt%3,tt/=3;
            memset( additional_table,0,sizeof(additional_table));
            for(int q=1;q<=ucnt;q++)
                if(des[q]==0){
                    additional_table[mp[U[q-1].name1]]+=1;
                    additional_table[mp[U[q-1].name2]]+=1;
                }
                else if(des[q]==1){
                    additional_table[mp[U[q-1].name1]]+=3;
                    additional_table[mp[U[q-1].name2]]+=0;
                }else if(des[q]==2){
                    additional_table[mp[U[q-1].name1]]+=0;
                    additional_table[mp[U[q-1].name2]]+=3;
                }
            getrank();
        }
        if(ucnt==0) getrank();
        sort(T.begin(),T.end(),cmp2);
        for(int i=0;i<n;i++){
                printf("Team %s can finish as high as ",T[i].name.c_str());
        out(T[i].low);
        printf(" place and as low as ");
        out(T[i].high);
        printf(" place.\n");
        }
    }
    return 0;
}
