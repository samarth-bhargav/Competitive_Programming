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
        int a,b,c;
        cin >> a >> b >> c;
        int ar[3];
        ar[0] = a;
        ar[1] = b;
        ar[2] = c;
        sort(ar, ar+3);
        if (ar[1] != ar[2]){
            cout << "NO" << "\n";
        }
        else{
            cout << "YES" << "\n";
            if (b == c){
                cout << a << " " << a << " " << b << "\n";
            }
            else if (a == b){
                cout << a << " " << c << " " << c << "\n";
            }
            else if (a == c){
                cout << b << " " << c << " " << b << "\n";
            }
        }
    }
}

