#include"bits/stdc++.h"
using namespace std;
int main()
{
    int n;
    int a;
cout<<"Enter a number";
cin>>n;
int _100r,_50r,_20r,_1r=0;
cout<<"Enter 1 for finding no of notes.";
cin>>a;
switch(1){
case 1:

_100r=n/100;
cout<<"100 rs notes are :"<<_100r<<endl;
n=n%100;
_50r=n/50;
n=n%50;
cout<<"50 rs notes are :"<<_50r<<endl;
_20r=n/20;
n=n%20;
cout<<"20 rs notes are :"<<_20r<<endl;
_1r=n/1;

cout<<"1 rs notes are :"<<_1r<<endl;

break;

default:
cout<<"Wrong choice.";
}
}
