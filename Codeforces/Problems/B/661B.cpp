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
        vector <int> a;
        vector <int> b;
        for(int i = 0; i < n; i++){
            int x;
            cin >> x;
            a.push_back(x);
        }
        for (int i = 0; i < n; i++){
            int x;
            cin >> x;
            b.push_back(x);
        }
        int minela = 1000000007;
        int minelb = 1000000007;
        for (int i = 0; i < n; i++){
            minela = min(minela, a[i]);
        }
        for (int i = 0; i < n; i++){
            minelb = min(minelb, b[i]);
        }
        vector <int> avals;
        vector <int> bvals;
        for (int i = 0; i < n; i++){
            avals.push_back(a[i] - minela);
            bvals.push_back(b[i] - minelb);
        }
        long long ans = 0;
        for (int i = 0; i < n; i++){
            ans += (avals[i] + bvals[i] - min(avals[i], bvals[i]));
        }
        cout << ans << "\n";
    }
}

