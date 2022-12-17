#include <bits/stdc++.h>
using namespace std;

#define int long long

const int INF = 1e18;
const int mxN = 1e5;
vector<array<int,3>> edges, mst;
map<pair<int,int>, int> edge_req;
vector<int> adj[mxN];
vector<int> c;

struct dsu{
    vector<int> p, s, ans;
    dsu(int n){
        p.resize(n);
        s.resize(n);
        ans.resize(n);
        for (int i = 0; i < n; i++){
            p[i] = i;
            s[i] = c[i];
            ans[i] = INF;
        }
    }
    int find(int x){
        return p[x] == x ? x : p[x] = find(p[x]);
    }
    bool join(int a, int b, int w){
        a = find(a);
        b = find(b);
        if (a == b){
            return false;
        }
        int ans1 = -INF, ans2 = -INF;
        if (s[a] <= ans[b]){
            ans1 = min({ans[b] - s[a], w - s[a]});
        }
        if (s[b] <= ans[a]){
            ans2 = min({w - s[b], ans[a] - s[b]});
        }
        ans[b] = max(ans1, ans2);
        p[a] = b;
        s[b] += s[a];
        return true;
    }
};

int32_t main(){
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++){
        int x; cin >> x;
        c.push_back(x);
    }
    for (int i = 0; i < m; i++){
        int a, b, w;
        cin >> a >> b >> w; a--; b--;
        edges.push_back({w, a, b});
    }
    sort(edges.begin(), edges.end());
    dsu d(n);
    for (int i = m-1; i >= 0; i--){
        d.join(edges[i][1], edges[i][2], edges[i][0]);
    }
    int v = d.find(0);
    if (d.ans[v] < 1 || d.s[v] != accumulate(c.begin(), c.end(), 0)){
        cout << -1 << "\n";
        return 0;
    }
    cout << d.ans[v] << "\n";
}