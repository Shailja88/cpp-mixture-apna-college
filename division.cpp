#include<bits/stdc++.h>
using namespace std;
int main()
{
    int t;
    cin>>t;
    int rating;
    if(t>=1 && t<=5000)
    {
        for(int i=1;i<=t;i++)
        {
            cin>>rating;
            if(rating<=5000 && rating>=-5000)
            {
                if(rating>=1900)
                cout<< "Division 1";
               if(rating>=1600 && rating<=1899)
                cout<< "Division 2";
               if (rating>=1400 && rating<=1599)
               cout<<"Division 3";
               if(rating<=1399)
               cout<<"Division 4";
            }
            cout<<endl;
        }
    }
    return 0;
}
