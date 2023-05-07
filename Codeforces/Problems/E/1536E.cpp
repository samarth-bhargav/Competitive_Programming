#include <bits/stdc++.h>
using namespace std;

const int mxN = 2e3, M = 1e9+7;
string g[mxN];

long long binpow(long long a, long long b) {
    a %= M;
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % M;
        a = a * a % M;
        b >>= 1;
    }
    return res;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n, m; cin >> n >> m;
        int num_holes = 0;
        for (int i = 0; i < n; i++){
            cin >> g[i];
            num_holes += count(g[i].begin(), g[i].end(), '#');
        }
        cout << binpow(2, num_holes) - (num_holes == n * m) << "\n";
    }
}
