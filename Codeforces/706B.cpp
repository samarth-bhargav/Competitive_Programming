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
    int ar[t];
    for (int i = 0; i < t; i++){
        cin >> ar[i];
    }
    sort(ar, ar+t);
    int x;
    cin >> x;
    for (int i = 0; i < x; i++){
        int c;
        cin >> c;
        if (binary_search(ar, ar + t, c)){
            cout << upper_bound(ar, ar + t, c) - ar << "\n";
        }
        else{
            cout << upper_bound(ar, ar + t, c) - ar<< "\n";
        }
    }
}

