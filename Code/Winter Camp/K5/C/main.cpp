#include <iostream>
#include <vector>
#include<algorithm>
using namespace std;
int n,t,now,ti,b[2000];
long long ans,re;
struct Node{
    int s,cnt;
}tmp;
bool cmp(Node a,Node b){
    return a.cnt<b.cnt;
}
vector<Node> a;
int main()
{
    ti=10000;
    cin>>n;
    for (int q=1;q<=n;q++) cin>>b[q];
    for (int q=1;q<=n;q++) b[q]=-b[q];

    for (int q=1;q<=n;q++) b[q]=-b[q];
    while (ti--){
    random_shuffle(b+1,b+1+n);
    a.clear();ans=0;
    for (int q=1;q<=n;q++){
         //   cout<<"step"<<q<<endl;
        t=b[q];
        if (t>5) ans+=t-5,t=5;
        now=1<<(q-1);
        while (t){
            int flag=0;
            sort(a.begin(),a.end(),cmp);
       //     cout<<"sortend now="<<now<<endl;
            for (int i=0;i<a.size();i++){
                tmp=a[i];
             //  cout<<"s="<<tmp.s<<endl;
                if ((tmp.s&now)==0) {
             //       cout<<"s="<<tmp.s<<endl;
                    t--;
                    now=(now|a[i].s);
                    tmp.s=a[i].s|(1<<(q-1));
                    tmp.cnt++;
                    a.push_back(tmp);
                    a[i].s=(1<<7)-1;
                    flag=1;
                //    cout<<tmp.s<<" "<<tmp.cnt<<endl;
                    break;
                }
            }
          //  cout<<flag<<endl;
            if (flag==0) break;
        }
        for (int i=1;i<=t;i++){
            tmp.cnt=1;
            tmp.s=1<<(q-1);
            a.push_back(tmp);
            ans++;
        }

    //  cout<<"ans="<<ans<<endl;
   //   for (int r=0;r<a.size();r++){ cout<<a[r].s<<endl;}
    }
    if (re==0) re=ans;else re=min(ans,re);
}
    cout<<re<<endl;
    return 0;
}
