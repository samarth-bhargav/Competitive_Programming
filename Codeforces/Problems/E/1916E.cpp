#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }
void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }
#define dbg(...) cerr<< "LINE "<<__LINE__<<": -> [" << #__VA_ARGS__ << "]:", dbg_out(__VA_ARGS__)
#else
#define dbg(...) 7;
#endif

typedef long long ll;

const int inf = 1e9;

struct Node {
    Node *l = 0, *r = 0;
    int lo, hi, mset = inf, madd = 0, val = -inf;
    Node(int lo,int hi):lo(lo),hi(hi){} // Large interval of -inf
    Node(vector<int>& v, int lo, int hi) : lo(lo), hi(hi) {
        if (lo + 1 < hi) {
            int mid = lo + (hi - lo)/2;
            l = new Node(v, lo, mid); r = new Node(v, mid, hi);
            val = max(l->val, r->val);
        }
        else val = v[lo];
    }
    int query(int L, int R) {
        if (R <= lo || hi <= L) return -inf;
        if (L <= lo && hi <= R) return val;
        push();
        return max(l->query(L, R), r->query(L, R));
    }
    void set(int L, int R, int x) {
        if (R <= lo || hi <= L) return;
        if (L <= lo && hi <= R) mset = val = x, madd = 0;
        else {
            push(), l->set(L, R, x), r->set(L, R, x);
            val = max(l->val, r->val);
        }
    }
    void add(int L, int R, int x) {
        if (R <= lo || hi <= L) return;
        if (L <= lo && hi <= R) {
            if (mset != inf) mset += x;
            else madd += x;
            val += x;
        }
        else {
            push(), l->add(L, R, x), r->add(L, R, x);
            val = max(l->val, r->val);
        }
    }
    void push() {
        if (!l) {
            int mid = lo + (hi - lo)/2;
            l = new Node(lo, mid); r = new Node(mid, hi);
        }
        if (mset != inf)
            l->set(lo,hi,mset), r->set(lo,hi,mset), mset = inf;
        else if (madd)
            l->add(lo,hi,madd), r->add(lo,hi,madd), madd = 0;
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while (t--){
        int n; cin >> n;
        vector<vector<int>> adj(n);
        for (int i = 1; i < n; i++){
            int x; cin >> x; x--; adj[x].push_back(i);
        }
        vector<int> a(n);
        for (int i = 0; i < n; i++){
            cin >> a[i]; a[i]--;
        }

        vector<array<int, 2>> ranges(n, {inf, -inf});

        int cnt = 0;

        auto dfs = [&](auto self, int u) -> void{
            if (adj[u].empty()){
                ranges[u] = {cnt, cnt}; cnt++;
                return;
            }
            for (int x : adj[u]){
                self(self, x);
                ranges[u][0] = min(ranges[u][0], ranges[x][0]);
                ranges[u][1] = max(ranges[u][1], ranges[x][1]);
            }
        };

        dfs(dfs, 0);

//        dbg(ranges);

        vector<int> default_vec(n, 0);
        Node st(default_vec, 0, n);

        vector<set<array<int, 2>>> updates(n);

        ll ans = 0;

        auto dfs2 = [&](auto self, int u) -> void{
            for (int x : adj[u]){
                self(self, x);
            }
            //process current color. to do this, undo all subtree colorings
            int lb = ranges[u][0];
            set<array<int, 2>> &relevant = updates[a[u]];
            vector<array<int, 2>> to_remove;

            auto it = relevant.lower_bound({lb, -inf});
            for (; it != relevant.end(); it++){
                to_remove.push_back(*it);
            }
            for (array<int, 2> x : to_remove){
                relevant.erase(x);
                st.add(x[0], x[1]+1, -1);
            }
            st.add(ranges[u][0], ranges[u][1]+1, 1);
            relevant.insert({ranges[u][0], ranges[u][1]});
            vector<int> children_maxes;
            for (int x : adj[u]){
                children_maxes.push_back(st.query(ranges[x][0], ranges[x][1]+1));
            }
            sort(children_maxes.begin(), children_maxes.end());
            if (children_maxes.size() > 1){
                ans = max(ans, (ll)children_maxes.back() * children_maxes[children_maxes.size()-2]);
            }
        };

        dfs2(dfs2, 0);

        //parent case
        for (int i = 0; i < n; i++){
            ans = max(ans, (ll)st.query(i, i+1));
        }

        cout << ans << "\n";
    }
}
