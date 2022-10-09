// 3
// 5 5 5
// 2 3 4
// 2 2 4

#include <bits/stdc++.h>
using namespace std;
void sort(int arr[],int n){
  for(int i=0;i<2;i++){
      int temp;
      if(arr[i]>=arr[i+1])
      {
       temp=arr[i];
       arr[i]=arr[i+1];
       arr[i+1]=temp;
      }
  }
}
int main() {
	// your code goes here
	int t;
    int a,b,c;int a1,b1,c1;
	int ar[3];
	cin>>t;
	while(t--){
        cin>>a;
        cin>>b;
        cin>>c;
	    a1=min(a,b);
	    b1=min(b,c);
	    c1=min(c,a);
	    ar[0]=a1;
	    ar[1]=b1;
	    ar[2]=c1;
 sort(ar,3);
 for(int i=0;i<3;i++)
 {
    cout<<ar[i]<<endl;
 }
if((ar[0]!=ar[1])&&(ar[0]!=ar[1]!=ar[2]) )
cout<<"NO"<<endl;
 
else {
cout<<"YES"<<endl;
	}}
	return 0;
}
