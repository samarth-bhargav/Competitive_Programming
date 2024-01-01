#include <bits/stdc++.h>

using namespace std;

#define int long long
const int M = 998244353;

struct FenwickTree {
    vector<int> bit;  // binary indexed tree
    int n;

    FenwickTree(int n) {
        this->n = n;
        bit.assign(n, 0);
    }

    FenwickTree(vector<int> const &a) : FenwickTree(a.size()) {
        for (size_t i = 0; i < a.size(); i++)
            add(i, a[i]);
    }

    int sum(int r) {
        int ret = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret += bit[r];
        return ret;
    }

    int sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }

    void add(int idx, int delta) {
        for (; idx < n; idx = idx | (idx + 1))
            bit[idx] += delta;
    }
};

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n, k; cin >> n >> k;
        vector<int> a(n), b(n);
        vector<int> index_of(n);
        for (int i = 0; i < n; i++){
            cin >> a[i];
            if (a[i] != -1) a[i]--;
            index_of[a[i]] = i;
        }
        for (int i = 0; i < n; i++){
            cin >> b[i];
            if (b[i] != -1) b[i]--;
        }
        FenwickTree used_geq(n+1);
        for (int i = 0; i < n; i++){
            if (b[i] != -1){
                used_geq.add(b[i], 1);
//                used_geq[b[i]]++;
            }
        }
//        for (int i = n-1; ~i; i--){
//            used_geq[i] += used_geq[i+1];
//        }
        int ans = 1;
        for (int i = n-1; ~i; i--){
            if (b[index_of[i]] != -1){
                used_geq.add(b[index_of[i]], -1);
                if (i - b[index_of[i]] > k) ans = 0;
                continue;
            }
            ans = (ans * (((n - 1) - max(0LL, i - k) + 1) - ((n - i - 1) + used_geq.sum(max(0LL, i-k), n)))) % M;
        }
        cout << (ans + M) % M << "\n";
    }
}