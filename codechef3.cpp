#include <iostream>
using namespace std;

int main() {
	// your code goes here
	int t;
	cin>>t;
	while(t--)
	{
	    long long int x,y,n,co=0;
	    cin>>n;
	    string s;
	    cin>>s;
	    for(int i=0;i<n/2;i++)
	    {
	        if(s[i]!=s[n-i-1]){
	            co+=1;
	        }
	    }
	    int ans;
	    if(co%2==0)
	    ans=co/2;
	    else
	    ans=co/2+1;
	    
	cout<<ans<<endl;

}
	return 0;
}

