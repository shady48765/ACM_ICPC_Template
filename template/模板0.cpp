模板
1.莫队算法
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#define maxn 55000
#define inf 2147483647
using namespace std;
struct query
{
    int l,r,s,w;
}a[maxn];
int c[maxn];
long long col[maxn],size[maxn],ans[maxn];
int n,m,cnt,len;

long long gcd(long long x,long long  y)
{
    return (!x)?y:gcd(y%x,x);
}

bool cmp(query a,query b)
{
    return (a.w==b.w)?a.r<b.r:a.w<b.w;
}

int main()
{
    //freopen("hose.in","r",stdin);
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++) scanf("%d",&c[i]);
    len=(int)sqrt(m);
    cnt=(len*len==m)?len:len+1;
    for (int i=1;i<=m;i++) 
    {
        scanf("%d%d",&a[i].l,&a[i].r);
        if (a[i].l>a[i].r) swap(a[i].l,a[i].r);
        size[i]=a[i].r-a[i].l+1;
        a[i].w=a[i].l/len+1;
        a[i].s=i;
    }
    sort(a+1,a+m+1,cmp);
    int i=1;
    while (i<=m)
    {
        int now=a[i].w;
        memset(col,0,sizeof(col));
        for (int j=a[i].l;j<=a[i].r;j++) ans[a[i].s]+=2*(col[c[j]]++);
        i++;
        for (;a[i].w==now;i++)
        {
            ans[a[i].s]=ans[a[i-1].s];
            for (int j=a[i-1].r+1;j<=a[i].r;j++)
                ans[a[i].s]+=2*(col[c[j]]++);
            if (a[i-1].l<a[i].l)
                for (int j=a[i-1].l;j<a[i].l;j++) 
                    ans[a[i].s]-=2*(--col[c[j]]);
            else
                for (int j=a[i].l;j<a[i-1].l;j++)
                    ans[a[i].s]+=2*(col[c[j]]++);
        }
    }
    long long all,num;
    for (int i=1;i<=m;i++)
    {
        if (size[i]==1) all=1; else all=size[i]*(size[i]-1);
        num=gcd(ans[i],all);
        printf("%lld/%lld\n",ans[i]/num,all/num);
    }
    return 0;
}    

2.三维偏序
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define maxn 200000
#define inf 2147483647
using namespace std;
struct point{
    int x,y,z,s;
}a[maxn],q1[maxn],q2[maxn];
int f[maxn];
int n,m;
struct bit
{
    int b[maxn];
    void clear(int x){
        for (int i=x;i;i-=(i&-i)) b[i]=0;
    }
    void add(int x,int z){
        for (int i=x;i;i-=(i&-i)) b[i]=max(b[i],z);
    }
    int ask(int x){
        int tmp=0;
        for (int i=x;i<=n;i+=(i&-i)) tmp=max(b[i],tmp);
        return tmp;
    }
}s;

bool cmp1(point a,point b)
{    return a.x>b.x;}

bool cmp2(point a,point b)
{    return a.y>b.y;}

void solve(int l,int r){
    if (l==r) return ;
    int mid=(l+r)>>1;
    solve(l,mid);
    int t1=0,t2=0;
    for (int i=l;i<=mid;i++) q1[++t1]=a[i];
    for (int i=mid+1;i<=r;i++) q2[++t2]=a[i];
    sort(q1+1,q1+t1+1,cmp2);
    sort(q2+1,q2+t2+1,cmp2);
    int i=1;
    for (int j=1;j<=t2;j++){
        for (;q1[i].y>q2[j].y&&i<=t1;i++)
            s.add(q1[i].z,f[q1[i].s]);
        f[q2[j].s]=max(f[q2[j].s],s.ask(q2[j].z)+1);
    }
    for (int i=1;i<=t1;i++)
        s.clear(q1[i].z);
    solve(mid+1,r);
}

