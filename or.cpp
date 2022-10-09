#include<bits/stdc++.h>
using namespace std;
void reverse(int arr[],int n,int k){
    int  a1[n]={0};
    int l=0;int m=k;
    
for(int i=0;i<n;i++){
 if(i<(n-k))
 {
    a1[i]=arr[m];
    m++;
    
 }
 else {
    a1[i]=arr[l];
    l++;
 }
}
for(int i=0;i<n;i++){
    cout<<a1[i]<<" ";
}
}
int main (){
//input an array;
int n;
cin>>n;

int arr[n];int k;
cout<<"Enter the position from where you want to reverse the array "<<endl;
cin>>k;
for(int i=0;i<n;i++){
    cin>>arr[i];
}
reverse(arr,n,k);
    return 0;
}