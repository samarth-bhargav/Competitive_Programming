#include <bits/stdc++.h>
using namespace std;

#define int long long

const int M = 998244353;
const int mxN = 3e5;

long long binpow(int x, int e){
    int res = 1, curr = x;
    while (e){
        if (e & 1){
            res *= curr; res %= M;
        }
        curr = (curr * curr) % M;
        e >>= 1;
    }
    return (res % M + M) % M;
}


int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    vector<int> inv(mxN);
    for (int i = 1; i < mxN; i++){
        inv[i] = binpow(i, M-2);
    }

    int n, m; cin >> n >> m;
    int ans = 1;

    string s; cin >> s;
    bool not_zero = true;
    for (int i = 0; i < n-1; i++){
        if (s[i] == '?'){
            if (i == 0) not_zero = false;
            else{
                ans *= i; ans %= M;
            }
        }
    }
    cout << not_zero * (ans % M + M) % M << "\n";
    for (int i = 0; i < m; i++){
        int idx; char c; cin >> idx >> c; idx--;
        if (c == '?' && s[idx] != '?'){
            if (idx == 0){
                not_zero = false;
            }
            else{
                ans = ans * idx; ans %= M;
            }
        }
        else if (c != '?' && s[idx] == '?'){
            if (idx == 0){
                not_zero = true;
            }
            else{
                ans = ans * inv[idx]; ans %= M;
            }
        }
        s[idx] = c;
        cout << not_zero * (ans % M + M) % M << "\n";
    }
}