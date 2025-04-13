#include <bits/stdc++.h>
using namespace std;

namespace internal {

#if __cplusplus >= 202002L

    using std::bit_ceil;

#else

    // @return same with std::bit::bit_ceil
unsigned int bit_ceil(unsigned int n) {
    unsigned int x = 1;
    while (x < (unsigned int)(n)) x *= 2;
    return x;
}

#endif

// @param n `1 <= n`
// @return same with std::bit::countr_zero
    int countr_zero(unsigned int n) {
#ifdef _MSC_VER
        unsigned long index;
    _BitScanForward(&index, n);
    return index;
#else
        return __builtin_ctz(n);
#endif
    }

// @param n `1 <= n`
// @return same with std::bit::countr_zero
    constexpr int countr_zero_constexpr(unsigned int n) {
        int x = 0;
        while (!(n & (1 << x))) x++;
        return x;
    }

}

template <class S,
        S (*op)(S, S),
        S (*e)(),
        class F,
        S (*mapping)(F, S),
        F (*composition)(F, F),
        F (*id)()>
struct lazy_segtree {

public:
    lazy_segtree() : lazy_segtree(0) {}
    explicit lazy_segtree(int n) : lazy_segtree(std::vector<S>(n, e())) {}
    explicit lazy_segtree(const std::vector<S>& v) : _n(int(v.size())) {
        size = (int)internal::bit_ceil((unsigned int)(_n));
        log = internal::countr_zero((unsigned int)size);
        d = std::vector<S>(2 * size, e());
        lz = std::vector<F>(size, id());
        for (int i = 0; i < _n; i++) d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) {
            update(i);
        }
    }

    void set(int p, S x) {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        d[p] = x;
        for (int i = 1; i <= log; i++) update(p >> i);
    }

    S get(int p) {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        return d[p];
    }

    S prod(int l, int r) {
        assert(0 <= l && l <= r && r <= _n);
        if (l == r) return e();

        l += size;
        r += size;

        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }

        S sml = e(), smr = e();
        while (l < r) {
            if (l & 1) sml = op(sml, d[l++]);
            if (r & 1) smr = op(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }

        return op(sml, smr);
    }

    S all_prod() { return d[1]; }

    void apply(int p, F f) {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        d[p] = mapping(f, d[p]);
        for (int i = 1; i <= log; i++) update(p >> i);
    }
    void apply(int l, int r, F f) {
//        if (!(0 <= l && l <= r && r <= _n)){
//            return;
//        }
        assert(0 <= l && l <= r && r <= _n);
        if (l == r) return;

        l += size;
        r += size;

        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }

        {
            int l2 = l, r2 = r;
            while (l < r) {
                if (l & 1) all_apply(l++, f);
                if (r & 1) all_apply(--r, f);
                l >>= 1;
                r >>= 1;
            }
            l = l2;
            r = r2;
        }

        for (int i = 1; i <= log; i++) {
            if (((l >> i) << i) != l) update(l >> i);
            if (((r >> i) << i) != r) update((r - 1) >> i);
        }
    }

    template <bool (*g)(S)> int max_right(int l) {
        return max_right(l, [](S x) { return g(x); });
    }
    template <class G> int max_right(int l, G g) {
        assert(0 <= l && l <= _n);
        assert(g(e()));
        if (l == _n) return _n;
        l += size;
        for (int i = log; i >= 1; i--) push(l >> i);
        S sm = e();
        do {
            while (l % 2 == 0) l >>= 1;
            if (!g(op(sm, d[l]))) {
                while (l < size) {
                    push(l);
                    l = (2 * l);
                    if (g(op(sm, d[l]))) {
                        sm = op(sm, d[l]);
                        l++;
                    }
                }
                return l - size;
            }
            sm = op(sm, d[l]);
            l++;
        } while ((l & -l) != l);
        return _n;
    }

    template <bool (*g)(S)> int min_left(int r) {
        return min_left(r, [](S x) { return g(x); });
    }
    template <class G> int min_left(int r, G g) {
        assert(0 <= r && r <= _n);
        assert(g(e()));
        if (r == 0) return 0;
        r += size;
        for (int i = log; i >= 1; i--) push((r - 1) >> i);
        S sm = e();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!g(op(d[r], sm))) {
                while (r < size) {
                    push(r);
                    r = (2 * r + 1);
                    if (g(op(d[r], sm))) {
                        sm = op(d[r], sm);
                        r--;
                    }
                }
                return r + 1 - size;
            }
            sm = op(d[r], sm);
        } while ((r & -r) != r);
        return 0;
    }

private:
    int _n, size, log;
    std::vector<S> d;
    std::vector<F> lz;

    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
    void all_apply(int k, F f) {
        d[k] = mapping(f, d[k]);
        if (k < size) lz[k] = composition(f, lz[k]);
    }
    void push(int k) {
        all_apply(2 * k, lz[k]);
        all_apply(2 * k + 1, lz[k]);
        lz[k] = id();
    }
};

namespace lazy_seg_var{
    struct F{
        int addend;
    };
    int op(int a, int b){
        return max(a, b);
    }
    F id(){
        return F{0};
    }
    int e(){
        return 0;
    }
    int mapping(F f, int x){
        return x + f.addend;
    }
    F composition(F a, F b){
        return F{a.addend + b.addend};
    }
}

