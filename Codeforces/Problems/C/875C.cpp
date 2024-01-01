#include <bits/stdc++.h>

using namespace std;

const int mxN = 2e5;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n; cin >> n;
        vector<array<int,2>> edges;
        map<array<int, 2>, int> visited;
        vector<vector<array<int, 2>>> nodes(n);
        for (int i = 0; i < n-1; i++){
            int u, v;
            cin >> u >> v; u--; v--;
            edges.push_back({u, v});
            visited[{u, v}] = false;
            visited[{v, u}] = false;
            nodes[u].push_back({i, v});
            nodes[v].push_back({i, u});
        }
        for (int i = 0; i < n; i++){
            sort(nodes[i].begin(), nodes[i].end());
        }
        queue<array<int,3>> curr, nxt;
        curr.push({nodes[0][0][0], 0, nodes[0][0][1]});
        visited[{0, nodes[0][0][1]}] = true;
        visited[{nodes[0][0][1], 0}] = true;
        int cnt = 0;
        while (!curr.empty()){
            cnt++;
            while (!curr.empty()){
                array<int, 3> tp = curr.front();
                curr.pop();
                for (array<int, 2> edge : nodes[tp[1]]){
                    if (!visited[{tp[1], edge[1]}]){
                        if (edge[0] < tp[0]){
                            nxt.push({edge[0], tp[1], edge[1]});
                        }
                        else{
                            curr.push({edge[0], tp[1], edge[1]});
                        }
                    }
                    visited[{tp[1], edge[1]}] = true;
                    visited[{edge[1], tp[1]}] = true;
                }
                for (array<int, 2> edge : nodes[tp[2]]){
                    if (!visited[{tp[2], edge[1]}]){
                        if (edge[0] < tp[0]){
                            nxt.push({edge[0], tp[2], edge[1]});
                        }
                        else{
                            curr.push({edge[0], tp[2], edge[1]});
                        }
                    }
                    visited[{tp[2], edge[1]}] = true;
                    visited[{edge[1], tp[2]}] = true;
                }
            }
            swap(curr, nxt);
        }
        cout << cnt << "\n";
    }
}