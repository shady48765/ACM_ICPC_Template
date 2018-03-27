#include <iostream>
#include<map>
#include<algorithm>

using namespace std;
struct Node{
    int a,b,del;
}tmp,b[1001000];
int a[1100];
int n,num,ans;
bool cmp(Node a,Node b){
    return a.del<b.del||a.del==b.del && a.a<b.a;
}
map<pair<int,int>,int> mp;
map<pair<int,int>,int> ::iterator it;
int main()
{
int ttt;cin>>ttt;
while (ttt--)
{
    cin>>n;//cout<<n<<endl;
    for (int i=1;i<=n;i++) a[i]=i;//cin>>a[i];
    sort(a+1,a+1+n);
    mp.clear();num=0;
    for (int i=1;i<=n;i++){
        for (int j=i+1;j<=n;j++){
            Node tmp;
            tmp.a=i;
            tmp.b=j;
            tmp.del=a[j]-a[i];
            b[++num]=tmp;
        //    cout<<i<<" "<<j<<" "<<a[j]-a[i]<<endl;
        }
    }
    ans=0;
    sort(b+1,b+1+num,cmp);
    for (int i=1;i<=num;i++){
  //      cout<<b[i].a<<" "<<b[i].b<<" "<<b[i].del<<endl;
    }
    cout<<endl;
    memset(f,0,sizeof(f));
    for (int i=1;i<=num;i++){
        it=mp.find(make_pair(b[i].a,b[i].del));

        if (it==mp.end()){
            mp[make_pair(b[i].b,b[i].del)]=2;
            ans=max(ans,2);
 //           cout<<"Can't find!"<<endl;
        }else {
            mp[make_pair(b[i].b,b[i].del)]=it->second+1;
            ans=max(ans,it->second+1);
 //0           cout<<it->first.first<<" "<<it->first.second<<" "<<it->second<<endl;
        }

    }
    cout<<ans<<endl;
}
    return 0;
}
