#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t, m; cin >> t >> m;
    while (t--){
        int n; cin >> n;
        struct rect{
            int x1, y1, x2, y2;
            rect(int x1, int y1, int x2, int y2){
                this->x1 = x1;
                this->y1 = y1;
                this->x2 = x2;
                this->y2 = y2;
            }
            rect(){}
        };
        vector<rect> rects(n);
        for (int i = 0; i < n; i++){
            cin >> rects[i].x1 >> rects[i].y1 >> rects[i].x2 >> rects[i].y2;
        }
        auto inside = [&](rect a, rect b){
            return a.x1 < b.x2 && a.y1 < b.y2;
        };
        vector<vector<int>> adj(n);
        vector<int> in_deg(n);
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                if (i != j){
                    if (inside(rects[i], rects[j])){
                        adj[i].push_back(j);
                        in_deg[j]++;
                    }
                }
            }
        }
        if (m == 1){
            vector<int> topo_sort;
            queue<int> nodes;
            for (int i = 0; i < n; i++){
                if (in_deg[i] == 0){
                    nodes.push(i);
                }
            }
            while (!nodes.empty()){
                int tp = nodes.front();
                topo_sort.push_back(tp);
                nodes.pop();
                for (int j : adj[tp]){
                    in_deg[j]--;
                    if (in_deg[j] == 0){
                        nodes.push(j);
                    }
                }
            }
            for (int x : topo_sort){
                cout << x+1 << " ";
            }
            cout << "\n";
        }
        else{
            for (int i = 0; i < n; i++){
                if (in_deg[i] == 0){
                    cout << 1;
                }
                else{
                    cout << 0;
                }
                for (int j : adj[i]){
                    in_deg[j]--;
                }
            }
            cout << "\n";
        }
    }
}