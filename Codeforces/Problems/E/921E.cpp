#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }
void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }
#define dbg(...) cerr << "LINE "<<__LINE__<<": -> [" << #__VA_ARGS__ << "]:", dbg_out(__VA_ARGS__)
#else
#define dbg(...) 7;
#endif

class Fraction {
public:
    long long numerator;
    long long denominator;

    Fraction(long long num = 1, long long denom = 1) : numerator(num), denominator(denom) {
        normalize();
    }

    void normalize() {
        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
        long long gcd = std::__gcd(numerator, denominator);
        numerator /= gcd;
        denominator /= gcd;
    }

    Fraction operator*(const Fraction& other) const {
        return Fraction(numerator * other.numerator, denominator * other.denominator);
    }

    Fraction& operator*=(const Fraction& other) {
        *this = *this * other;
        return *this;
    }
};

class SegmentTree {
private:
    int n;
    vector<long long> tree;
    vector<Fraction> lazy_mul;
    vector<long long> lazy_add;

    void build(const vector<long long>& arr, int v, int tl, int tr) {
        if (tl == tr) {
            tree[v] = arr[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(arr, v * 2 + 1, tl, tm);
            build(arr, v * 2 + 2, tm + 1, tr);
            tree[v] = tree[v * 2 + 1] + tree[v * 2 + 2];
        }
    }

    void apply(int v, int tl, int tr, const Fraction& mul, long long add) {
        tree[v] = static_cast<long long>((tree[v] / mul.denominator) * mul.numerator + (tr - tl + 1) * add);

        if (tl != tr) {
            lazy_add[v * 2 + 1] = static_cast<long long>((lazy_add[v * 2 + 1] / mul.denominator) * mul.numerator + add);
            lazy_add[v * 2 + 2] = static_cast<long long>((lazy_add[v * 2 + 2] / mul.denominator) * mul.numerator + add);
            lazy_mul[v * 2 + 1] *= mul;
            lazy_mul[v * 2 + 2] *= mul;
        }
    }

    void push(int v, int tl, int tr) {
        apply(v, tl, tr, lazy_mul[v], lazy_add[v]);
        lazy_mul[v] = Fraction(1, 1); // Reset to 1.0 for double
        lazy_add[v] = 0;
    }

    void update_range(int v, int tl, int tr, int l, int r, const Fraction& mul, long long add) {
        if (l > r) return;
        if (l == tl && r == tr) {
            push(v, tl, tr);
            apply(v, tl, tr, mul, add);
        } else {
            push(v, tl, tr);
            int tm = (tl + tr) / 2;
            update_range(v * 2 + 1, tl, tm, l, std::min(r, tm), mul, add);
            update_range(v * 2 + 2, tm + 1, tr, std::max(l, tm + 1), r, mul, add);
            tree[v] = tree[v * 2 + 1] + tree[v * 2 + 2];
        }
    }

    long long query(int v, int tl, int tr, int l, int r) {
        if (l > r) return 0;
        push(v, tl, tr);
        if (l == tl && r == tr) {
            return tree[v];
        }
        int tm = (tl + tr) / 2;
        return query(v * 2 + 1, tl, tm, l, std::min(r, tm)) + query(v * 2 + 2, tm + 1, tr, std::max(l, tm + 1), r);
    }

public:
    SegmentTree(const vector<long long>& arr) {
        n = arr.size();
        tree.assign(4 * n, 0);
        lazy_mul.assign(4 * n, Fraction()); // Initialized to Fraction(1, 1)
        lazy_add.assign(4 * n, 0);
        build(arr, 0, 0, n - 1);
    }

    void update_range_mul_add(int l, int r, const Fraction& mul, long long add) {
        update_range(0, 0, n - 1, l, r, mul, add);
    }

    long long query(int l, int r) {
        return query(0, 0, n - 1, l, r);
    }
};

struct st2{
    int n;
    vector<int> marked, t;
    vector<int> a;

    st2 (vector<int> a){
        this->a = a;
        n = a.size();
        marked.resize(4 * n, 0); t.resize(4 * n);
        build(1, 0, n-1);
    }

    void build(int v, int tl, int tr){
        if (tl == tr){
            t[v] = a[tl]; return;
        }
        int tm = (tl + tr) / 2;
        build(v*2, tl, tm);
        build(v*2+1, tm+1, tr);
    }

    void push(int v) {
        if (marked[v]) {
            t[v*2] = t[v*2+1] = t[v];
            marked[v*2] = marked[v*2+1] = true;
            marked[v] = false;
        }
    }

    void update(int v, int tl, int tr, int l, int r, int new_val) {
        if (l > r)
            return;
        if (l == tl && tr == r) {
            t[v] = new_val;
            marked[v] = true;
        } else {
            push(v);
            int tm = (tl + tr) / 2;
            update(v*2, tl, tm, l, min(r, tm), new_val);
            update(v*2+1, tm+1, tr, max(l, tm+1), r, new_val);
        }
    }

    int get(int v, int tl, int tr, int pos) {
        if (tl == tr) {
            return t[v];
        }
        push(v);
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            return get(v*2, tl, tm, pos);
        else
            return get(v*2+1, tm+1, tr, pos);
    }
    int get(int pos){
        return get(1, 0, n-1, pos);
    }
};

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m, q; cin >> n >> m >> q;
    vector<int> harbors(n, 0);
    vector<int> pos(m);
    for (int i = 0; i < m; i++){
        cin >> pos[i]; pos[i]--;
    }
    for (int i = 0; i < m; i++){
        int v; cin >> v;
        harbors[pos[i]] = v;
    }
    vector<int> h_left(n), h_right(n);
    int l = 0;
    for (int i = 0; i < n; i++){
        if (harbors[i]) l = i;
        h_left[i] = l;
    }
    int r = n-1;
    for (int i = n-1; ~i; i--){
        if (harbors[i]) r = i;
        h_right[i] = r;
    }
    vector<long long> arr(n);
    for (int i = 0; i < n; i++){
        arr[i] = (long long) harbors[h_left[i]] * (h_right[i] - i);
    }
    SegmentTree st(arr);
    st2 left(h_left), right(h_right);
    for (int i = 0; i < q; i++){
        int t, a, b; cin >> t >> a >> b; a--;
        if (t == 1){
            int c_left = left.get(a), c_right = right.get(a);
            st.update_range_mul_add(c_left+1, a, Fraction(1, 1), -(long long)(c_right - a) * harbors[c_left]);
            st.update_range_mul_add(a, c_right-1, Fraction(b, harbors[c_left]), 0);
            right.update(1, 0, n-1, c_left+1, a, a);
            left.update(1, 0, n-1, a, c_right-1, a);
            harbors[a] = b;
        }
        else{
            b--;
            cout << st.query(a, b) << "\n";
        }
    }
}