#include <bits/stdc++.h>

using namespace std;

int main() {
int t,n;  int a;


int final=0;
int x=0;

cin>>t;
cin>>n;
int A[n];
int ans[10];
for(int i=0;i<10;i++)
{
    ans[i]=0;
}
for(int i=1;i<=t;i++)
{



for(int i=0;i<n;i++)
   {
     cin>>a;
     A[i]=a;
   }


   for(int i=0;i<n;i++)
   {
       for(int j=0;j<10;j++)
       {
           if(A[i]==j+1)
           ans[j]+=1;
           
       }
   }


   for(int i=0;i<9;i++)
    {
        final=max(ans[i],ans[i+1]);
    }  

     for(int i =0;i<10;i++)
     {
        if(ans[i]!=0 && ans[i]==final)
        {
            x=x+1;
        }
     }



     if(x==1)
     cout<<final+1;
     if(x>1)
     cout<<"CONFUSED";

       x=0;
     cout<<endl;
}
return 0;
}
