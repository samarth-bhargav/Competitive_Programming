/*
ID: samarth10
LANG: C++11
TASK: 
*/
#include <bits/stdc++.h>

using namespace std;

int main() {
    //setIO();
    int t;
    cin >> t;
    while (t--){
        int a,b;
        cin >> a >> b;
        if (abs(a-b)%10 == 0){
            cout << (abs(a-b)/10) << "\n";
        }
        else{
            cout << (abs(a-b)/10 + 1) << "\n";
        }
    }
}

