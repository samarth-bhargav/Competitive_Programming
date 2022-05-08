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
        vector <int> vi;
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i){
            int c;
            cin >> c;
            vi.push_back(c);
        }
        sort(vi.begin(), vi.end());
        int gran = vi.size() + 1;
        for (int i = vi.size() - 1; i >= 0; i--){
            if (vi[i] > i + 1){
                gran --;
            }
            else{
                break;
            }
        }
        cout << gran << "\n";
    }
}

