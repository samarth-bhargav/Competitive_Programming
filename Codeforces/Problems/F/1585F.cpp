#include <bits/stdc++.h>
using namespace std;

#define int long long
const int INF = 1 << 30;
const int M = 998244353;

struct st_max{
    vector<int> t, a;
    int sz;
    st_max(vector<int> a){
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
        return min(qry(v*2, tl, tm, l, min(r, tm)),
                   qry(v*2+1, tm+1, tr, max(l, tm+1), r));
    }
};

int32_t main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    int ans = 1;
    for (int i = 0; i < n; i++){
        ans *= a[i];
        ans = (ans % M + M) % M;
    }
    st_max st(a);
    for (int i = 0; i < n; i++){
        int left_greater, right_greater;
        int lo = 0, hi = i;
        while (lo < hi){
            int mid = (lo + hi) / 2;
            if (st.qry(mid, i-1) > a[i]){
                hi = mid;
            }
            else{
                lo = mid+1;
            }
        }
        left_greater = lo;
        lo = i; hi = n-1;
        while (lo < hi){
            int mid = (lo + hi + 1) / 2;
            if (st.qry(i+1, mid) >= a[i]){
                lo = mid;
            }
            else{
                hi = mid-1;
            }
        }
        right_greater = hi;
        int ld = i - left_greater + 1;
        int rd = right_greater - i + 1;
        if (ld > rd){
            swap(ld, rd);
        }

    }
    cout << ans << "\n";
}