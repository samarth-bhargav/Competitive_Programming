/*
ID: samarth10
LANG: C++11
TASK: 
*/
#include <bits/stdc++.h>

using namespace std;


void setIO(string name) {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen((name + ".in").c_str(), "r", stdin);
    freopen((name + ".out").c_str(), "w", stdout);
}


int main() {
    //setIO();
    int x;
    cin >> x;
    if (x%2 == 0){
        cout << 4 << " " << x-4 << "\n";
    }
    else{
        if (x >= 13){
            cout << 9 << " " << x - 9 << "\n";
        }
    }
}

