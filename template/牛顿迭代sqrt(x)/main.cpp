#include <iostream>

using namespace std;
//f(x)=sqrt(x)
double square_root(int x)
{
    if(x==0)
        return 0;
    double root=1,last=-1;
    while(true)
    {
        double next=(root+x/root)/2;
        if(next==last){
            return min(last,root);
        }
        last=root;root=next;
    }
}
int main()
{
    int n;
    cin>>n;
    cout<<square_root(n)<<endl;
    return 0;
}
