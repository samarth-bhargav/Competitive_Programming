#include <bits/stdc++.h>
using namespace std;

unordered_set<int> deleted;

struct dsu{
    vector<int> p;
    vector<vector<int>> vals;
    vector<int> active;
    dsu (int n){
        p.resize(n);
        active.resize(n);
        vals.resize(n);
        for (int i = 0; i < n; i++){
            p[i] = i;
            active[i] = (deleted.find(i) == deleted.end());
            vals[i] = {i};
        }
    }
    int find(int x){
        return x == p[x] ? x : p[x] = find(p[x]);
    }
    void join(int a, int b){
        if (vals[a].size() < vals[b].size()){
            swap(a,b);
        }
        a = find(a);
        b = find(b);
        p[a] = b;
        active[b] += active[a];
        for (int x : vals[a]){
            vals[b].push_back(x);
        }
        vals[a].clear();
        vals[a].shrink_to_fit();
    }
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, q;
    cin >> n >> q;

    unordered_set<int> edges_processed;
    vector<pair<char, int>> queries;
    vector<array<int,2>> edges;
    vector<int> ans(n, -1);

    for (int i = 0; i < q; i++){
        char c; cin >> c;
        if (c == 'A'){
            int a,b; cin >> a >> b;
            edges.push_back({--a, --b});
            queries.push_back({'A', 0});
        }
        else{
            int x; cin >> x;
            queries.push_back({c, --x});
            if (c == 'D'){
                deleted.insert(x);
            }
            else{
                edges_processed.insert(x);
            }
        }
    }
    dsu d(n);
    for (int i = 0; i < edges.size(); i++){
        if (edges_processed.find(i) == edges_processed.end()){
            d.join(edges[i][0], edges[i][1]);
        }
    }
    reverse(queries.begin(), queries.end());
    for (int i = 0; i < queries.size(); i++){
        if (queries[i].first == 'R'){
            //add edge
            int idx = queries[i].second;
            int a = d.find(edges[idx][0]);
            int b = d.find(edges[idx][1]);
            bool one = (d.active[a] == 0);
            bool two = (d.active[b] == 0);
            if (one ^ two){
                if (one){
                    //everything in one turns into active
                    for (int x : d.vals[a]){
                        if (ans[x] == -1){
                            ans[x] = queries.size() - i;
                        }
                    }
                }
                else{
                    //everything in two turns active
                    for (int x : d.vals[b]){
                        if (ans[x] == -1){
                            ans[x] = queries.size() - i;
                        }
                    }
                }
            }
            d.join(edges[idx][0], edges[idx][1]);
        }
        else if (queries[i].first == 'D'){
            int a = d.find(queries[i].second);
            if (d.active[a] == 0){
                for (int x : d.vals[a]){
                    if (ans[x] == -1){
                        ans[x] = queries.size() - i;
                    }
                }
            }
            d.active[a]++;
        }
    }
    for (int i = 0; i < n; i++){
        cout << (ans[i] == -1 ? queries.size() : ans[i]-1) << "\n";
    }
}
