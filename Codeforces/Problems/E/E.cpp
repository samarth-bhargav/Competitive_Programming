#include <bits/stdc++.h>
using namespace std;

#define int long long
const int M = 998244353;
const int INF = 5e18;
const int B = 31;
const int mxN = 1e9;
const int mxN2 = 8e5 + 1;

int power2[mxN2];

int32_t main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    power2[0] = 1;
    for (int i = 1; i < mxN2; i++){
        power2[i] = power2[i-1] << 1;
        power2[i] = (power2[i] % M + M) % M;
    }
    int n; cin >> n;
    vector<int> repeats;
    vector<array<int, 2>> ones, twos;
    for (int i = 0; i < n; i++){
        int x; cin >> x;
        if (x == 3) repeats.push_back(i);
        else{
            int y; cin >> y;
            if (x == 1) ones.push_back({i, y});
            else twos.push_back({i, y});
        }
    }
    int ans = 0;

    vector<int> pref(n+1); pref[0] = 0;
    int twos_ptr = 0;
    for (int i = 1; i <= n; i++){
        if (twos_ptr == twos.size()){
            pref[i] = pref[i-1];
            continue;
        }
        pref[i] = pref[i-1] + (twos[twos_ptr][0] == i-1 ? twos[twos_ptr][1] : 0);
        if (twos[twos_ptr][0] == i-1){
            twos_ptr++;
        }
    }

    vector<int> inter_sums;
    int last = 0;
    for (int i = 0; i < repeats.size(); i++){
        inter_sums.push_back(pref[repeats[i] + 1] - pref[last]);
        last = repeats[i];
    }
    vector<int> backlog;
    if (inter_sums.size() != 0){
        backlog.push_back(inter_sums[0]);
        for (int i = 1; i < inter_sums.size(); i++){
            backlog.push_back(min(backlog.back() * 2 + inter_sums[i], mxN));
        }
    }

    for (int i = 0; i < ones.size(); i++){
        int idx = ones[i][0];
        int health = ones[i][1];
        array<int, 2> pop = {idx, -1};
        auto first_two = lower_bound(twos.begin(), twos.end(), pop);
        int first_rpt;
        if (pref[n] - pref[idx] >= health){
            continue;
        }
        if (lower_bound(repeats.begin(), repeats.end(), idx) == repeats.end()){
            //just evaluate till the end
            ans += (health - (pref[n] - pref[idx]) > 0 ? 1 : 0);
            ans = (ans % M + M) % M;
            continue;
        }
        if (first_two == twos.end()){
            first_rpt = lower_bound(repeats.begin(), repeats.end(), idx) - repeats.begin();
            if (backlog[first_rpt] == 0){
                ans += power2[repeats.size() - first_rpt];
                ans = (ans % M + M) % M;
                continue;
            }
            int num_valid = ((health - 1) / backlog[first_rpt]) + 1;
            ans += min(power2[repeats.size() - first_rpt], num_valid);
            ans = (ans % M + M) % M;
            continue;
        }
        else{
            first_rpt = lower_bound(repeats.begin(), repeats.end(), (*first_two)[0]) - repeats.begin();
        }



        vector<int> sums;
        int r_after_ind = lower_bound(repeats.begin(), repeats.end(), idx) - repeats.begin();
        if (first_rpt == repeats.size()){
            if (backlog[r_after_ind] == 0){
                ans += power2[repeats.size() - r_after_ind];
                ans = ((ans % M) + M) % M;
                continue;
            }
            health -= pref[n] - pref[repeats[r_after_ind]];
            int num_valid = ((health - 1) / backlog[r_after_ind]) + 1;
            ans += min(power2[repeats.size() - r_after_ind], num_valid);
            ans = ((ans % M) + M) % M;
            continue;
        }
        int rep_btw = first_rpt - r_after_ind;
        bool non_bl = false;
        if (backlog[r_after_ind] == 0){
            non_bl = true;
            last = idx;
            for (int j = 0; j < B; j++){
                if (first_rpt + j >= repeats.size()){
                    break;
                }
                sums.push_back(pref[repeats[first_rpt+j] + 1] - pref[last]);
                last = repeats[first_rpt+j];
            }
        }
        else{
            last = idx;
            for (int j = 0; j < B; j++){
                if (r_after_ind + j >= repeats.size()){
                    break;
                }
                sums.push_back(pref[repeats[r_after_ind+j] + 1] - pref[last]);
                last = repeats[r_after_ind+j];
            }
            first_rpt = r_after_ind;
        }

        //array is like sum, 3, sum, 3, . . . etc;
        //now binary search
        int lo = 0, hi = (1 << (sums.size())) - 1;
        int final = sums[0] + pref[n] - pref[repeats[first_rpt]];
        for (int j = 0; j < B; j++){
            if ((hi >> j) & 1){
                int pow2 = 1;
                for (int k = j; k > 0; k--){
                    final += pow2 * sums[k];
                    pow2 *= 2;
                }
            }
        }
        final += backlog[first_rpt] * hi;
        vector<int> chainsums;
        chainsums.push_back(sums[1]);
        for (int j = 2; j < sums.size(); j++){
            chainsums.push_back(min(INF, 2 * chainsums.back() + sums[j]));
        }
        while (lo < hi){
            int mid = (lo + hi) / 2;
            int curr = 0;
            for (int j = 0; j < B; j++){
                if ((mid >> j) & 1){
                    //add all sums
                    curr += (j == 0 ? 0 : chainsums[j-1]);
                }
            }
            curr += backlog[first_rpt] * mid;
            if (final - curr >= health){
                lo = mid+1;
            }
            else{
                hi = mid;
            }
        }
        int iters_left = ((1 << (sums.size())) - lo) * (non_bl ? power2[rep_btw] : 1);
        ans += iters_left;
        ans = ((ans % M) + M) % M;
    }
    cout << ans << "\n";
}