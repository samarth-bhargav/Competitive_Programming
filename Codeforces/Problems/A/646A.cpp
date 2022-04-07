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
        int n,x;
        cin >> n >> x;
        int even = 0;
        int odd = 0;
        for (int i = 0; i < n; i++){
            int c;
            cin >> c;
            if (c%2 == 0){
                even ++;
            }
            else{
                odd ++;
            }
        }
        if (even > 0 && odd > 0){
            if (x != n){
                cout << "Yes" << "\n";
            }
            else{
                if (odd%2 == 1){
                    cout << "Yes" << "\n";
                }
                else{
                    cout << "No" << "\n";
                }
            }
        }
        else{
            if (odd == 0){
                cout << "No" << "\n";
            }
            else{
                if (x%2 == 1){
                    cout << "Yes" << "\n";
                }
                else{
                    cout << "No" << "\n";
                }
            }
        }
    }
}

