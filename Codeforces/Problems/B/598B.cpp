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
        int c;
        cin >> c;
        vector <int> val;
        vector <int> s;
        for (int i = 0; i < c; i++){
            int j;
            cin >> j;
            val.push_back(j);
            s.push_back(0);
        }
        for (int j = 1; j < c; j++){
            for (int i = c-2; i >= 0; i--){
                if (val[i] > val[i+1] && s[i] == 0){
                    s[i] = 1;
                    swap(val[i], val[i+1]);
                    break;
                }
            }
        }
        for (auto& i: val){
            cout << i << " ";
        }
        cout << "\n";
    }
}

