#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e5;
struct dsu{
    int p[mxN+1], sz[mxN+1];
    void init(){
        for (int i = 1; i <= mxN; i++){
            p[i] = i;
            sz[i] = 1;
        }
    }
    int find(int x){
        return (p[x]==x?x:p[x]=find(p[x]));
    }
    void join(int a, int b){
        a = find(a); b = find(b);
        p[a] = b;
        sz[b]+=sz[a];
    }
} d;
bool cmp(const pair<pair<int,int>,int> a1, const pair<pair<int,int>,int> a2) {
    return a1.first.second > a2.first.second;
}
vector<pair<int,pair<int,int>>>adj(mxN);
vector<pair<pair<int,int>,int>>qs(mxN);
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    d.init();
    freopen("mootube.in","r",stdin);
    freopen("mootube.out","w",stdout);
    int n,q; cin >> n >> q;
    qs.resize(q); adj.resize(n-1);
    for (int i = 0; i < n-1; i++){
        int u,v,w; cin >> u >> v >> w;
        adj.push_back({w,{u,v}});
    }
    for (int i = 0; i < q; i++){
        int a,b; cin >> a >> b;
        qs.push_back({{b,a},i});
    }
    sort(qs.begin(),qs.end(),cmp);
    sort(adj.begin(),adj.end());
    int iter = adj.size()-1;
    vector<int>ans(q);
    for (int i = 0; i < q; i++){
        while (iter >= 0 && adj[iter].first >= qs[i].first.second){
            d.join(adj[iter].second.first,adj[iter].second.second);
            iter--;
        }
        ans[qs[i].second] = d.sz[d.find(qs[i].first.first)]-1;
    }
    for (int i = 0; i < q; i++){
        cout << ans[i] << "\n";
    }
}