int main()
{
    //freopen("3sort.in","r",stdin);
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
        scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].z),a[i].s=i;
    sort(a+1,a+n+1,cmp1);
    for (int i=1;i<=n;i++) f[i]=1;
    solve(1,n);
    int ans=0;
    for (int i=1;i<=n;i++) ans=max(ans,f[i]);
    printf("%d\n",ans);
    return 0;
}

3.网络流sap
int dfs(int now,int flow)
{
    if (now==ed) return flow;
    int sap=0;
    for (int j=last[now];j;j=e[j].next)
    {
        int k=e[j].t;
        if (e[j].val&&dis[now]==dis[k]+1)
        {
            last[now]=j;
            int tmp=dfs(k,min(e[j].val,flow-sap));
            e[j].val-=tmp;
            e[j^1].val+=tmp;
            sap+=tmp;
            if (sap==flow) return sap;
        }
    }
    if (dis[st]>=num) return sap;
    if (!(--gap[dis[now]])) dis[st]=num;
    ++gap[++dis[now]];
    last[now]=fir[now];
    return sap;
}

int main()
{
 	memset(dis,0,sizeof(dis));
  	memset(gap,0,sizeof(gap));
    gap[0]=num;
    for (int i=st;i<=ed;i++) last[i]=fir[i];
    int ans=0;
    while (dis[st]<num) ans+=dfs(st,inf);
}

4.zkw费用流
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<ctime>
#define maxn 6200
#define maxm 52000
#define inf 2147483647
using namespace std;
struct et
{
    int s,t,next,val,cost;
}e[maxm];
int dis[maxn],fir[maxn],q[maxn],v[maxn],sum[maxn],win[maxn],lose[maxn],d[maxn],c[maxn];
bool inque[maxn];
int n,m,tot,st,ed;
long long ans;

void prepare()
{
    for (int i=st;i<=ed;i++) dis[i]=inf;
    int head=0,tail=1;
    q[1]=ed; dis[ed]=0; inque[ed]=1;
    while (head<tail)
    {
        int now=q[++head];
        for (int j=fir[now];j;j=e[j].next)
        {
            int k=e[j].t;
            if (e[j^1].val&&dis[k]>dis[now]+e[j^1].cost)
            {
                dis[k]=dis[now]+e[j^1].cost;
                if (!inque[k]) q[++tail]=k,inque[k]=1;
            }
        }
        inque[now]=0;
    }
}

int dfs(int now,int flow)
{
    if (now==ed)
    {
        ans=ans+(long long)dis[st]*flow;
        return flow;
    }
    v[now]=1;
    int sap=0;
    for (int j=fir[now];j;j=e[j].next)
    {
        int k=e[j].t;
        if (!v[k]&&e[j].val&&dis[now]==dis[k]+e[j].cost)
        {
            int tmp=dfs(k,min(e[j].val,flow-sap));
            e[j].val-=tmp;
            e[j^1].val+=tmp;
            sap+=tmp;
            if (sap==flow) return sap;
        }
    }
    return sap;
}

bool adjust()
{
    int tmp=inf;
    for (int i=st;i<=ed;i++) 
        if (v[i]) for (int j=fir[i];j;j=e[j].next)
        {
            int k=e[j].t;
            if (!v[k]&&e[j].val) tmp=min(tmp,dis[k]+e[j].cost-dis[i]);
        }
    if (tmp==inf) return 0;
    for (int i=st;i<=ed;i++)
        if (v[i]) dis[i]+=tmp;
    return 1;
}

void add(int x,int y,int z,int w)
{
    e[++tot].s=x; e[tot].t=y; e[tot].val=z; e[tot].cost=w; e[tot].next=fir[x]; fir[x]=tot;
    e[++tot].s=y; e[tot].t=x; e[tot].val=0; e[tot].cost=-w; e[tot].next=fir[y]; fir[y]=tot;
}

