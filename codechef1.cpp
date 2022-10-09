// #include<bits/stdc++.h>
// using namespace std;
// int main()
// {
//     int T;//test case
//     int X,Y,Z;
//     cin>>T;
//     if(T>=1 && T<=100)
//     {
//         for(int i=0;i<T;i++)
//         {
//             cin>>X;
//             cin>>Y;
//             cin>>Z;
//             if(X>=1 && X<=100 && Y>=1 && Y<=100 && Z>=1 && Z<=100 )
//             {
//                if(X<=Z && X+Y>Z)
//               cout<<"1";
//                else if( X<=Z && X+Y<=Z)
//                cout<<"2";
//                else
//                {
//                    cout<<"0";
//                }
//             }
//             cout<<endl;
           
//         }
//     }
    
    
// // }
// #include<bits/stdc++.h>
// using namespace std; 
// int main()
// {
//     int T;
//      int X,Y;
//      cin>>T;
//      if(T>=1 && T<=5000)
//      {
//          for(int i=0;i<T;i++)
//          {
//              cin>>X;
//              cin>>Y;
//              if(X>=1 && X<=100 && X>=1 && X<=100)
//              {
//                  if(X*100 == Y*10)
//                  cout<<"Cloth";
             
//              if(X*100>Y*10)
//              cout<<"Cloth";
//               if(X*100<Y*10)
//               cout<<"Disposable";
             
//          }
//          cout<<endl;
//      }
//      }
//     return 0;
// }
#include<bits/stdc++.h>
using namespace std; 
int main()
{
    int T;
    int N;
    int x=3;
    cin>>T;
    if(T>=1 && T<=100000)
    {
        for(int i=0;i<T;i++)
        {
            cin>>N;
            if(N>=2 && N <=1000000000)
            {
                if(N==2)
                cout<<x;
               if(N%2!=0)
               {
                   cout<<(3*(N-1))/2;
               }
               if(N%2==0 && N!=2)
               {
                   cout<<(3*N)/2;
               }
            }
            cout<<endl;
        }
    }
    return 0;
}
