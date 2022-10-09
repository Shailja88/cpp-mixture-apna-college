#include<bits/stdc++.h>
using namespace std;
int divide(int dividend, int divisor){
    int quo=0;int num=0;
while(true){
             if (num>abs(dividend)){
               quo= quo-1;
             break;
             } else {
            num=num+abs(divisor);
               quo=quo+1;
              
                // if(num==abs(dividend))
                //   break;
            
             }
        
}
}
        if((dividend >=0 && divisor<0 )||(dividend <0 && divisor>0 ))
        return -1*(quo);
        else 
        return quo;
}

        
    
    
    
int main(){
    int a=divide(10,3);
    cout<<a<<endl;
    return 0;
}