int main()
{
    scanf("%d%d",&n,&m);
    st=0; ed=n+m+1; tot=1;
    for (int i=1;i<=n;i++)
    {
        scanf("%d%d%d%d",&win[i],&lose[i],&c[i],&d[i]);
        sum[i]=win[i]+lose[i];
    }
    int x,y;
    for (int i=1;i<=m;i++)
    {
        scanf("%d%d",&x,&y);
        add(st,i,1,0);
        add(i,m+x,1,0);
        add(i,m+y,1,0);
        sum[x]++; sum[y]++;
    }
    for (int i=1;i<=n;i++)
        for (int j=win[i]+1;j<=sum[i]-lose[i];j++)
            add(m+i,ed,1,(c[i]+d[i])*(2*j-1)-2*d[i]*sum[i]);
    //for (int i=2;i<=tot;i++) cout<<e[i].s<<' '<<e[i].t<<' '<<e[i].val<<' '<<e[i].cost<<endl;
    //计算初始收益
    for (int i=1;i<=n;i++)
        ans+=c[i]*win[i]*win[i]+d[i]*(sum[i]-win[i])*(sum[i]-win[i]);
    prepare();
    do
        do memset(v,0,sizeof(v));
        while (dfs(st,inf));
    while (adjust());
    printf("%lld\n",ans);
    return 0;
}

5.线段树
road
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define maxn 800000
#define inf 2147483647
using namespace std;
long long key[4][maxn],cov[maxn];
int n,m;
long long ll,rr;

inline void cover(int x,long long l,long long r,long long z)
{
    key[1][x]+=z*(r-l+1);
    key[2][x]+=z*(l+r)*(r-l+1)/2;
    key[3][x]+=z*(r*(r+1)*(2*r+1)-(l-1)*l*(2*l-1))/6;
}

inline void down(int x,int l,int r)
{
    int mid=(l+r)>>1;
    cov[x*2]+=cov[x];
    cov[x*2+1]+=cov[x];
    cover(x*2,l,mid,cov[x]);
    cover(x*2+1,mid+1,r,cov[x]);
    cov[x]=0;
}    
    
inline void add(int x,int l,int r,long long z)
{
    if (ll<=l&&r<=rr)
    {
        cov[x]+=z;
        cover(x,l,r,z);
        return ;
    }
    down(x,l,r);
    int mid=(l+r)>>1;
    if (ll<=mid) add(x*2,l,mid,z);
    if (rr>mid) add(x*2+1,mid+1,r,z);
    for (int i=1;i<=3;i++) key[i][x]=key[i][x*2]+key[i][x*2+1];
}

inline long long ask(int k,int x,int l,int r)
{
    long long tmp=0;
    if (ll<=l&&r<=rr) return key[k][x];
    down(x,l,r);
    int mid=(l+r)>>1;
    if (ll<=mid) tmp+=ask(k,x*2,l,mid);
    if (rr>mid) tmp+=ask(k,x*2+1,mid+1,r);
    for (int i=1;i<=3;i++) key[i][x]=key[i][x*2]+key[i][x*2+1];
    return tmp;
}

inline long long gcd(long long a,long long b)
{
    if (a==0) return b;
    else return gcd(b%a,a);
}    

int main()
{
    //freopen("road4.in","r",stdin);
    //freopen("road.out","w",stdout);
    scanf("%d%d",&n,&m);
    n=n-1;
    int x,y,z;
    char sign;
    for (int i=1;i<=m;i++)
    {
        scanf("\n%c",&sign);
        if (sign=='C')
        {
            scanf("%d%d%d",&x,&y,&z);
            ll=x; rr=y-1;
            add(1,1,n,z);
        }
        else 
        if (sign=='Q')
        {
            scanf("%d%d",&x,&y);
            ll=x; rr=y-1;
            long long a1=(rr-ll-rr*ll+1)*ask(1,1,1,n);
            long long a2=(ll+rr)*ask(2,1,1,n);
            long long a3=ask(3,1,1,n);
            long long ans=a1+a2-a3;
            long long sum=(rr-ll+1)*(rr-ll+2)/2;
            long long tmp;
            if (ans>sum) tmp=gcd(sum,ans); else tmp=gcd(ans,sum);
            printf("%lld/%lld\n",ans/tmp,sum/tmp);
        }
    }
    return 0;
}

