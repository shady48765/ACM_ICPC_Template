#include <iostream>
#include<algorithm>
using namespace std;
//letter 0.25-7,90-155,125-290
//packet 0.25-50,90-300,125-380
//parcel length<2100
double s[4];
int main()
{
    while(cin>>s[1]>>s[2]>>s[3]&&(s[1]+s[2]+s[3]))
    {
        sort(s+1,s+4);
        if(s[1]<0.25||s[2]<90||s[3]<125){
            cout<<"not mailable"<<endl;
            continue;
        }
        if(s[1]<=7&&s[2]<=155&&s[3]<=290)
        {
            cout<<"letter"<<endl;
            continue;
        }
        if(s[1]<=50&&s[2]<=300&&s[3]<=380)
        {
            cout<<"packet"<<endl;
            continue;
        }
        double sum=2*(s[1]+s[2])+s[3];
        if(sum<=2100)
        {
            cout<<"parcel"<<endl;
            continue;
        }
        cout<<"not mailable"<<endl;

    }
    return 0;
}
