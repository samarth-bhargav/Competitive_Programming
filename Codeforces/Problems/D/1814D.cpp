#include <bits/stdc++.h>

using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n, diff; cin >> n >> diff;
        vector<int> freq(n), damage(n);
        for (int i = 0; i < n; i++){
            cin >> freq[i];
        }
        for (int i = 0; i < n; i++){
            cin >> damage[i];
        }
        vector<int> power(n);
        vector<int> sorted_power;
        for (int i = 0; i < n; i++){
            power[i] = freq[i] * damage[i];
        }
        sorted_power = power;
        sort(sorted_power.begin(), sorted_power.end());
        auto intersection = [](array<int, 2> a, array<int, 2> b){
            if (a[0] > b[0]) swap(a, b);
            if (a[1] >= b[1]) return array<int,2> {b[0], b[1]};
            if (a[1] < b[0]) return array<int,2>{-1,-1};
            if (a[1] >= b[0]) return array<int,2>{b[0], a[1]};
            return array<int,2>{-1, -1};
        };
        int ans = n;
        for (int i = 0; i < n; i++){
            //iterate through all powers
            int mid = power[i];
            int start = max(power[i] - diff, 1LL);
            int finish = power[i] + diff;
            bool bad = false;
            set<array<int, 2>> poss_starts = {{start, mid}};
            for (int j = 0; j < n; j++){
                //iterate through frequencies
                int between = (finish / freq[j] - (start - 1) / freq[j]);
                if (between == 0){
                    bad = true;
                    break;
                }
                else if (between >= 1){
                    if (between >= 4) continue;
                    vector<int> mults;
                    int curr_mult = (finish / freq[j]) * freq[j];
                    while (curr_mult >= start){
                        mults.push_back(curr_mult);
                        curr_mult -= freq[j];
                    }
                    bool temp = false;
                    set<array<int,2>> to_remove;
                    set<array<int,2>> to_insert;
                    for (int mult : mults){
                        auto it = poss_starts.lower_bound({mult+1, -1});
                        if (it == poss_starts.begin() || (*prev(it))[1] < max(mult-diff, start)){}
                        else{
                            temp = true;
                            array<int,2> curr = (*prev(it));
                            to_remove.insert(curr);
                            assert((intersection(curr, {max(mult-diff, start), mult}) != array<int,2>{-1, -1}));
                            to_insert.insert(intersection(curr, {max(mult-diff, start), mult}));
                            it = poss_starts.lower_bound({mult-diff, -1});
                            if (it == poss_starts.begin() || (*prev(it))[1] < max(mult-diff, start)){}
                            else{
                                curr = (*prev(it));
                                to_remove.insert(curr);
                                assert((intersection(curr, {max(mult-diff, start), mult}) != array<int,2>{-1, -1}));
                                to_insert.insert(intersection(curr, {max(mult-diff, start), mult}));
                            }
                        }
                    }
                    if (!temp){
                        bad = true; break;
                    }
                    for (array<int,2> x : to_remove){
                        poss_starts.erase(x);
                    }
                    //combine all to_insert ranges
                    vector<array<int,2>> final_insert;
                    for (array<int,2> x : to_insert){
                        if (final_insert.empty() || final_insert.back()[1] < x[0]){
                            final_insert.push_back(x);
                        }
                        else{
                            array<int, 2> bk = final_insert.back();
                            final_insert.pop_back();
                            final_insert.push_back({bk[0], x[1]});
                        }
                    }
                    for (array<int,2> x : final_insert){
                        poss_starts.insert(x);
                    }
                }
            }
            if (bad) continue;
            //iterate through all possible starts
            for (array<int,2> rng : poss_starts){
                for (int st = rng[0]; st <= rng[1]; st++){
                    int fin = st + diff;
                    ans = min(ans, n - (upper_bound(sorted_power.begin(), sorted_power.end(), fin) - lower_bound(sorted_power.begin(), sorted_power.end(), st)));
                    if (ans == 3){
                        cout << "hi\n";
                    }
                }
            }
        }
        cout << ans << "\n";
    }
}