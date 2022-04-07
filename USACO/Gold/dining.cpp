#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int mxN = 5e4;
int n,m,k;
vector<pair<int,int>>hbs;
vector<pair<int,int>> adj1[mxN];
vector<pair<int,int>> adj2[mxN];

int main() {
    freopen("dining.in","r",stdin);
    freopen("dining.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> k;
    for (int i = 0; i < m; i++){
        int a,b,w;
        cin >> a >> b >> w; a--; b--;
        adj1[a].emplace_back(b,w);
        adj1[b].emplace_back(a,w);
    }
    for (int i = 0; i < k; i++){
        int a,b;
        cin >> a >> b; a--;
        hbs.emplace_back(a,b);
    }
    int d[n],d1[n+1];
    memset(d,0x3f,sizeof(d)); d[n-1] = 0;
    memset(d1,0x3f,sizeof(d1)); d1[n] = 0;
    set<pair<int,int>>q; set<pair<int,int>>q1;
    q.insert({0,n-1});
    while (!q.empty()){
        pair<int,int>curr = *q.begin();
        q.erase(q.begin());
        for (auto edge: adj1[curr.second]){
            if (d[curr.second]+edge.second < d[edge.first]){
                q.erase({d[edge.first],edge.first});
                d[edge.first] = d[curr.second]+edge.second;
                q.insert({d[edge.first],edge.first});
            }
        }
    }
    for (int i = 0; i < n; i++){
        cerr << d[i] << " ";
    }
    for (int i = 0; i < n; i++){
        adj2[i] = adj1[i];
    }
    for (auto & i : hbs){
        adj2[n].push_back({i.first,d[i.first]-i.second});
    }
    q1.insert({0,n});
    while (!q1.empty()){
        pair<int,int>curr = *q1.begin();
        q1.erase(q1.begin());
        for (auto edge: adj2[curr.second]){
            if (d1[curr.second]+edge.second < d1[edge.first]){
                q1.erase({d1[edge.first],edge.first});
                d1[edge.first] = d1[curr.second]+edge.second;
                q1.insert({d1[edge.first],edge.first});
            }
        }
    }
    for (int i = 0; i < n; i++) {
        cerr << d1[i] << " ";
    }
    for (int i = 0; i < n-1; i++){
        if (d1[i] <= d[i]){
            cout << 1 << "\n";
        }
        else{
            cout << 0 << "\n";
        }
    }
}

