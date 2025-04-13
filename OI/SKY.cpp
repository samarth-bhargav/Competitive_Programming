#include <bits/stdc++.h>

using namespace std;

int dx[8] = {0, 0, -1, 1, 1, 1, -1, -1};
int dy[8] = {1, -1, 0, 0, 1, -1, 1, -1};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, t; cin >> n >> t;
    vector<array<int, 2>> points;
    set<array<int, 3>> points_set;
    map<array<int, 2>, int> pt_to_idx;
    for (int i = 0; i < n; i++){
        int x, y; cin >> x >> y;
        points.push_back({x, y});
        points_set.insert({x, y, i});
        pt_to_idx[{x, y}] = i;
    }
    set<array<int, 2>> visited;
    vector<int> ans;
    array<int, 3> tp = *points_set.begin();
    visited.insert({tp[0], tp[1]});
    ans.push_back(tp[2]);
    points_set.erase(points_set.begin());
    set<array<int, 3>> poss;

    for (int d = 0; d < 8; d++){
        if (pt_to_idx.count({tp[0]+dx[d], tp[1]+dy[d]})){
            poss.insert({tp[0]+dx[d], tp[1]+dy[d], pt_to_idx[{tp[0]+dx[d], tp[1]+dy[d]}]});
            visited.insert({tp[0]+dx[d], tp[1]+dy[d]});
        }
    }

    while (!poss.empty()){
        tp = *poss.begin();
        poss.erase(poss.begin());
        ans.push_back(tp[2]);
        for (int d = 0; d < 8; d++){
            array<int, 2> new_pt = {tp[0] + dx[d], tp[1] + dy[d]};
            if (pt_to_idx.count(new_pt)){
                if (!visited.count(new_pt)){
                    visited.insert(new_pt);
                    poss.insert({new_pt[0], new_pt[1], pt_to_idx[new_pt]});
                }
            }
        }
    }
    if (ans.size() == n){
        cout << "YES\n";
        for (int i = 0; i < n; i++){
            cout << ans[i]+1 << "\n";
        }
    }
    else{
        cout << "NO\n";
    }
}