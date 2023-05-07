#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll

struct st{
    vector<int> t;
    vector<int> a;
    int sz;

    st(int sz){
        this->sz = sz;
        t.resize(4*sz);
        a.resize(sz);
        fill(a.begin(), a.end(), 0);
        fill(t.begin(), t.end(), 0);
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

    void upd(int pos, int new_val){
        upd(1, 0, sz-1, pos, new_val);
    }

    int qry(int v, int tl, int tr, int l, int r){
        if (l > r) return 0;
        if (tl == l && tr == r) return t[v];
        int tm = (tl + tr) / 2;
        return qry(v*2, tl, tm, l, min(r, tm))
             + qry(v*2+1, tm+1, tr, max(l, tm+1), r);
    }

    int qry(int l, int r){
        return qry(1, 0, sz-1, l, r);;
    }
};

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    vector<ll> ps(n+1); ps[0] = 0;
    for (int i = 0; i < n; i++){
        ps[i+1] = ps[i] + a[i];
        if (ps[i+1] < 0){
            cout << -1 << "\n";
            return 0;
        }
        if (i == n-1 && *max_element(ps.begin(), ps.end()) != ps[i+1]){
            cout << -1 << "\n";
            return 0;
        }
    }
    map<ll, int> cc;
    vector<ll> ps_cpy(ps.begin(), ps.end());
    sort(ps_cpy.begin(), ps_cpy.end());
    for (int i = 0; i < ps_cpy.size(); i++){
        cc[ps_cpy[i]] = i;
    }
//    for (int i = 1; i <= n; i++){
//        cerr << ps[i] << " ";
//    }
//    cerr << endl;
//    for (auto &x : cc){
//        cerr << x.first << " " << x.second << "\n";
//    }
//    cerr << endl;
    st st_max(n+1);
    ll ans = 0;
    for (int i = 0; i < n; i++){
        //look at ps[i+1]!!
        ans += st_max.qry(cc[ps[i+1]]+1, n);
        st_max.upd(cc[ps[i+1]], st_max.a[cc[ps[i+1]]]+1);
    }
    cout << ans << "\n";
}
