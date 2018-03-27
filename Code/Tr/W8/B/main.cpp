#include <iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
char buf[300005];
char A[300005];
int len;
int main()
{
    while(scanf("%s",buf)!=EOF)
    {
        len=strlen(buf);
        for(int i=0;i<len;i++)
        {
            if(buf[i]>buf[(i+1)%len])
                A[i]=8-buf[i]+buf[(i+1)%len]+'0';
            else
                A[i]=buf[(i+1)%len]-buf[i]+'0';
        }
        //printf("%s\n",A);
        int i=0,j=1,k=0;
        for(;i<len&&j<len&&k<len;)
        {
            //printf("hehe\n");
            if(A[(i+k)%len]==A[(j+k)%len]) k++;
            else if(A[(i+k)%len]>A[(j+k)%len])
            {
                i+=k+1;
                if(i==j) i+=1;
                if(i>j) swap(i,j);
                k=0;
            }
            else if(A[(i+k)%len]<A[(j+k)%len])
            {
                j+=k+1;
                k=0;
            }
        }
        for(int k=0;k<len;k++)
            printf("%c",A[(i+k)%len]);
        printf("\n");
    }

    return 0;
}
