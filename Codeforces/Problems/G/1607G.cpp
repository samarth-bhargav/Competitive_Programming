#include <bits/stdc++.h>
using namespace std;

#define int long long
const int INF = 1e18;
int n, m;
vector<array<int, 2>> dishes;
vector<array<int, 2>> imbalances;

array<int, 2> isec(array<int, 2> i1, array<int, 2> i2){
    vector<array<int, 2>> ar = {i1, i2};
    sort(ar.begin(), ar.end());
    if (ar[0][1] < ar[1][0]){
        return {INF, INF};
    }
    return {ar[1][0], ar[0][1]};
}
int find_ans(){
    deque<array<int, 2>> f_ranges;
    f_ranges.push_back({0,0});
    for (int i = 0; i < n; i++){
        f_ranges.push_back({f_ranges[i][0]+imbalances[i][0], f_ranges[i][1]+imbalances[i][1]});
    }
    if (f_ranges.back()[0] == 0 || f_ranges.back()[1] == 0){
        return 0;
    }
    if (f_ranges.back()[0] < 0 && f_ranges.back()[1] > 0){
        return ((f_ranges.back()[0] % 2) + 2) % 2;
    }
    if (f_ranges.back()[0] < 0 && f_ranges.back()[1] < 0){
        return f_ranges.back()[1];
    }
    return f_ranges.back()[0];
}

vector<array<int, 2>> construct(int d){
    deque<array<int, 2>> f_ranges, b_ranges;
    f_ranges.push_back({0,0});
    for (int i = 0; i < n; i++){
        f_ranges.push_back({f_ranges[i][0]+imbalances[i][0], f_ranges[i][1]+imbalances[i][1]});
        sort(f_ranges.back().begin(), f_ranges.back().end());
    }
    b_ranges.push_back({d, d});
    for (int i = n-1; ~i; i--){
        array<int, 4> candidates = {b_ranges[0][0]-imbalances[i][0],
                                    b_ranges[0][1]-imbalances[i][0],
                                    b_ranges[0][0]-imbalances[i][1],
                                    b_ranges[0][1]-imbalances[i][1]};
        sort(candidates.begin(), candidates.end());
        b_ranges.push_front({candidates[0], candidates[3]});
    }
    const array<int, 2> INF_PAIR = {INF, INF};
    vector<int> balances(n+1);
    for (int i = 0; i <= n; i++){
        balances[i] = isec(f_ranges[i], b_ranges[i])[0];
        if (isec(f_ranges[i], b_ranges[i]) == INF_PAIR){
            assert(false);
        }
    }
    vector<int> balances_for_each(n);
    for (int i = 1; i <= n; i++){
        balances_for_each[i-1] = balances[i] - balances[i-1];
    }
    vector<array<int, 2>> construction;
    for (int i = 0; i < n; i++){
        int diff = dishes[i][0] - dishes[i][1];
        int diff_to_make = balances_for_each[i];
        int difference_process = diff - diff_to_make;
        //diff_1 + diff_2 = m, diff_1 - diff_2 = difference_process
        int diff_1 = (m + difference_process) / 2;
        int diff_2 = (m - difference_process) / 2;
        construction.push_back({diff_1, diff_2});
    }
    return construction;
}

int32_t main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int tt;
    cin >> tt;
    while (tt--){
        cin >> n >> m;
        dishes.resize(n);
        imbalances.resize(n);
        for (int i = 0; i < n; i++){
            cin >> dishes[i][0] >> dishes[i][1];
            int i1 = max(dishes[i][0] - m, 0LL);
            int i2 = max(dishes[i][1] - m, 0LL);
            imbalances[i] = {i1 - (dishes[i][1] - (m - (dishes[i][0] - i1))), (dishes[i][0] - (m - (dishes[i][1] - i2))) - i2};
            sort(imbalances[i].begin(), imbalances[i].end());
//            cerr << imbalances[i][0] << " " << imbalances[i][1] << "\n";
        }
        int parity = 0;
        for (int i = 0; i < n; i++){
            parity = (parity + imbalances[i][0]) % 2;
            parity = (parity + 2) % 2;
        }
        int lo = find_ans();
        cout << abs(lo) << "\n";
        vector<array<int, 2>> solution = construct(lo);
        for (int i = 0; i < n; i++){
            cout << solution[i][0] << " " << solution[i][1] << "\n";
        }
        cout << "\n";
        imbalances.clear(); imbalances.shrink_to_fit();
        dishes.clear(); dishes.shrink_to_fit();
    }
}
