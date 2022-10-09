#include <bits/stdc++.h>
using namespace std;

int main() {
	// your code goes here
	int t;
	cin>>t;
	while(t--){
	    long long n;
	    
	   long long no=0;
	  
	    cin>>n;
        long long a[n];
        
        
	    for(int i=0;i<n;i++){
	        cin>>a[i];
	    }
	    for(int i=0;i<n;i++){
	         long long n1=0;
	            for(int j=0;j<n;j++){
	                if(a[i]==a[j]){
	                n1=n1+1;
	                //    cout<<n1<<endl; 
	                }
	                  no=max(n1,no);
	            }
	          
                // cout<<no<<endl;
	            
	            
	        }
	    
	    
	    
	    if(n%2==0){
	        if(no<=(n/2)){
	            cout<<"YES"<<endl;
	        }  
	        else
	        cout<<"NO"<<endl;
	    }
	    else{
	        if(no<=n/2+1){
	            cout<<"YES"<<endl;
	        }
	        else{
	            cout<<"NO"<<endl;
	        }
	        
	    }
	    
	}
	return 0;
}