6.LCT
tree
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define maxn 220000
#define inf 1000000000
#define ms 51061
using namespace std;
int fir[maxn],c[maxn][2],fa[maxn],size[maxn],rev[maxn];
unsigned int key[maxn],sum[maxn],add[maxn],mul[maxn];
int n,m,tot;
unsigned int ans;
struct et
{
    int s,t,next;
    void add(int x,int y)
    {
        s=x; t=y; next=fir[x]; fir[x]=tot;
    }
}e[maxn];

inline void update(int x)
{
    if (!x) return ;
    size[x]=size[c[x][0]]+size[c[x][1]]+1;
    sum[x]=(sum[c[x][0]]+sum[c[x][1]]+key[x])%ms;
}

inline bool root(int x)
{
    return (c[fa[x]][0]!=x&&c[fa[x]][1]!=x);
}

inline void reverse(int x)
{
    if (!x) return ;
    swap(c[x][0],c[x][1]);
    rev[x]^=1;
}

inline void mult(int x,int w)
{
    if (!x) return ;
    key[x]=key[x]*w%ms;
    sum[x]=sum[x]*w%ms;
    mul[x]=mul[x]*w%ms; 
    add[x]=add[x]*w%ms;
}

inline void addit(int x,int w)
{
    if (!x) return ;
    key[x]=(key[x]+w)%ms;
    sum[x]=(sum[x]+w*size[x])%ms;
    add[x]=(add[x]+w)%ms;
}

inline void down(int x)
{
    if (rev[x])
    {
        reverse(c[x][0]); reverse(c[x][1]);
        rev[x]=0;
    }
    if (mul[x]!=1)
    {
        mult(c[x][0],mul[x]); mult(c[x][1],mul[x]);
        mul[x]=1;
    }
    if (add[x])
    {
        addit(c[x][0],add[x]); addit(c[x][1],add[x]);
        add[x]=0;
    }
}

inline void zigzag(int x)
{
    //down(x);
    int y=fa[x],z=fa[y];
    int p=(c[y][1]==x),q=p^1;
    if (!root(y))
        if (c[z][0]==y) c[z][0]=x; else c[z][1]=x;
    fa[x]=z; fa[y]=x; fa[c[x][q]]=y;
    c[y][p]=c[x][q]; c[x][q]=y;
    update(y);
}

inline void relax(int x)
{
    if (!root(x)) relax(fa[x]);
    down(x);
}

inline void splay(int x)
{
    relax(x);
    while (!root(x))
    {
        int y=fa[x],z=fa[y];
        //if (z) down(z); down(y);
        if (!root(y))
            if ((c[y][0]==x)xor(c[z][0]==y)) zigzag(x); else zigzag(y);
        zigzag(x);
    }
    //down(x);
    update(x);
}

inline int access(int x)
{
    int y=0;
    for (;x;x=fa[x])
    {
        splay(x);
        c[x][1]=y;
        update(x);
        y=x;
    }
    return y;
}

inline void link(int x,int y)
{
    access(x); splay(x);
    reverse(x);
    fa[x]=y;
}

inline void cut(int x,int y)
{
    access(x); splay(y);
    if (fa[x]==y) fa[x]=0; 
    else
    {
        access(y); splay(x);
        fa[y]=0;
    }
}

inline void dfs(int now)
{
    for (int j=fir[now];j;j=e[j].next)
    {
        int k=e[j].t;
        if (fa[now]!=k) fa[k]=now,dfs(k);
    }
}

