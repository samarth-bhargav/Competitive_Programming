#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9+7;

struct st_min{
    vector<int> t, a;
    vector<int> lazy;
    int sz;

    st_min(vector<int> a){
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
            return INF;
        if (l <= tl && tr <= r)
            return t[v];
        push(v);
        int tm = (tl + tr) / 2;
        return min(qry(v*2, tl, tm, l, min(r, tm)),
                   qry(v*2+1, tm+1, tr, max(l, tm+1), r));
    }
};

struct FenwickTree {
    vector<int> bit;  // binary indexed tree
    int n;

    FenwickTree(int n) {
        this->n = n;
        bit.assign(n, 0);
    }

    FenwickTree(vector<int> a) : FenwickTree(a.size()) {
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

int32_t main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--){
        int n, m;
        cin >> n >> m;
        vector<int> a(n), b(m);
        for (auto &i : a){
            cin >> i;
        }
        for (auto &i : b){
            cin >> i;
        }
        sort(b.begin(), b.end());
        //get initial for first elem
        int pref[n+1], suf[n+1];
        pref[0] = 0; suf[n] = 0;
        for (int i = 1; i <= n; i++){
            pref[i] = pref[i-1] + (a[i-1] > b[0]);
        }
        for (int i = n-1; ~i; i--){
            suf[i] = suf[i+1] + (a[i] < b[0]);
        }
        vector<int> vals(n+1);
        for (int i = 0; i <= n; i++){
            vals[i] = pref[i] + suf[i];
        }
//        for (int i = 0; i <= n; i++){
//            cerr << vals[i] << " ";
//        }
//        cerr << "\n";
        st_min st(vals);
        map<int, vector<int>> freq;
        for (int i = 0; i < n; i++){
            freq[a[i]].push_back(i);
        }
        long long ans = st.qry(0, n);
        long long prev_ans = ans;
        auto lb = freq.lower_bound(b[0]);
        for (int i = 1; i < m; i++){
            if (b[i] == b[i-1]){
                ans += prev_ans;
                continue;
            }
            lb = freq.lower_bound(b[i-1]);
            while (lb != freq.end() && lb->first <= b[i]){
                for (int idx : lb->second){
                    if (lb->first == b[i-1]){
                        //b[i-1] went from being considered equal to now less
                        st.upd(0, idx, 1);
                    }
                    else if (lb->first == b[i]){
                        //b[i] went from being considered greater to now equal
                        st.upd(idx+1, n, -1);
                    }
                    else{
                        st.upd(idx+1, n, -1);
                        st.upd(0, idx, 1);
                    }
                }
                lb++;
            }
            prev_ans = st.qry(0, n);
            ans += prev_ans;
        }


        //add original inversions of a!!
        vector<int> a_cpy = a;
        sort(a_cpy.begin(), a_cpy.end());
        vector<int> acc_pos(n);
        for (int i = 0; i < n; i++){
            acc_pos[i] = lower_bound(a_cpy.begin(), a_cpy.end(), a[i]) - a_cpy.begin();
            //relative positions
        }
        vector<int> frequencies(n, 0);
        for (int i = 0; i < n; i++){
            frequencies[acc_pos[i]]++;
        }
        FenwickTree inversion(frequencies);
        for (int i = 0; i < n; i++){
            ans += inversion.sum(acc_pos[i]-1);
            inversion.add(acc_pos[i], -1);
        }
//        cerr << "hi\n";
        cout << ans << "\n";
    }
}
