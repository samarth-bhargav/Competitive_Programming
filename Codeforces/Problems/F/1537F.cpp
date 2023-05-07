#include <bits/stdc++.h>
using namespace std;

#define int long long
const int mxN = 2e5;
int n, m;
vector<int> st[mxN], c(mxN), a(mxN), b(mxN);

struct dsu{
    vector<int> p;
    dsu(int sz){
        p.resize(sz);
        iota(p.begin(), p.end(), 0);
    }
    int find(int x){
        return x^p[x] ? p[x] = find(p[x]) : x;
    }
    bool join(int x, int y){
        x = find(x); y = find(y);
        if (x == y){
            return false;
        }
        p[y] = x;
        return true;
    }
};

int dfs(int u, int v){
    c[u] = (c[v] == -1 ? 1 : -1);
    int delta = 0;
    for (int x: st[u]){
        if (x != v){
            delta += dfs(x, u);
        }
    }
    return b[u] - (a[u] + delta);
}

int32_t main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--){
        cin >> n >> m;
        for (int i = 0; i < n; i++){
            cin >> a[i];
        }
        for (int i = 0; i < n; i++){
            cin >> b[i];
        }
        vector<array<int, 2>> edges(m);
        for (int i = 0; i < m; i++){
            cin >> edges[i][0] >> edges[i][1];
            edges[i][0]--; edges[i][1]--;
        }
        int sum = 0;
        for (int i = 0; i < n; i++){
            sum += (a[i] - b[i]);
            sum = (sum % 2 + 2) % 2;
        }
        if (sum){
            cout << "NO\n";
            continue;
        }
        dsu d(n);
        for (int i = 0; i < m; i++){
            if (d.join(edges[i][0], edges[i][1])){
                st[edges[i][0]].push_back(edges[i][1]);
                st[edges[i][1]].push_back(edges[i][0]);
            }
        }
        //bicolor
        fill(c.begin(), c.begin()+n, 0);
        c[0] = 1;
        int delta = 0;
        for (int x : st[0]) delta += dfs(x, 0);
        bool good = false;
        for (int i = 0; i < m; i++){
            if (c[edges[i][0]] == c[edges[i][1]]){
                good = true;
                break;
            }
        }
        cout << ((delta == b[0] - a[0] || good) ? "YES\n" : "NO\n");
        for (int i = 0; i < n; i++){
            st[i].clear(); st[i].shrink_to_fit();
        }
    }
}
