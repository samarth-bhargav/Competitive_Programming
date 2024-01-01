#include <bits/stdc++.h>

using namespace std;

struct node{
    vector<int> vals;
    node(){}
    node(vector<int> vals){
        this->vals = vals;
    }
};

node merge(node a, node b){
//     assert(is_sorted(a.vals.begin(), a.vals.end()));
//     assert(is_sorted(b.vals.begin(), b.vals.end()));
    node res;
    res.vals.reserve(a.vals.size() + b.vals.size());
    int j = 0;
    for (int i = 0; i < a.vals.size(); i++){
        for (; j < b.vals.size() && b.vals[j] < a.vals[i]; j++){
            res.vals.push_back(b.vals[j]);
        }
        res.vals.push_back(a.vals[i]);
    }
    for (; j < b.vals.size(); j++){
        res.vals.push_back(b.vals[j]);
    }
//    assert(is_sorted(res.vals.begin(), res.vals.end()));
    return res;
}

struct seg{
    vector<node> t;
    int sz;
    vector<int> a;

    seg(vector<int> a){
        this->a = a;
        this->sz = a.size();
        t.resize(4 * sz);
        bld(1, 0, sz-1);
    }

    void bld(int v, int tl, int tr){
        if (tl == tr){
            t[v] = node({a[tl]});
            return;
        }
        int tm = (tl + tr) / 2;
        bld(v*2, tl, tm);
        bld(v*2+1, tm+1, tr);
        t[v] = merge(t[v*2], t[v*2+1]);
    }

    int max_under_in_range(int ub, int l, int r){
        return qry(1, 0, sz-1, l, r, ub);
    }

    int qry(int v, int tl, int tr, int l, int r, int ub){
        if (l > r) return -1;
        if (tl == l && tr == r){
            auto it = lower_bound(t[v].vals.begin(), t[v].vals.end(), ub);
            if (it == t[v].vals.begin()){
                return -1;
            }
            it--;
            return *it;
        }
        int tm = (tl + tr) / 2;
        return max(qry(v*2, tl, tm, l, min(r, tm), ub),
                   qry(v*2+1, tm+1, tr, max(l, tm+1), r, ub));
    }
};

struct seg2{
    int sz;
    vector<int> t;
    vector<int> a;

    seg2(int sz){
        this->sz = sz;
        a.resize(sz);
        t.resize(4 * sz);
        bld(1, 0, sz-1);
    }

    void bld(int v, int tl, int tr){
        if (tl == tr){
            a[tl] = 0;
            t[v] = 0;
            return;
        }
        int tm = (tl + tr) / 2;
        bld(v*2, tl, tm);
        bld(v*2+1, tm+1, tr);
        t[v] = t[v*2] + t[v*2+1];
    }

    int qry(int l, int r){
        return qry(1, 0, sz-1, l, r);
    }

    int qry(int v, int tl, int tr, int l, int r){
        if (l > r) return 0;
        if (tl == l && tr == r){
            return t[v];
        }
        int tm = (tl + tr) / 2;
        return qry(v*2, tl, tm, l, min(r, tm)) +
               qry(v*2+1, tm+1, tr, max(l, tm+1), r);
    }

    void upd(int new_pos, int val){
        upd(1, 0, sz-1, new_pos, val);
    }

    void upd(int v, int tl, int tr, int new_pos, int val){
        if (tl == tr){
            a[new_pos] = val;
            t[v] = val;
            return;
        }
        int tm = (tl + tr) / 2;
        if (new_pos <= tm){
            upd(v*2, tl, tm, new_pos, val);
        }
        else{
            upd(v*2+1, tm+1, tr, new_pos, val);
        }
        t[v] = t[v*2] + t[v*2+1];
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, q; cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    seg st(a);
    vector<int> last_occ(n+1, -1);
    vector<int> prev_l(n);
    vector<int> max_under(n);

    vector<vector<int>> y_at_x(n+1);

    for (int i = 0; i < n; i++){
        if (last_occ[a[i]] == -1){
            prev_l[i] = -1;
            max_under[i] = -1;
            last_occ[a[i]] = i;
            y_at_x[a[i]].push_back(a[i]);
            continue;
        }
        prev_l[i] = last_occ[a[i]];
        last_occ[a[i]] = i;
        max_under[i] = st.max_under_in_range(a[i], prev_l[i], i);
        if (max_under[i] != -1){
            y_at_x[max_under[i]].push_back(a[i]);
        }
    }

    map<pair<int,int>, int> ordered_queries;
    vector<int> ans(q);
    vector<vector<int>> queries(n+1);

    for (int i = 0; i < q; i++){
        int x, y; cin >> x >> y;
        queries[x].push_back(y);
        ordered_queries[{x, y}] = i;
    }

    seg2 st_sum(n+1);

    for (int c = n; c >= 0; c--){
        for (int u : y_at_x[c]){
            st_sum.upd(u, st_sum.a[u]+1);
        }
        for (int y : queries[c]){
            ans[ordered_queries[{c, y}]] = st_sum.qry(0, y);
        }
    }
    for (int i = 0; i < q; i++){
        cout << ans[i] << "\n";
    }
}