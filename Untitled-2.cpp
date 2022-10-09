#include<iostream>
using namespace std;
int main(){
    int n,m;
    cin>>n;
    cin>>m;
    int A[n][m];
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
          cin>>A[i][j];
        }
    }
    for(int i=0;i<n;i++){
        int temp=A[i][j];
        A[i][j]=A[j][i]; 
        A[j][i]=temp;
    }
}