#include <bits/stdc++.h>

using namespace std;

struct st_sum{
    vector<int> t, a;
    vector<int> lazy;
    int sz;

    st_sum(vector<int> a){
        this->a = a;
        sz = this->a.size();
        t.resize(4*sz);
        lazy.resize(4*sz);
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
    void push(int v) {
        t[v*2] += lazy[v];
        lazy[v*2] += lazy[v];
        t[v*2+1] += lazy[v];
        lazy[v*2+1] += lazy[v];
        lazy[v] = 0;
    }
    void upd(int l, int r, int addend){
        upd(1, 0, sz-1, l, r, addend);
    }
    void upd(int v, int tl, int tr, int l, int r, int addend) {
        if (l > r)
            return;
        if (l == tl && tr == r) {
            t[v] += addend;
            lazy[v] += addend;
        }else {
            push(v);
            int tm = (tl + tr) / 2;
            upd(v*2, tl, tm, l, min(r, tm), addend);
            upd(v*2+1, tm+1, tr, max(l, tm+1), r, addend);
            t[v] = min(t[v*2], t[v*2+1]);
        }
    }
    int qry(int l, int r){
        return qry(1, 0, sz-1, l, r);
    }
    int qry(int v, int tl, int tr, int l, int r) {
        if (l > r)
            return 0;
        if (l == tl && r == tr)
            return t[v];
        push(v);
        int tm = (tl + tr) / 2;
        return qry(v*2, tl, tm, l, min(r, tm)) +
                   qry(v*2+1, tm+1, tr, max(l, tm+1), r);
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++){
        cin >> a[i]; a[i]--;
    }
    st_sum changes_normal(vector<int>(n, 0)), changes_rev(vector<int>(n, 0));
    for (int i = 0; i < n; i++){
        //find out "boundary points" for when a[i] - i < 0
        //boundary points happen when i = a[i]+1, i = a[i]+2 ...., i = n-1
        //these happen at cyclic (right) shifts of k = (a[i]+1-i), (a[i]+2-i), .... (n-i) (we take modulo n)
        int lb = (a[i]+1-i);
        if (lb < 0){
            lb = (lb % n + n) % n;
        }
        else if (lb + i > n-1) continue;
        int ub = n-1-i;
//        cerr << i << " " << lb << " " << ub << endl;
        if (lb > ub){
            changes_normal.upd(lb, n-1, 1);
            changes_normal.upd(0, ub, 1);
        }
        else{
            changes_normal.upd(lb, ub, 1);
        }
    }
    reverse(a.begin(), a.end());
//    cerr << endl;
//    for (int i = 0; i < n; i++){
//        cerr << a[i] << " ";
//    }
//    cerr << endl;
    for (int i = 0; i < n; i++){
        //find out "boundary points" for when a[i] - i < 0
        //boundary points happen when i = a[i]+1, i = a[i]+2 ...., i = n-1
        //these happen at cyclic shifts of k = (a[i]+1-i), (a[i]+2-i), .... (n-i) (we take modulo n)
        int lb = (a[i]+1-i);
        if (lb < 0){
            lb = (lb % n + n) % n;
        }
        else if (lb + i > n-1) continue;
        int ub = n-1-i;
//        cerr << i << " " << lb << " " << ub << endl;
        if (lb > ub){
            changes_rev.upd(lb, n-1, 1);
            changes_rev.upd(0, ub, 1);
        }
        else{
            changes_rev.upd(lb, ub, 1);
        }
    }
    vector<int> ans_normal(n), ans_rev(n);
    for (int i = 0; i < n; i++){
        ans_normal[i] = changes_normal.qry(i, i);
        ans_rev[i] = changes_rev.qry(i, i);
    }
    int cum_rotation = 0;
    cout << ans_normal[cum_rotation] << "\n";
    int q; cin >> q;
    int flipped = 1;
    for (int i = 0; i < q; i++){
        int tj; cin >> tj;
        if (tj == 3){
            flipped *= -1; cum_rotation = -cum_rotation;
        }
        else if (tj == 1){
            int k; cin >> k;
            cum_rotation += (-1) * k;
            cum_rotation = (cum_rotation % n + n) % n;
        }
        else{
            int k; cin >> k;
            cum_rotation += k;
            cum_rotation = (cum_rotation % n + n) % n;
        }
        if (flipped == -1){
            cout << ans_rev[(cum_rotation % n + n) % n] << "\n";
        }
        else{
            cout << ans_normal[(cum_rotation % n + n) % n] << "\n";
        }
    }
}