#include <iostream>
#include<cstdio>
#include<cstring>
using namespace std;
long long k;
long long  p;
struct _matrix
{
    long long A[3][3];
    void nowclear()
    {
        memset(A,0,sizeof(A));
    }
}I,matrix;
_matrix operator*(_matrix A,_matrix B)
{
    _matrix C;
    C.nowclear();
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            for(int k=0;k<3;k++)
                C.A[i][j]+=A.A[i][k]*B.A[k][j]%p,C.A[i][j]%=p;
    return C;
}
int fastpow(long long k)
{
    I.nowclear();
    I.A[0][0]=I.A[1][1]=I.A[2][2]=1;
    matrix.A[0][0]=10;
    matrix.A[0][1]=1;
    matrix.A[0][2]=0;
    matrix.A[1][0]=0;
    matrix.A[1][1]=10;
    matrix.A[1][2]=1;
    matrix.A[2][0]=0;
    matrix.A[2][1]=0;
    matrix.A[2][2]=1;
    while(k)
    {
        if(k&1)
            I=I*matrix;
        matrix=matrix*matrix;
        k>>=1;
    }
    return (I.A[0][1]%p+I.A[0][2]%p)%p;
}
int main()
{
    freopen("zeroes.in","r",stdin);
    freopen("zeroes.out","w",stdout);
    cin>>k>>p;
    cout<<(fastpow(k-1)%p*9%p+k)%p;
    return 0;
}
