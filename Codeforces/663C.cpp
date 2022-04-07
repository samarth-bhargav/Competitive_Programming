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
const int MOD = 1e9+7;
int main() {
    //setIO();
    int x;
    cin >> x;
    int e = 4;
    if (x == 1 || x == 2){
        cout << 0 << "\n";
    }
    else{
        for (int i = 4; i <= x; i++){
            e = (e * i) % MOD;
        }
        cout << e << "\n";
    }
}

