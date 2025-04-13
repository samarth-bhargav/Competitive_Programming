#include <bits/stdc++.h>
using namespace std;


#define int long long

#ifdef LOCAL
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }
void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }
#define dbg(...) cerr << "LINE "<<__LINE__<<": -> [" << #__VA_ARGS__ << "]:", dbg_out(__VA_ARGS__)
#else
#define dbg(...) 7;
#endif

struct cultivar{
    int l, r, k;
    int idx;
};

bool incLv1(const cultivar &a, const cultivar &b){
    if (a.l <= b.l){
        if (a.l == b.l){
            return a.r < b.r;
        }
        return true;
    }
    return false;
}


bool incLv2(const cultivar &a, const cultivar &b){
    if (a.l <= b.l){
        if (a.l == b.l){
            return a.r > b.r;
        }
        return true;
    }
    return false;
}

struct FenwickTree {
    vector<int> bit;
    int n;
    FenwickTree(int n) {
        this->n = n;
        bit.assign(n, 0);
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

    int n; cin >> n;
    vector<cultivar> cultivars(n);

    for (int i = 0; i < n; i++){
        cin >> cultivars[i].l >> cultivars[i].r >> cultivars[i].k;
        cultivars[i].idx = i;
    }

    vector<int> all_pts;
    for (int i = 0; i < n; i++){
        all_pts.push_back(cultivars[i].l);
        all_pts.push_back(cultivars[i].r);
    }

    sort(all_pts.begin(), all_pts.end());
    map<int,int> coord_compress;

    for (int i = 0; i < 2 * n; i++){
        coord_compress[all_pts[i]] = i;
    }

    sort(cultivars.begin(), cultivars.end(), incLv2);

    FenwickTree active_r(2 * n);

    vector<int> ans(n, 0);

    for (int i = 0; i < n; i++){
        int coord_idx = lower_bound(all_pts.begin(), all_pts.end(), cultivars[i].l + cultivars[i].k) - all_pts.begin();
        ans[cultivars[i].idx] += active_r.sum(coord_idx, 2 * n - 1);
        active_r.add(coord_compress[cultivars[i].r], 1);
    }

    sort(cultivars.begin(), cultivars.end(), incLv1);

    vector<int> sizes;
    for (int i = 0; i < n; i++){
        sizes.push_back(cultivars[i].r - cultivars[i].l);
        sizes.push_back(cultivars[i].k);
    }

    sort(sizes.begin(), sizes.end());
    map<int,int> size_compress;

    for (int i = 0; i < 2 * n; i++){
        size_compress[sizes[i]] = i;
    }

    FenwickTree ft_size(2 * n);
    vector<array<int, 5>> events;
    for (int i = 0; i < n; i++){
        //process bigger ones first
        events.push_back({cultivars[i].l, -cultivars[i].r, cultivars[i].idx, 1, cultivars[i].k});
        if (cultivars[i].l + cultivars[i].k == cultivars[i].r){
            events.push_back({cultivars[i].r - cultivars[i].k + 1, (int)-1e18, cultivars[i].idx, 0, cultivars[i].k});
        }
        else{
            events.push_back({cultivars[i].r - cultivars[i].k, (int)1e18, cultivars[i].idx, 0, cultivars[i].k});
        }
    }

    sort(events.begin(), events.end());

    vector<int> before_counts(n);

    for (int i = 0; i < 2 * n; i++){
        if (events[i][3] == 1){
            int l = events[i][0], r = -events[i][1], idx = events[i][2];
            ft_size.add(size_compress[r - l], 1);
            before_counts[idx] = ft_size.sum(size_compress[events[i][4]], 2 * n - 1);
        }
        else if (events[i][3] == 0){
            int r = events[i][0], l = events[i][1], idx = events[i][2];
            ans[idx] += ft_size.sum(size_compress[events[i][4]], 2 * n-1) - before_counts[idx];
        }
    }

    dbg(ans);

    for (int i = 0; i < n; i++){
        cout << ans[i] << "\n";
    }
}