int main()
{
    //freopen("tree.in","r",stdin);
    scanf("%d%d",&n,&m);
    int x,y;
    for (int i=1;i<=n;i++) size[i]=key[i]=mul[i]=sum[i]=1,add[i]=0;
    for (int i=1;i<n;i++)
    {
        scanf("%d%d",&x,&y);
        e[++tot].add(x,y);
        e[++tot].add(y,x);
    }
    int rot=rand()%n+1;
    dfs(rot);
    char sign;
    int u,v,z,lca;
    for (int i=1;i<=m;i++)
    {
        scanf("\n%c",&sign);
        switch (sign)
        {
            case '+':
                scanf("%d%d%d",&u,&v,&z);
                access(u); lca=access(v); splay(u);
                sum[lca]=(sum[lca]+z)%ms,key[lca]=(key[lca]+z)%ms;
                addit(c[lca][1],z);
                if (u!=lca)    addit(u,z);
            break;
            case '-':
                scanf("%d%d%d%d",&x,&y,&u,&v);
                cut(x,y);
                link(u,v);
            break;
            case '*':
                scanf("%d%d%d",&u,&v,&z);
                access(u); lca=access(v); splay(u);
                sum[lca]=(sum[lca]+key[lca]*(z-1))%ms,key[lca]=(key[lca]*z)%ms;
                mult(c[lca][1],z);
                if (u!=lca) mult(u,z);
            break;
            case '/':
                scanf("%d%d",&u,&v);
                access(u); lca=access(v); splay(u);
                if (u==lca)
                    ans=(key[lca]+sum[c[lca][1]])%ms;
                else 
                    ans=(key[lca]+sum[c[lca][1]]+sum[u])%ms;
                printf("%d\n",ans);
            break;
        }
    }
    return 0;
}

7.Simplex
Match
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define maxn 1010
#define inf 2147483647
using namespace std;
int mat[1000][1000],num[1000][1000],next[maxn],c[maxn],rank[maxn];
bool v[maxn*maxn],p[maxn][maxn],ls[maxn];
int n,m,a,b,sum;

void change(int x,int e)
{
    int last=-1;
    for (int i=0;i<=m;i++)
        if (mat[x][i])
        {
            next[i]=last;
            last=i;
        }
    for (int i=0;i<=n;i++)
    {
        if (i==x||mat[i][e]==0) continue;
        for (int j=last;j!=-1;j=next[j])
        {
            if (j==e) continue;
            mat[i][j]-=mat[i][e]*mat[x][j];
        }
        mat[i][e]=-mat[i][e];
    }
}

int simplex()
{
    while (1)
    {
        int now=0;
        for (int i=1;i<=m;i++)     
            if (mat[0][i]>0) { 
                now=i;
                break;
            }
        if (now==0) return -mat[0][0];
        int tmp,mi=inf;
        for (int i=1;i<=n;i++)
            if (mat[i][now]>0&&mat[i][0]<mi)
                mi=mat[i][0],tmp=i;
        change(tmp,now);
    }
}

int gcd(int a,int b)
{
    if (b==0) return a;
    else return gcd(b,a%b);
}

int main()
{
    scanf("%d%d",&a,&b);
    for (int i=1;i<=b;i++) v[i*i]=1;
    memset(ls,0,sizeof(ls));
    for (int i=a;i<=b;i++)
        for (int j=a;j<i;j++)
            if (v[i*i-j*j]&&gcd(i,j)==1)
            {
                p[i][j]=1;
                if (!ls[i]) c[++n]=i,ls[i]=1;
                if (!ls[j]) c[++n]=j,ls[j]=1;
            }
    sort(c+1,c+n+1);
    for (int i=1;i<=n;i++) rank[c[i]]=i;
    for (int i=a;i<=b;i++)
        for (int j=a;j<i;j++)
        {
            if (p[i][j])
            {
                m++;
                mat[rank[i]][m]=1;
                mat[rank[j]][m]=1;
                mat[0][m]=i+j;
            }
        }
    for (int i=1;i<=n;i++)
        mat[i][0]=1;
    int ans=simplex();
    for (int i=1;i<=n;i++) sum+=(mat[i][0]==0);
    printf("%d %d\n",sum,ans);
    return 0;
}

