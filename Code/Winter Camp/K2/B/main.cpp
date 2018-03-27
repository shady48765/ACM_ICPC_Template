#include <iostream>
#include<string>
#include<cstring>
using namespace std;
char A[202000],B[202000],C[202000];
int m,n,j,cnt,next[202000];
bool check(){
    int flag=1,first;
    if (cnt>6) return 0;
    first=1;
    int i;
 //   cout<<"n="<<n<<endl;
 // for (int i=1;i<=n;i++) cout<<B[i];cout<<endl;
    for (i=1;i<=n;i+=2){
      //  cout<<i<<" "<<B[i]<<" "<<B[i+1]<<endl;
        if (B[i]=='a' && B[i+1]=='a') {C[(i+1)>>1]='a';cout<<i<<" "<<C[i]<<endl;}
        else if(B[i]=='a' && B[i+1]=='b') {C[(i+1)>>1]='b';cout<<i<<" "<<C[i]<<endl;}
        else if(B[i]=='b' && first) {
            for(int j=n+1;j>=2;j--){
                B[j]=B[j-1];
            }
            first=0;
            n++;
            B[1]='a';
            i=1;
            cout<<"! "<<i<<" "<<n<<endl;
        }else if (i==n && i%2==1){
            B[++n]='a';i=1;
            cout<<"@ "<<i<<" "<<n<<endl;
        }
        if (flag==0) break;
    }
    if (flag==0) return 0;
    for (int i=1;i<=(n+1)>>1;i++) cout<<C[i];cout<<endl;
  //9  cout<<"YES"<<endl;
    n=(n+1)>>1;

    for (int i=1;i<=n;i++){
        B[i]=C[i];
    }
    cout<<"n'="<<n<<endl;
    for (int i=1;i<=n;i++) cout<<B[i];cout<<endl;
    return 1;
}
int main()
{
  //  freopen("data.in","r",stdin)
    cin>>A>>B;m=strlen(A);n=strlen(B);
  //  A[1]='a';for (int i=0;i<1;i++)B[i]='a';m=1;n=1;
 //   cout<<B<<endl;
    cnt=0;
    for (int i=n;i;i--) B[i]=B[i-1];B[n+1]='0';
    do{

    //    cout<<n<<endl;
    //    for (int i=1;i<=n;i++) cout<<B[i];cout<<endl;
        j=0;
        for (int i=2;i<=n;i++){
            while (j!=0 && B[j+1]!=B[i]) j=next[j];
            if (B[i]==B[j+1]) j++;
            next[i]=j;
        }
//        if (n<=10)    for (int i=1;i<=m;i++) cout<<A[i];cout<<endl;
//       cout<<m<<endl;
  //  if (n<=10)    for (int i=1;i<=n;i++) cout<<B[i];cout<<endl;
 //  cout<<n<<endl;
        j=0;
        for (int i=0;i<m;i++){
            while (j!=0 && B[j+1]!=A[i]) j=next[j];
            if (B[j+1]==A[i]) j++;
            if (j==n) {
                cout<<cnt<<endl;
                return 0;
            }
        }
        cnt++;
      //  cout<<"!"<<endl;
    }while (check());

    cout<<"-1"<<endl;
    return 0;
}
