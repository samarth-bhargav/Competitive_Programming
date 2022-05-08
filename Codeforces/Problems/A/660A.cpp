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
    for (int i = 0; i < t; i++){
        int x;
        cin >> x;
        if (x > 30 && x != 36 && x != 40 && x != 44){
            cout << "YES" << "\n" << "6 10 14 " << x - 30 << "\n";
        }
        else if(x == 36){
            cout << "YES" << "\n" << "6 10 15 5" << "\n";
        }
        else if(x == 40){
            cout << "YES" << "\n" << "6 10 15 9" << "\n";
        }
        else if(x == 44){
            cout << "YES" << "\n" << "6 10 15 13" << "\n";
        }
        else{
            cout << "NO" << "\n";
        }
    }
}