typedef lazy_seg_var::F F;

const int SQRT = 700;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while (t--){
        int n, q, k; cin >> n >> q >> k;
        vector<int> a(n);
        for (int i = 0; i < n; i++){
            cin >> a[i];
        }
        struct query{
            int lo, hi, idx;
            query(int lo, int hi, int idx){
                this->lo = lo;
                this->hi = hi;
                this->idx = idx;
            }
            bool operator <(const query &o) const{
                if (lo / SQRT != o.lo / SQRT){
                    return lo / SQRT < o.lo / SQRT;
                }
                return ((lo / SQRT) & 1) ? hi < o.hi : o.hi < hi;
            }
        };
        vector<query> queries;
        vector<int> parity(q);
        for (int i = 0; i < q; i++){
            int l, r; cin >> l >> r; l--; r--;
            queries.push_back(query(l,r,i));
            parity[i] = (r - l + 1) % 2;
        }
        sort(queries.begin(), queries.end());

        int kSQRT = sqrt(k);
        if ((kSQRT + 1) * (kSQRT + 1) == k){
            kSQRT++;
        }
        int exact_flag = (kSQRT * kSQRT == k);

        lazy_segtree<int,
        lazy_seg_var::op,
        lazy_seg_var::e,
        lazy_seg_var::F,
        lazy_seg_var::mapping,
        lazy_seg_var::composition,
        lazy_seg_var::id> seg(kSQRT + 1);

        multiset<int> above;
        multiset<int> below;

        auto add = [&](int x){
            if (exact_flag && x == kSQRT){
                if (seg.get(kSQRT) - seg.get(kSQRT-1) == 0){
                    seg.apply(kSQRT, lazy_seg_var::F{1});
                    above.insert(x);
                }
                else{
                    seg.apply(kSQRT, lazy_seg_var::F{-1});
                    if (above.find(x) != above.end()){
                        above.erase(above.find(x));
                    }
                }
                return;
            }
            if (x <= kSQRT){
                seg.apply(x, kSQRT+1, lazy_seg_var::F{-1});
                below.insert(x);
            }
            else{
                seg.apply(k / x, kSQRT+1, lazy_seg_var::F{1});
                above.insert(x);
            }
        };

        auto remove = [&](int x){
            if (exact_flag && x == kSQRT){
                if (seg.get(kSQRT) - seg.get(kSQRT-1) == 0){
                    seg.apply(kSQRT, lazy_seg_var::F{1});
                    above.insert(x);
                }
                else{
                    seg.apply(kSQRT, lazy_seg_var::F{-1});
                    if (above.find(x) != above.end()){
                        above.erase(above.find(x));
                    }
                }
                return;
            }
            if (x <= kSQRT){
                seg.apply(x, kSQRT+1, lazy_seg_var::F{1});
                if (below.find(x) != below.end()){
                    below.erase(below.find(x));
                }
            }
            else{
                seg.apply(k / x, kSQRT+1, lazy_seg_var::F{-1});
                if (above.find(x) != above.end()){
                    above.erase(above.find(x));
                }
            }
        };

        vector<int> answers(q);

        int numSQRT = 0;

        int l = -1, r = -1;
        for (query Query : queries){
            while (r < Query.hi){
                r++;
                add(a[r]);
                if (a[r] == kSQRT && exact_flag){
                    numSQRT++;
                }
            }
            while (l > Query.lo){
                l--;
                add(a[l]);
                if (a[l] == kSQRT && exact_flag){
                    numSQRT++;
                }
            }
            while (r > Query.hi){
                remove(a[r]);
                if (a[r] == kSQRT && exact_flag){
                    numSQRT--;
                }
                r--;
            }
            while (l < Query.lo){
                if (l >= 0){
                    remove(a[l]);
                    if (a[l] == kSQRT && exact_flag){
                        numSQRT--;
                    }
                }
                l++;
            }
            answers[Query.idx] = seg.all_prod();
            if (above.size() + below.size() <= 1){
                if (above.size() + below.size() == 0){
                    answers[Query.idx] = 0;
                    continue;
                }
                if (below.size() == 1){
                    answers[Query.idx] = 0;
                    continue;
                }
                else{
                    if (*above.begin() == kSQRT && exact_flag){
                        answers[Query.idx] = 0;
                    }
                    else{
                        answers[Query.idx] = 1;
                    }
                    continue;
                }
            }
            if (parity[Query.idx] && ((numSQRT & 1) || numSQRT == 0) && (above.size() - answers[Query.idx] / 2) == (Query.hi - Query.lo + 1 + 1 - (numSQRT - (numSQRT & 1))) / 2 &&
                above.size() != 0 && *above.begin() * (below.size() == 0 ? 1 : *prev(below.end())) <= k
                && seg.get(k / *above.begin()) == answers[Query.idx] && seg.prod(0, k / *above.begin()) < answers[Query.idx]){
                answers[Query.idx]--;
            }
        }

        for (int i = 0; i < q; i++){
            cout << (max(answers[i], 0) + 1) / 2 << " ";
        }
        cout << "\n";

    }
}