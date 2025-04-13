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

bool incL(const cultivar &a, const cultivar &b){
    if (a.l <= b.l){
        if (a.l == b.l){
            return a.r < b.r;
        }
        return true;
    }
    return false;
}

bool decR(const cultivar &a, const cultivar &b){
    if (a.r >= b.r){
        if (a.r == b.r){
            return a.l > b.l;
        }
        return true;
    }
    return false;
}

bool incRK(const pair<cultivar, int> &a, const pair<cultivar, int> &b){
    return (a.first.r - a.first.k) < (b.first.r - b.first.k);
}

bool incLK(const pair<cultivar, int> &a, const pair<cultivar, int> &b){
    return (a.first.l + a.first.k) < (b.first.l + b.first.k);
}

int32_t main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;
    vector<cultivar> cultivars(n);

    for (int i = 0; i < n; i++){
        cin >> cultivars[i].l >> cultivars[i].r >> cultivars[i].k;
        cultivars[i].idx = i;
    }

    sort(cultivars.begin(), cultivars.end(), incL);
    set<pair<cultivar, int>, decltype(incRK)*> active(incRK);

    vector<int> ans(n, 0);

    for (int i = 0; i < n; i++){
        while (!active.empty()){
            cultivar fir = active.begin()->first;
            if (fir.r - fir.k >= cultivars[i].l){
                break;
            }
            ans[fir.idx] += (i - active.begin()->second - 1);
            active.erase(active.begin());
        }
        active.insert(make_pair(cultivars[i], i));
    }

    while (!active.empty()){
        cultivar fir = active.begin()->first;
        ans[fir.idx] += (n - active.begin()->second - 1);
        active.erase(active.begin());
    }

    dbg("L->R Sweep Finished");
    dbg(ans);

    sort(cultivars.begin(), cultivars.end(), decR);

    set<pair<cultivar, int>, decltype(incLK)*> active2(incLK);

    for (int i = 0; i < n; i++){
        while (!active2.empty()){
            cultivar fir = prev(active2.end())->first;
            if (fir.l + fir.k <= cultivars[i].r){
                break;
            }
            ans[fir.idx] += (i - prev(active2.end())->second - 1);
            active2.erase(prev(active2.end()));
        }
        active2.insert(make_pair(cultivars[i], i));
    }

    while (!active2.empty()){
        cultivar fir = active2.begin()->first;
        ans[fir.idx] += (n - active2.begin()->second - 1);
        active2.erase(active2.begin());
    }

    dbg("R->L Sweep Finished");
    dbg(ans);

    sort(cultivars.begin(), cultivars.end(), incL);
    set<int> active_r;

    for (int i = 0; i < n; i++){
        while (!active_r.empty() && *active_r.begin() < cultivars[i].r){
            active_r.erase(active_r.begin());
        }
        ans[cultivars[i].idx] -= active_r.size();
        active_r.insert(cultivars[i].r);
    }

    for (int i = 0; i < n; i++){
        cout << ans[i] << "\n";
    }
}