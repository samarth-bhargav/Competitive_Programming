#include <bits/stdc++.h>

using namespace std;

#define int long long

struct node{
    int sz;
    int l_restrict;
    int r_restrict;
    int both_restrict;
    int no_restrict;
    node(int x){
        l_restrict = x;
        r_restrict = x;
        both_restrict = x;
        no_restrict = x;
        sz = 1;
    }
    node(){
        sz = 0;
    }
};

node merge(node l, node r){
    if (l.sz == 0) return r;
    if (r.sz == 0) return l;
    node ret;
    if (l.sz == 1){
        if (r.sz == 1){
            ret.sz = 2;
            int l_val = l.r_restrict, r_val = r.r_restrict;
            ret.l_restrict = r_val;
            ret.r_restrict = l_val;
            ret.both_restrict = 0;
            ret.no_restrict = max(r_val, l_val);
        }
        else{
            int l_val = l.r_restrict;
            ret.l_restrict = r.no_restrict;
            ret.r_restrict = max(l_val + r.both_restrict, r.r_restrict);
            ret.both_restrict = r.r_restrict;
            ret.no_restrict = max(l_val + r.l_restrict, r.no_restrict);
        }
    }
    else if (r.sz == 1){
        int r_val = r.r_restrict;
        ret.r_restrict = l.no_restrict;
        ret.l_restrict = max(r_val + l.both_restrict, l.l_restrict);
        ret.both_restrict = l.l_restrict;
        ret.no_restrict = max(r_val + l.r_restrict, l.no_restrict);
    }
    else{
        ret.l_restrict = max(l.both_restrict + r.no_restrict, l.l_restrict + r.l_restrict);
        ret.r_restrict = max(l.no_restrict + r.both_restrict, l.r_restrict + r.r_restrict);
        ret.no_restrict = max(l.no_restrict + r.l_restrict, l.r_restrict + r.no_restrict);
        ret.both_restrict = max(l.both_restrict + r.r_restrict, l.l_restrict + r.both_restrict);
    }
    ret.sz = l.sz + r.sz;
    return ret;
}

struct st{
    int sz;
    vector<node> a;
    vector<node> t;

    st (vector<int> arr){
        sz = arr.size();
        for (int i = 0; i < sz; i++){
            a.push_back(node(arr[i]));
        }
        t.resize(4*sz);
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
        t[v] = merge(t[v*2], t[v*2+1]);
    }

    void upd(int pos, int new_val){
        upd(1, 0, sz-1, pos, new_val);
    }

    void upd(int v, int tl, int tr, int pos, int new_val){
        if (tl == tr){
            a[pos] = node(new_val);
            t[v] = a[pos];
            return;
        }
        int tm = (tl + tr) / 2;
        if (pos <= tm){
            upd(v*2, tl, tm, pos, new_val);
        }
        else{
            upd(v*2+1, tm+1, tr, pos, new_val);
        }
        t[v] = merge(t[v*2], t[v*2+1]);
    }

    node qry(int l, int r){
        return qry(1, 0, sz-1, l, r);
    }

    node qry(int v, int tl, int tr, int l, int r){
        if (tl == l && tr == r){
            return t[v];
        }
        if (l > r) return node();
        int tm = (tl + tr) / 2;
        return merge(qry(v*2, tl, tm, l, min(r, tm)),
                     qry(v*2+1, tm+1, tr, max(l, tm+1), r));
    }
};

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;
    vector<int> a(n-1);
    for (int i = 0; i < n-1; i++){
        cin >> a[i];
    }
    long long tot = accumulate(a.begin(), a.end(), 0LL) * 2;
    int q; cin >> q;
    if (n == 2 || n == 3){
        for (int i = 0; i < q; i++){
            int idx, val;
            cin >> idx >> val; idx--;
            tot += 2 * (val - a[idx]);
            cout << tot << "\n";
        }
        return 0;
    }
    st s_tree = st(vector<int> (a.begin()+1, a.end()-1));
    for (int i = 0; i < q; i++){
        int idx, val;
        cin >> idx >> val; idx--;
        tot += 2 * (val - a[idx]);
        a[idx] = val;
        if (idx == 0 || idx == n-2){
            cout << tot - 2 * s_tree.qry(0, n-4).no_restrict << "\n";
            continue;
        }
        s_tree.upd(idx-1, val);
        cout << tot - 2 * s_tree.qry(0, n-4).no_restrict << "\n";
    }
}