#include <bits/stdc++.h>

using namespace std;

#define tcT template<class T

#define int long long

tcT> struct SimpleSegmentTree {
    int len;
    vector<T> segtree;
    vector<T> a;
    const T DEFAULT = 0;
    SimpleSegmentTree(int _len) : len(_len), segtree(_len * 2, DEFAULT), a(_len, DEFAULT){}
    SimpleSegmentTree(vector<T> a){
        this->a = a;
        len = (int)a.size();
        segtree = vector<T>(len * 2, DEFAULT);
        for (int i = 0; i < len; i++){
            set(i, a[i]);
        }
    }
    void set(int ind, T val) {
        //cerr<<"set: " << ind << " " << val << endl;
        if (ind < 0 || ind >= len) return;
        a[ind] = val;
        ind += len; segtree[ind] = val;
        for (; ind > 1; ind /= 2) segtree[ind / 2] = merge(segtree[ind], segtree[ind ^ 1]);
    }
    T query(int start, int end) {
        end++;
        //cerr<<"query: "<< start << " " << end;
        if (start >= end) return DEFAULT;
        if (end > a.size()) return DEFAULT;
        T res = DEFAULT;
        for (start += len, end += len; start < end; start /= 2, end /= 2) {
            if (start % 2 == 1) { res = merge(res, segtree[start++]); }
            if (end % 2 == 1) { res = merge(res, segtree[--end]); }
        }
        //cerr << " " << res << endl;
        return res;
    }
    T merge(T x, T y) { return x + y; }
};

using st = SimpleSegmentTree<int>;

void brute(int n, int m){
    vector<int> a(n);
    for (int i = 0; i < n; i++){
        char c; cin >> c;
        a[i] = c - 'a';
    }
    for (int q = 0; q < m; q++){
        int t; cin >> t;
        if (t == 1){
            int l, r, x; cin >> l >> r >> x; l--; r--;
            for (int j = l; j <= r; j++){
                a[j] = (a[j] + x) % 26;
            }
        }
        else{
            int l, r; cin >> l >> r; l--; r--;
            bool good = true;
            for (int i = 0; i < n-1; i++){
                if (a[i] == a[i+1]){
                    good = false;
                }
            }
            for (int i = 0; i < n-2; i++){
                if (a[i] == a[i+2]){
                    good = false;
                }
            }
            if (!good){
                cout << "NO\n";
            }
            else{
                cout << "YES\n";
            }
        }
    }
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n, m; cin >> n >> m;
        if (n <= 5){
            brute(n, m);
            continue;
        }
        vector<int> a(n);
        for (int i = 0; i < n; i++){
            char c; cin >> c;
            a[i] = c - 'a';
        }
        vector<int> twos(n-1);
        vector<int> threes(n-2);
        for (int i = 0; i < n-1; i++){
            twos[i] = (a[i] == a[i+1]);
        }
        for (int i = 0; i < n-2; i++){
            threes[i] = (a[i] == a[i+2]);
        }

        auto cong = [&](int a, int b){
            return ((a % 26) + 26) % 26 == ((b % 26) + 26) % 26;
        };

        st two_st = st(twos);
        st three_st = st(threes);
        vector<int> pf_a(n); pf_a[0] = a[0];
        for (int i = 1; i < n; i++) pf_a[i] = a[i] - a[i-1];
        st actual_vals = st(pf_a);
        for (int i = 0; i < m; i++){
            int type; cin >> type;
            if (type == 1){
                int l, r, x; cin >> l >> r >> x; l--; r--;
                actual_vals.set(l, actual_vals.query(l, l) + x);
                if (r+1 < n){
                    actual_vals.set(r+1, actual_vals.query(r+1, r+1) - x);
                }
                //check boundaries
                if (l - 2 >= 0){
                    if (cong(actual_vals.query(0, l-2), actual_vals.query(0, l))){
                        three_st.set(l-2, 1);
                    }
                    else{
                        three_st.set(l-2, 0);
                    }
                }
                if (l - 1 >= 0){
                    int val = actual_vals.query(0, l-1);
                    if (cong(val, actual_vals.query(0, l+1))){
                        three_st.set(l-1, 1);
                    }
                    else{
                        three_st.set(l-1, 0);
                    }
                    if (cong(val, actual_vals.query(0, l))){
                        two_st.set(l-1, 1);
                    }
                    else{
                        two_st.set(l-1, 0);
                    }
                }
                if (r + 1 < n){
                    int val = actual_vals.query(0,  r+1);
                    if (cong(val, actual_vals.query(0, r-1))){
                        three_st.set(r-1, 1);
                    }
                    else{
                        three_st.set(r-1, 0);
                    }
                    if (cong(val, actual_vals.query(0, r))){
                        two_st.set(r, 1);
                    }
                    else{
                        two_st.set(r, 0);
                    }
                }
                if (r + 2 < n){
                    if (cong(actual_vals.query(0, r), actual_vals.query(0, r+2))){
                        three_st.set(r, 1);
                    }
                    else{
                        three_st.set(r, 0);
                    }
                }
            }
            else{
                int l, r; cin >> l >> r; l--; r--;
                if (two_st.query(l, r-1) || three_st.query(l, r-2)){
                    cout << "NO\n";
                }
                else{
                    cout << "YES\n";
                }
            }
        }
    }
}