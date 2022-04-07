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
        double n,m,k;
        cin >> n >> m >> k;
        if (n/k >= m){
            cout << m << "\n";
        }
        else if(m == 0){
            cout << 0 << "\n";
        }
        else{
            cout << setprecision(15) << (n/k) - ceil((m - n/k)/(k-1)) << "\n";
        }
    }

}