8.2维BIT
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define maxn 2048
using namespace std;
int n,m;
struct bit
{
    int b[maxn][maxn];
    void add(int x,int y,int z)
    {
        for (int i=x;i<=n;i+=(i&-i))
            for (int j=y;j<=m;j+=(j&-j))
                b[i][j]+=z;
    }
    int ask(int x,int y)
    {
        int tmp=0;
        for (int i=x;i>0;i-=(i&-i))
            for (int j=y;j>0;j-=(j&-j))
                tmp+=b[i][j];
        return tmp;
    }
}s,t,l,r;

void ins(int x1,int y1,int x2,int y2,int z)
{
    s.add(x1,y1,z); s.add(x2+1,y1,-z); s.add(x1,y2+1,-z); s.add(x2+1,y2+1,z);
    l.add(x1,y1,z*x1); l.add(x2+1,y1,-z*(x2+1)); l.add(x1,y2+1,-z*x1); l.add(x2+1,y2+1,z*(x2+1));
    r.add(x1,y1,z*y1); r.add(x2+1,y1,-z*y1); r.add(x1,y2+1,-z*(y2+1)); r.add(x2+1,y2+1,z*(y2+1));
    t.add(x1,y1,z*x1*y1); t.add(x2+1,y1,-z*(x2+1)*y1); t.add(x1,y2+1,-z*x1*(y2+1)); t.add(x2+1,y2+1,z*(x2+1)*(y2+1));
}

int query(int x1,int y1,int x2,int y2)
{
    int a1=s.ask(x2,y2)*(x2+1)*(y2+1)-s.ask(x1-1,y2)*x1*(y2+1)-s.ask(x2,y1-1)*(x2+1)*y1+s.ask(x1-1,y1-1)*x1*y1;
    int a2=l.ask(x2,y2)*(y2+1)-l.ask(x1-1,y2)*(y2+1)-l.ask(x2,y1-1)*y1+l.ask(x1-1,y1-1)*y1;
    int a3=r.ask(x2,y2)*(x2+1)-r.ask(x1-1,y2)*x1-r.ask(x2,y1-1)*(x2+1)+r.ask(x1-1,y1-1)*x1;
    int a4=t.ask(x2,y2)-t.ask(x1-1,y2)-t.ask(x2,y1-1)+t.ask(x1-1,y1-1);
    return a1-a2-a3+a4;
}

int main()
{
    //freopen("make.in","r",stdin);
    char sign[10];
    scanf("%s%d%d",sign,&n,&m);
    int x1,x2,y1,y2;
    int z;
    while (scanf("%s",sign)!=EOF)
    {
        if (sign[0]=='L') 
        {
            scanf("%d%d%d%d%d",&x1,&y1,&x2,&y2,&z);
            ins(x1,y1,x2,y2,z);
        }
        else
        {
            scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
            int ans=query(x1,y1,x2,y2);
            printf("%d\n",ans);
        }
    }
    return 0;
}

9.整体二分
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define maxn 220000
#define inf 1000000000

using namespace std;
struct query
{
    int x,y,k,s,tp,cur;
}q[maxn],q1[maxn],q2[maxn];
int a[maxn],ans[maxn],tmp[maxn],t[maxn];
int n,m,num,cnt;

void add(int x,int y)
{
    for (int i=x;i<=n;i+=(i&-i)) t[i]+=y;
}

int ask(int x)
{
    int tmp=0;
    for (int i=x;i>0;i-=(i&-i)) tmp+=t[i];
    return tmp;
}

