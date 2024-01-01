#include <bits/stdc++.h>

using namespace std;

struct FenwickTree2D {
    vector<vector<int>> bit;
    int n, m;

    FenwickTree2D(int n, int m){
        this->n = n; this->m = m;
        bit = vector<vector<int>>(n, vector<int>(m, 0));
    }

    int sum(int x, int y) {
        int ret = 0;
        for (int i = x; i >= 0; i = (i & (i + 1)) - 1)
            for (int j = y; j >= 0; j = (j & (j + 1)) - 1)
                ret += bit[i][j];
        return ret;
    }

    void add(int x, int y, int delta) {
        for (int i = x; i < n; i = i | (i + 1))
            for (int j = y; j < m; j = j | (j + 1))
                bit[i][j] += delta;
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n; cin >> n;
        int a[n][n];
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                char c; cin >> c;
                a[i][j] = c - '0';
            }
        }
        FenwickTree2D ft(2 * n, 2 * n);
        int ops = 0;

        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                int minus = i - j + n;
                int plus = i + j;
                if (ft.sum(minus, plus) % 2 != a[i][j]){
                    ft.add(minus, plus, 1);
                    ops++;
                }
            }
        }
        cout << ops << "\n";
    }
}