#include <bits/stdc++.h>
using namespace std;

const int mxN = 3e5;
vector<pair<int,int>> edges;
vector<int> adj[mxN];

struct dsu{
    int n;
    vector<int> p;
    dsu(int n){
        this->n = n;
        p.resize(n);
        iota(p.begin(), p.end(), 0);
    }
    int find(int x){
        return x==p[x] ? p[x] : p[x] = find(p[x]);
    }
    bool join(int a, int b){
        a = find(a);
        b = find(b);
        if (a == b){
            return false;
        }
        p[a] = b;
        return true;
    }
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++){
        int a,b;
        cin >> a >> b; a--; b--;
        edges.emplace_back(a,b);
    }
    vector<int> occ(n, 0);
    int q; cin >> q;
    vector<pair<int, int>> queries;
    for (int i = 0; i < q; i++){
        int a, b;
        cin >> a >> b; a--; b--;
        occ[a]++; occ[b]++;
        queries.emplace_back(a, b);
    }
    bool possible = true;
    for (int i = 0; i < n; i++){
        possible &= (~occ[i] & 1);
    }
    if (!possible){
        cout << "NO\n";
        int num_odd = 0;
        for (int i = 0; i < n; i++){
            if (occ[i] & 1){
                num_odd++;
            }
        }
        cout << (num_odd + 1) / 2 << "\n";
    }
    else{
        //construct spanning tree
        dsu d(n);
        for (int i = 0; i < m; i++){
            if (d.join(edges[i].first, edges[i].second)){
                adj[edges[i].first].push_back(edges[i].second);
                adj[edges[i].second].push_back(edges[i].first);
            }
        }
        cout << "YES\n";
        for (int qq = 0; qq < q; qq++){
            queue<int> bfs; bfs.push(queries[qq].first);
            vector<int> parent(n, -1);
            while (!bfs.empty()){
                int tp = bfs.front();
                bfs.pop();
                for (int nbr : adj[tp]){
                    if (parent[nbr] == -1){
                        parent[nbr] = tp;
                        bfs.push(nbr);
                    }
                }
            }
            stack<int> path;
            int curr = queries[qq].second;
            while (curr != queries[qq].first){
                path.push(curr);
                curr = parent[curr];
            }
            path.push(queries[qq].first);
            cout << path.size() << "\n";
            while (!path.empty()){
                cout << path.top()+1 << " ";
                path.pop();
            }
            cout << "\n";
        }
    }
}
