#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;
    vector<long long> a(n), b(n);
    for (int i = 0; i < n; i++){
        string x, y; cin >> x >> y;
        if (find(x.begin(), x.end(), '.') == x.end()) x += '.';
        if (find(y.begin(), y.end(), '.') == y.end()) y += '.';
        int fpoint_idx = find(x.begin(), x.end(), '.') - x.begin();
        int mv = 0;
        for (int j = fpoint_idx; j < x.size() - 1; j++){
            swap(x[j], x[j+1]);
            mv++;
        }
        x.pop_back();
        for (; mv <= 4; mv++){
            x += '0';
        }
        mv = 0;
        fpoint_idx = find(y.begin(), y.end(), '.') - y.begin();
        for (int j = fpoint_idx; j < y.size() - 1; j++){
            swap(y[j], y[j+1]);
            mv++;
        }
        y.pop_back();
        for (; mv <= 4; mv++){
            y += '0';
        }
        a[i] = stoll(x); b[i] = stoll(y);
    }
    sort(a.rbegin(), a.rend());
    sort(b.rbegin(), b.rend());

    long long ans = 0, sa = 0, sb = 0, ptr_a = 0, ptr_b = 0;
    for (long long i = 1; i <= 2 * n; i++){
        if (sa < sb && ptr_a != n){
            sa += a[ptr_a];
            ptr_a++;
        }
        else{
            sb += b[ptr_b]
            ptr_b++;
        }
        ans = max(ans, min(sa, sb) - i * 100000);
    }
    printf("%.4Lf\n", ((long double) ans) / 100000);
}