void divide(int head,int tail,int l,int r)
{
    //cout<<head<<' '<<tail<<' '<<l<<' '<<r<<endl;
    if (head>tail) return ;
    if (l==r) 
    {
        for (int i=head;i<=tail;i++)
            if (q[i].tp==3) ans[q[i].s]=l;//,cout<<l<<endl;
        return ;
    }
    int mid=(l+r)>>1;
    for (int i=head;i<=tail;i++)
    {
        if (q[i].tp==1&&q[i].y<=mid) add(q[i].x,1);
        else
        if (q[i].tp==2&&q[i].y<=mid) add(q[i].x,-1);
        else
        if (q[i].tp==3) tmp[i]=ask(q[i].y)-ask(q[i].x-1);
    }
    for (int i=head;i<=tail;i++)
    {
        if (q[i].tp==1&&q[i].y<=mid) add(q[i].x,-1);
        else
        if (q[i].tp==2&&q[i].y<=mid) add(q[i].x,1);
    }
    int l1=0,l2=0;
    for (int i=head;i<=tail;i++)
        if (q[i].tp==3)
        {
            if (q[i].cur+tmp[i]>q[i].k-1)//q[i].cur+tmp[i]表示累积了多少个数
                q1[++l1]=q[i];
            else
            {
                q[i].cur+=tmp[i];
                q2[++l2]=q[i];
            }
        }
        else
        {
            if (q[i].y<=mid) q1[++l1]=q[i];
            else q2[++l2]=q[i];
        }
    for (int i=1;i<=l1;i++) q[head+i-1]=q1[i];
    for (int i=1;i<=l2;i++) q[head+l1+i-1]=q2[i];
    divide(head,head+l1-1,l,mid);
    divide(head+l1,tail,mid+1,r);
}    

int main()
{
    //freopen("ranking.in","r",stdin);
    //freopen("ranking.out","w",stdout);
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++) 
    {
        scanf("%d",&a[i]);
        q[++num].x=i; q[num].y=a[i];
        q[num].tp=1; q[num].s=0;
    }
    char sign;
    int x,y,z;
    for (int i=1;i<=m;i++)
    {
        scanf("\n%c",&sign);
        if (sign=='Q')
        {
            scanf("%d%d%d",&x,&y,&z);
            q[++num].x=x,q[num].y=y,q[num].k=z;
            q[num].tp=3; q[num].s=++cnt;
        }
        else
        {
            scanf("%d%d",&x,&y);
            q[++num].x=x; q[num].y=a[x]; 
            q[num].tp=2; q[num].s=0;
            q[++num].x=x; q[num].y=y;
            q[num].tp=1; q[num].s=0;
            a[x]=y;
        }
    }
    divide(1,num,0,inf);
    for (int i=1;i<=cnt;i++)
        printf("%d\n",ans[i]);
    return 0;
}

10.AC自动机
typewriter
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define inf 2147483647
#define maxn 200000
using namespace std;
struct ask
{
    int x,y,s;
}a[maxn];
struct et
{
    int s,t,next;
}e[maxn];
int n,m,tot,num,now,rot,cnt,tim;
char s[maxn];
int fir[maxn],fail[maxn],ch[maxn][27],fa[maxn],q[maxn];
int t[maxn],ans[maxn],ll[maxn],rr[maxn],st[maxn];

void insert(int w)
{
    if (!ch[now][w]) ch[now][w]=++num;
    fa[ch[now][w]]=now;
    now=ch[now][w];
}

void add(int x,int y)
{
    e[++tot].s=x; e[tot].t=y; e[tot].next=fir[x]; fir[x]=tot;
}

void build()
{
    int head=0,tail=1;
    q[1]=rot;
    while (head<tail)
    {
        int p=q[++head];
        for (int w=0;w<26;w++)
            if (ch[p][w])
            {
                int tmp=ch[p][w];
                int j=p;
                if (j==rot) fail[tmp]=rot;
                else
                {
                    j=fail[j];
                    while (j&&ch[j][w]==0) j=fail[j];
                    if (ch[j][w]) fail[tmp]=ch[j][w];
                    else fail[tmp]=rot;
                }
                add(fail[tmp],tmp);
                q[++tail]=tmp;
            }
    }
}

void dfs(int i)
{
    ll[i]=rr[i]=++cnt;
    for (int j=fir[i];j;j=e[j].next)
    {
        int k=e[j].t;
        if (fa[i]!=k) dfs(k);
        rr[i]=cnt;
    }
}

