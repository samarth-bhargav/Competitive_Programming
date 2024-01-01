#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define ld long double

struct Line {
    mutable ld k, m, p; int i;
    bool operator<(const Line& o) const { return k < o.k; }
    bool operator<(ld x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
    // (for doubles, use inf = 1/.0, div(a,b) = a/b)
    constexpr static const ld inf = 1e18;
    ld div(ld a, ld b) {// floored division
        return a/b; }
    bool isect(iterator x, iterator y) {
        if (y == end()) return x->p = inf, 0;
        if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
        else x->p = div(y->m - x->m, x->k - y->k);
        return x->p >= y->p;
    }
    void add(ld k, ld m, int i) {
        auto z = insert({k, m, 0, i}), y = z++, x = y;
        while (isect(y, z)) z = erase(z);
        if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
        while ((y = x) != begin() && (--x)->p >= y->p)
            isect(x, erase(y));
    }
    pair<int, ll> query(ld x) {
        assert(!empty());
        auto l = *lower_bound(x);
        return {l.i, (ll)(l.k * x + l.m)};
    }
};

const int INF = 1e9;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    for (int tt = 0; tt < t; tt++){
        int n; cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++){
            cin >> a[i];
        }
        ll prod = 1;
        bool solved = false;
        for (int i = 0; i < n; i++){
            prod = prod * (ll)a[i];
            if (prod > INF){
                solved = true;
                break;
            }
        }
        if (solved){
            int i, j;
            for (i = 0; i < n; i++){
                if (a[i] != 1) break;
            }
            for (j = n-1; ~j; j--){
                if (a[j] != 1) break;
            }
            cout << i+1 << " " << j+1 << "\n";
            continue;
        }
        ll tot_sum = accumulate(a.begin(), a.end(), 0LL);

        LineContainer cht;
        cht.add(1, 0, 0);
        ll curr_ans = tot_sum, curr_i = 0, curr_j = 0;
        ll curr_pref = 0, curr_m = 1;
        for (int i = 1; i < n; i++){
            curr_pref += a[i-1];
            curr_m *= a[i-1];
            cht.add(1 / (ld)curr_m, curr_pref, i);
            auto res = cht.query(curr_m * a[i]);
            if (res.second + tot_sum - (curr_pref + a[i]) > curr_ans){
                curr_i = res.first; curr_j = i;
                curr_ans = res.second + tot_sum - (curr_pref + a[i]);
            }
        }
        cout << curr_i+1 << " " << curr_j+1 << "\n";
    }
}