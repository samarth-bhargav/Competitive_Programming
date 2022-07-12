#include <bits/stdc++.h>
using namespace std;

#define int long long

struct st{
    vector<int> t;
    vector<int> a;
    int sz;
    st(){}
    st(vector<int> a){
        this->a = a;
        this->sz = a.size();
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
        t[v] = t[v*2] + t[v*2 + 1];
    }
    int qry(int v, int tl, int tr, int l, int r){
        if (l > r){
            return 0;
        }
        if (l == tl && r == tr){
            return t[v];
        }
        int tm = (tl + tr) / 2;
        return qry(v*2, tl, tm, l, min(r, tm))
                + qry(v*2+1, tm+1, tr, max(l, tm+1), r);
    }
    int greater_than(int lb){
        return qry(1, 0, sz-1, lb+1, sz-1);
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
        t[v] = t[v*2] + t[v*2+1];
    }
    void insert(int val){
        a[val]++;
        upd(1, 0, sz-1, val, a[val]);
    }
};

int32_t main(){
    ifstream cin("haircut.in");
    ofstream cout("haircut.out");
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    int prefix[n+1];
    memset(prefix, 0, sizeof(prefix));
    st oset(vector<int> (n+1, 0));
    for (int i = 0; i < a.size(); i++){
        prefix[a[i]] += oset.greater_than(a[i]);
        oset.insert(a[i]);
    }
    int ans = 0;
    for (int i = 0; i < n; i++){
        cout << ans << "\n";
        ans += prefix[i];
    }
}