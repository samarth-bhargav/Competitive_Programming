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
        int n;
        cin >> n;
        set <int> a;
        for (int i = 0; i < 2*n; i++){
            int k;
            cin >> k;
            if (a.find(k) == a.end()){
                cout << k << " ";
                a.insert(k);
            }
        }
        cout << "\n";
    }
}

