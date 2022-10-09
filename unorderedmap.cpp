#include<iostream>
#include<unordered_map>
#include<string>
using namespace std;
int main(){
    unordered_map<string,int> ourmap;
    //insert
    pair<string,int> p("abc",1);
    ourmap.insert(p);
    ourmap["def"]=2;
    //find or access
    cout<<ourmap["abc"]<<endl;
    
}