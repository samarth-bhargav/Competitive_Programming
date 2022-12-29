#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

struct st{
    int sz;
    vector<int> t, a;
    st(int n){
        this->sz = n;
        a.resize(n);
        fill(a.begin(), a.end(), 1e9);
        t.resize(4*n);
        bld(1, 0, sz-1);
    }
    void bld(int v, int tl, int tr){
        if (tl == tr){
            t[v] = a[tl];
            return;
        }
        int tm = (tl + tr) / 2;
        bld(v*2, tl, tm);
        bld(v*2+1, tm+1, tr);
        t[v] = min(t[v*2], t[v*2+1]);
    }
    int qry(int l, int r){
        return qry(1, 0, sz-1, l, r);
    }
    int qry(int v, int tl, int tr, int l, int r){
        if (l > r){
            return INF;
        }
        if (tl == l && tr == r){
            return t[v];
        }
        int tm = (tl + tr) / 2;
        int q1 = qry(v*2, tl, tm, l, min(r, tm));
        int q2 = qry(v*2+1, tm+1, tr, max(l, tm+1), r);
        return min(q1, q2);
    }
    void upd(int pos, int new_val){
        upd(1, 0, sz-1, pos, new_val);
    }
    void upd(int v, int tl, int tr, int pos, int new_val){
        if (tl == tr){
            a[pos] = new_val;
            t[v] = new_val;
            return;
        }
        int tm = (tl + tr) / 2;
        if (pos <= tm){
            upd(v*2, tl, tm, pos, new_val);
        }
        else{
            upd(v*2+1, tm+1, tr, pos, new_val);
        }
        t[v] = min(t[v*2], t[v*2+1]);
    }
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, q;
    cin >> n >> q;
    set<int> active;
    for (int i = 0; i < n; i++){
        active.insert(i);
    }
    st sick(n);
    for (int qq = 0; qq < q; qq++){
        int t; cin >> t;
        if (t == 0){
            int l, r, x;
            cin >> l >> r >> x; l--; r--;
            if (x == 0){
                auto it = active.lower_bound(l);
                while (it != active.end() && *it <= r){
                    active.erase(it);
                    it = active.lower_bound(l);
                }
            }
            if (x == 1){
                if (sick.a[l] > r){
                    sick.upd(l, r);
                }
            }
        }
        if (t == 1){
            int j; cin >> j; j--;
            auto it = active.find(j);
            if (it == active.end()){
                cout << "NO\n";
                continue;
            }
            int start_r = (it == active.begin() ? -1 : *prev(it));
            int end_r = (it == prev(active.end()) ? n : *next(it));
            if (sick.qry(start_r+1, j) < end_r){
                cout << "YES\n";
            }
            else{
                cout << "N/A\n";
            }
        }
    }
}
