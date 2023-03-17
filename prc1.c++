#include<bits/stdc++.h>
using namespace std;

int main()
{
    int a=-62;
    string s=to_string(a);
    reverse(s.begin(),s.end());
    int b=stoi(s);
    cout<<endl<<b-26;
    return 0;
}