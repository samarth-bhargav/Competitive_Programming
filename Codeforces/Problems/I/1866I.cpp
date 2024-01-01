#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m, k;
    cin >> n >> m >> k;
    if (n == 1 && m == 1 && k == 0){
        cout << "Bhinneka\n";
        return 0;
    }
    vector<vector<int>> special(n, vector<int>());
    for (int i = 0; i < k; i++){
        int x, y;
        cin >> x >> y; x--; y--;
        special[x].push_back(y);
    }
    special[n-1].push_back(m-1);
    for (int i = 0; i < n; i++){
        sort(special[i].begin(), special[i].end());
    }
    set<int> active_columns;
    for (int i = 0; i < m; i++){
        active_columns.insert(i);
    }
    bool good = false;
    for (int i = n-1; ~i; i--){
        for (int c : special[i]){
            active_columns.erase(c);
        }
        if (active_columns.empty()) continue;
        auto it = prev(active_columns.end());
        if (*it > (special[i].empty() ? -1 : special[i].back())){
            if (i == 0 && *it == 0){
                good = true;
                break;
            }
            int col = *it;
            active_columns.erase(col);
        }
    }
    if (good){
        cout << "Bhinneka\n";
    }
    else{
        cout << "Chaneka\n";
    }
}