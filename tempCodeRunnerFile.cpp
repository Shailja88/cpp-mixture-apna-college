//Write a program to check if a given number is power of 2
#include<iostream>
using namespace std;
bool ispowerof2(int n){
    return(n && !(n & n-1));

}
int main()
{
    cout<<ispowerof2(12)<<endl;
    return 0;
}