int getsum(int x)
{
    int ans=0;
    for (int i=x;i;i-=(i & -i)) ans+=t[i];
    return ans;
}

void ins(int x,int z)
{
    for (int i=x;i<=cnt;i+=(i & -i)) t[i]+=z;
}

bool cmp(ask a,ask b)
{
    return a.y<b.y;
}

int main()
{
    //freopen("type.in","r",stdin);
    scanf("%s",s);
    int len=strlen(s);
    rot=now=num=tim=0;
    //建立AC自动机同时构造fail树
    for (int i=0;i<len;i++)
    {
        if (s[i]=='B') now=fa[now];
        else 
        if (s[i]=='P') st[++tim]=now;
        else
            insert(s[i]-'a');
    }
    build();
    cnt=0;
    //遍历得到fail树的dfs序
    dfs(rot);
    //处理询问
    scanf("%d",&m);
    //按Y排序询问，以便把Y相同的一起处理
    for (int i=1;i<=m;i++)
    {
        scanf("%d%d",&a[i].x,&a[i].y);
        a[i].s=i;
    }
    sort(a+1,a+m+1,cmp);
    //按照一开始建AC的顺序遍历AC自动机，如果遇到一个和询问的y[tim]相同的串，就查询相应的x
    now=rot;
    int tim=0,tail=1;
    for (int i=0;i<len;i++)
    {
        if (s[i]=='B')//删除并回溯 
        {
            ins(ll[now],-1);
            now=fa[now];
        }
        else 
        if (s[i]=='P')//区间查询
        {
            tim++;
            while (a[tail].y==tim)
            {
                int tmp=st[a[tail].x];
                ans[a[tail].s]=getsum(rr[tmp])-getsum(ll[tmp]-1);
                tail++;
            }
        }
        else//单点插入
        {
            int w=s[i]-'a';
            now=ch[now][w];
            ins(ll[now],1);
        }
    }
    for (int i=1;i<=m;i++) printf("%d\n",ans[i]);
    return 0;
}

11.参数二分
minhoop
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#define maxn 10000
#define maxm 50000
using namespace std;
struct et
{
        int s,t,next;
        double val,cost;
}e[maxm];
int v[maxn],fir[maxn];
double dis[maxn];
int n,m,tot;

bool find(int now)
{
        v[now]=1;
        for (int j=fir[now];j;j=e[j].next)
        {
                int k=e[j].t;
                if (dis[now]+e[j].cost<dis[k])
                {
                        if (!v[k])
                        {
                                dis[k]=dis[now]+e[j].cost;
                                if (find(k))
                                        {
                                                v[now]=0;
                                                return 1;
                                        }
                        }
                        else
                        {
                                v[now]=0;
                                return 1;
                        }
                }
        }
        v[now]=0;
        return 0;
}

bool judge(double p)
{
        for (int i=1;i<=tot;i++) e[i].cost=e[i].val-p;
        for (int i=1;i<=n;i++) dis[i]=0;
        for (int i=1;i<=n;i++) if (find(i)) return 1;
        return 0;
}

void add(int x,int y,double z)
{
        e[++tot].s=x; e[tot].t=y; e[tot].val=z; 
        e[tot].next=fir[x]; fir[x]=tot;
}

int main()
{
        freopen("1486.in","r",stdin);
        scanf("%d %d",&n,&m);
        int x,y;
        double z;
        for (int i=1;i<=m;i++)
        {
                scanf("%d %d %lf",&x,&y,&z);
                add(x,y,z);
        }
        double l=-1e7,r=1e7,ans=0;
        while (l-r<=1e-9)
        {
                double mid=(l+r)/2;
                        //cout<<mid<<endl;
                if (judge(mid)) r=mid-(1e-9),ans=mid;
                else l=mid+(1e-9);
        }
        printf("%.8lf",ans);
        return 0;
}