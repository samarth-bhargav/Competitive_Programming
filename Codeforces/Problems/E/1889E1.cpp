#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n, m, k; cin >> n >> m >> k;
        vector<array<int, 2>> intervals(m);
        for (int i = 0; i < m; i++){
            cin >> intervals[i][0] >> intervals[i][1];
            intervals[i][0]--; intervals[i][1]--;
        }
        sort(intervals.begin(), intervals.end());
        set<array<int, 2>> active_endpoints; //pos, idx
        int curr_idx = 0;

        vector<vector<int>> cover(n);

        int global = 0;

        for (int i = 0; i < n; i++){
            while (curr_idx < m && intervals[curr_idx][0] <= i){
                active_endpoints.insert({intervals[curr_idx][1], curr_idx});
                curr_idx++;
            }
            while (!active_endpoints.empty() && (*active_endpoints.begin())[0] < i){
                active_endpoints.erase(active_endpoints.begin());
            }
            if (active_endpoints.empty()){
                global++;
            }
            else if (active_endpoints.size() < 3){
                for (auto arr : active_endpoints){
                    cover[i].push_back(arr[1]);
                }
                sort(cover[i].begin(), cover[i].end());
            }
        }

        map<int, int> one_cover;
        map<vector<int>, int> two_cover;

        for (int i = 0; i < n; i++){
            if (cover[i].size() == 1){
                one_cover[cover[i][0]]++;
            }
            else if (cover[i].size() == 2){
                two_cover[cover[i]]++;
            }
        }

        int max_one_cover = 0;
        set<pair<int,int>> sorted_one_cover;
        for (auto arr : one_cover){
            sorted_one_cover.insert({arr.second, arr.first});
        }
        if (sorted_one_cover.size() > 0){
            max_one_cover += prev(sorted_one_cover.end())->first;
        }
        if (sorted_one_cover.size() > 1){
            max_one_cover += prev(prev(sorted_one_cover.end()))->first;
        }
        int ans = max_one_cover;
        for (auto pr : two_cover){
            ans = max(ans, pr.second + one_cover[pr.first[0]] + one_cover[pr.first[1]]);
        }
        cout << ans + global << "\n";
    }
}