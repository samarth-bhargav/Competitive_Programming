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
        string c;
        cin >> c;
        int zero = 0;
        int one = 0;
        for (int i = 1; i < c.length()-1; ++i){
            if (c[i] == '0'){
                zero ++;
            }
            else{
                one ++;
            }
        }
        if (c[c.length() - 1] == '1' && c[0] == '1'){
            if (zero - one > 2){
                cout << 1 + one << "\n";
            }
            else{
                cout << zero << "\n";
            }
        }
        else if(c[c.length() - 1] == '0' && c[0] == '0'){
            if (one - zero > 2){
                cout << 1 + zero << "\n";
            }
            else{
                cout << one << "\n";
            }
        }
        else{
            cout << min(zero,one) << "\n";
        }
    }
}

