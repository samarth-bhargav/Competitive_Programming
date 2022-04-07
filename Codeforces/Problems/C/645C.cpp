/*
ID: samarth10
LANG: C++11
TASK: 
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


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
        ll a,b;
        cin >> a >> b;
        ll c,d;
        cin >> c >> d;
        ll len = abs(b-d) + abs(a-c);
        ll diff;
        if (a > c || b > d){
            cout << 0 << "\n";
        }
        else{
            if (len%2 == 0){
                diff = min(abs(a-c), abs(b-d));
                cout << ((diff - 1) * (diff)) + diff + 1<< "\n";
            }
            else{
                diff = min(abs(a-c), abs(b-d));
                cout << (diff*(diff+1)) + 1<< "\n";
            }
        }
    }
}

