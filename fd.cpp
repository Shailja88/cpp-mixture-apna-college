#include<bits/stdc++.h>
using namespace std;
int main(){
    int a;
    cin>>a;
    for(int i=0;i<a;i++){
        for(int j=0;j<a;j++){
            if( j== 2)
            {
                cout<<"LOOp khtm"<<endl;
                return 0;
            }
            else{
                cout<<j<<endl;
            }
        }
    }
    return 0;
}