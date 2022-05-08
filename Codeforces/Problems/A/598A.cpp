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
    int t;
    cin >> t;
    while (t--){
        long long a,b,c,d;
        cin >> a >> b >> c >> d;
        //first check mod
        //then check if value satisfies
        if (d % c <= b){
            if (c*a + b >= d){
                cout << "yes" << "\n";
            }
            else{
                cout << "no" << "\n";
            }
        }
        else{
            cout << "no" << "\n";
        }
    }
}

