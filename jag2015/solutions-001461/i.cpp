#include <stdlib.h>
#include <string.h>
#if ( _WIN32 || __WIN32__ || _WIN64 || __WIN64__ )
#define INT64 "%I64d"
#else
#define INT64 "%lld"
#endif

#if ( _WIN32 || __WIN32__ || _WIN64 || __WIN64__ )
#define UNS64 "%I64u"
#else
#define UNS64 "%llu"
#endif
    #include<stdio.h>
    #include<algorithm>
    #include<vector>
    #include<complex>
    #include<math.h>
    using namespace std;
    double ax[110000];
    double ay[110000];
    double bx[110000];
    double by[110000];
    double cx[110000];
    double cy[110000];
    double EPS=1e-9;
    double ABS(double a){return max(a,-a);}
    double abs2(double x,double y){return x*x+y*y;}
    const double PI=4.0*atan(1.0);
    typedef complex<double> Complex;
    const Complex I(0,1);
    void fft(int n,double theta,Complex a[]){
    for(int m=n;m>=2;m>>=1){
    int mh=m>>1;
    for(int i=0;i<mh;i++){
    Complex w=exp(i*theta*I);
    for(int j=i;j<n;j+=m){
    int k=j+mh;
    Complex x=a[j]-a[k];
    a[j]+=a[k];
    a[k]=w*x;
    }
    }
    theta*=2;
    }
    int i=0;
    for(int j=1;j<n-1;j++){
    for(int k=n>>1;k>(i^=k);k>>=1);
    if(j<i)swap(a[i],a[j]);
    }
    }
    int Ax[110000];
    int Ay[110000];
    int Bx[110000];
    int By[110000];
    int Cx[110000];
    int Cy[110000];
    Complex af[524400];
    Complex bf[524400];
    Complex cf[524400];
    int cd[524400];
    int main(){
    int a,b,c;
    scanf("%d%d%d",&a,&b,&c);
    for(int i=0;i<a;i++)scanf("%d%d",Ax+i,Ay+i);
    for(int i=0;i<b;i++)scanf("%d%d",Bx+i,By+i);
    for(int i=0;i<c;i++)scanf("%d%d",Cx+i,Cy+i);
    for(int i=0;i<a;i++){
    ax[i]=Ax[i];
    ay[i]=Ay[i];
    }
    for(int i=0;i<b;i++){
    bx[i]=Bx[i];
    by[i]=By[i];
    }
    for(int i=0;i<c;i++){
    cx[i]=Cx[i];
    cy[i]=Cy[i];
    }
    int cL=0;
    int cR=0;
    for(int i=1;i<c;i++){
    if(cx[i]*114514+cy[i]*810<cx[cL]*114514+cy[cL]*810)cL=i;
    if(cx[i]*114514+cy[i]*810>cx[cR]*114514+cy[cR]*810)cR=i;
    }
    if((cx[cL]-cx[cR])*(cx[cL]-cx[cR])+(cy[cL]-cy[cR])*(cy[cL]-cy[cR])<EPS){
    for(int i=0;i<a;i++)ay[i]-=cy[0];
    for(int i=0;i<b;i++)by[i]-=cy[0];
    for(int i=1;i<c;i++)cy[i]-=cy[0];
    cy[0]=0;
    }else{
    double th=atan2(cy[cR]-cy[cL],cx[cR]-cx[cL]);
    for(int i=0;i<a;i++){
    double tx=ax[i]*cos(th)+ay[i]*sin(th);
    double ty=-ax[i]*sin(th)+ay[i]*cos(th);
    ax[i]=tx;ay[i]=ty;
    }
    for(int i=0;i<b;i++){
    double tx=bx[i]*cos(th)+by[i]*sin(th);
    double ty=-bx[i]*sin(th)+by[i]*cos(th);
    bx[i]=tx;by[i]=ty;
    }
    for(int i=0;i<c;i++){
    double tx=cx[i]*cos(th)+cy[i]*sin(th);
    double ty=-cx[i]*sin(th)+cy[i]*cos(th);
    cx[i]=tx;cy[i]=ty;
    }
    for(int i=0;i<a;i++)ay[i]-=cy[0];
    for(int i=0;i<b;i++)by[i]-=cy[0];
    }
    double aD=999999999;
    double aU=-999999999;
    double bD=999999999;
    double bU=-999999999;
    for(int i=0;i<a;i++){
    aD=min(aD,ay[i]);
    aU=max(aU,ay[i]);
    }
    for(int i=0;i<b;i++){
    bD=min(bD,by[i]);
    bU=max(bU,by[i]);
    }
    long long ret=0;
    if(aU-aD<EPS&&bU-bD<EPS){
    if(ABS(aU+bU)>EPS){
    printf("0\n");
    return 0;
    }
    int N=524288;
    int AL=999999999;
    int AR=-999999999;
    int BL=999999999;
    int BR=-999999999;
    int CL=999999999;
    int CR=-999999999;
    for(int i=0;i<a;i++){
    Ax[i]+=110000;
    Ay[i]+=110000;
    }
    for(int i=0;i<b;i++){
    Bx[i]+=110000;
    By[i]+=110000;
    }
    for(int i=0;i<c;i++){
    Cx[i]+=110000;
    Cy[i]+=110000;
    }
    for(int i=0;i<a;i++){
    AL=min(AL,Ax[i]);
    AR=max(AR,Ax[i]);
    }
    for(int i=0;i<b;i++){
    BL=min(BL,Bx[i]);
    BR=max(BR,Bx[i]);
    }
    for(int i=0;i<c;i++){
    CL=min(CL,Cx[i]);
    CR=max(CR,Cx[i]);
    }
    if(AL!=AR||BL!=BR||CL!=CR){
    for(int i=0;i<a;i++)af[Ax[i]]+=Complex(1,0);
    for(int i=0;i<b;i++)bf[Bx[i]]+=Complex(1,0);
    for(int i=0;i<c;i++)cd[Cx[i]*2]++;
    fft(N,PI*2/N,af);
    fft(N,PI*2/N,bf);
    for(int i=0;i<N;i++)cf[i]=af[i]*bf[i];
    fft(N,-PI*2/N,cf);
    for(int i=0;i<N;i++)cf[i]=cf[i]/(double)N;
    for(int i=0;i<524288;i+=2)ret+=((long long)(cf[i].real()+0.5)*cd[i]);
    }else{
    for(int i=0;i<a;i++)af[Ay[i]]+=Complex(1,0);
    for(int i=0;i<b;i++)bf[By[i]]+=Complex(1,0);
    for(int i=0;i<c;i++)cd[Cy[i]*2]++;
    fft(N,PI*2/N,af);
    fft(N,PI*2/N,bf);
    for(int i=0;i<N;i++)cf[i]=af[i]*bf[i];
    fft(N,-PI*2/N,cf);
    for(int i=0;i<N;i++)cf[i]=cf[i]/(double)N;
    for(int i=0;i<524288;i+=2)ret+=((long long)(cf[i].real()+0.5)*cd[i]);
    }
    }else{
    if(aU-aD<EPS){
    for(int i=0;i<max(a,b);i++){
    swap(ax[i],bx[i]);
    swap(ay[i],by[i]);
    }
    swap(a,b);
    }
    vector<pair<double,double> > v;
    for(int i=0;i<b;i++)v.push_back(make_pair(by[i],bx[i]));
    std::sort(v.begin(),v.end());
    vector<pair<double,double> > q;
    for(int i=0;i<a;i++)q.push_back(make_pair(-ay[i],ax[i]));
    std::sort(q.begin(),q.end());
    std::sort(cx,cx+c);
    int at=0;
    long long last=0;
    for(int i=0;i<a;i++){
    if(i&&abs2(q[i].first-q[i-1].first,q[i].second-q[i-1].second)<EPS){
    ret+=last;
    continue;
    }
    last=0;
    while(at<v.size()&&v[at].first<q[i].first+EPS){
    if(ABS(v[at].first-q[i].first)<EPS){
    double M=(v[at].second+q[i].second)/2;
    last+=lower_bound(cx,cx+c,M+EPS)-lower_bound(cx,cx+c,M-EPS);
    }
    at++;
    }
    ret+=last;
    }
    }
    printf(INT64 "\n",ret);
    }

