#include <bits/stdc++.h>

using namespace std;

#define int long long

const int mxN = 4e5;
const int M = 1e9+7;
int fac[mxN], invf[mxN];

int n, k;
vector<int> adj[mxN];

long long binpow(long long x, int e){
    long long res = 1;
    while (e > 0){
        if (e & 1){
            res = (res * x) % M;
        }
        x = (x * x) % M;
        e >>= 1;
    }
    return (res % M + M) % M;
}

int nCr(int nn, int r){
    if (nn < 0) return 0;
    if (nn < r) return 0;
    if (r < 0) return 0;
    long long res = fac[nn];
    res *= invf[r]; res %= M;
    res *= invf[nn-r]; res = (res % M + M) % M;
    return res;
}

void precalc(){
    fac[0] = 1;
    invf[0] = binpow(fac[0], M-2);
    for (int i = 1; i <= mxN; i++){
        fac[i] = (fac[i-1] * i % M + M) % M;
        invf[i] = binpow(fac[i], M-2);
    }
}

vector<int> subtree_sizes[mxN];

int dfs(int u, int v){
    int sz = 0;
    for (int neighbor : adj[u]){
        if (neighbor != v){
            subtree_sizes[u].push_back(dfs(neighbor, u));
            sz += subtree_sizes[u].back();
        }
    }
    if (u != 0){
        subtree_sizes[u].push_back(n-(sz+1));
    }
    return sz+1;
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    precalc();

    cin >> n >> k;
    for (int i = 0; i < n-1; i++){
        int a, b;
        cin >> a >> b; a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(0, -1);
    int ans = 0;
    for (int i = 0; i < n; i++){
        vector<int> restrictions;
        int sumr = 0;
        for (int j : subtree_sizes[i]){
            restrictions.push_back(max(0LL, j - (k + 1) / 2));
            sumr += max(0LL, j - (k + 1) / 2);
        }
        ans += nCr(n, k + sumr);
        ans = (ans % M + M) % M;
    }
    ans = ans * fac[n-k]; ans = ans % M;
    ans = ans * fac[k]; ans = ans % M;
    ans = ans * invf[n]; ans = ans % M;
    cout << ans << "\n";
}