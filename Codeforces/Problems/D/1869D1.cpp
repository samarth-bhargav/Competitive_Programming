#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n; cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++){
            cin >> a[i];
        }
        long long tot_sum = accumulate(a.begin(), a.end(), 0LL);
//        cerr << tot_sum << endl;
        if (tot_sum % n != 0){
            cout << "NO\n";
            continue;
        }
        int avg = tot_sum / n;
        vector<int> cnt_diff(31, 0);
        vector<int> opps_neg(31, 0), opps_pos(31, 0);
        bool bad = false;
        for (int i = 0; i < n; i++){
            int diff = abs(a[i] - avg);
            if (diff == 0) continue;
            int pos_first1 = 32 - __builtin_clz(diff);
            int pos_last1 = __builtin_ctz(diff);
//            cerr << diff << " " << pos_first1 << " " << pos_last1 << endl;
            if ((1 << pos_first1) - (1 << pos_last1) != diff){
                bad = true; break;
            }
            if (pos_first1 == pos_last1+1){
                if (a[i] < avg){
                    opps_neg[pos_last1]++;
                }
                else{
                    opps_pos[pos_last1]++;
                }
            }
            if (a[i] < avg) swap(pos_first1, pos_last1);
            cnt_diff[pos_first1]++; cnt_diff[pos_last1]--;
        }
        if (bad){
            cout << "NO\n";
            continue;
        }
        for (int i = 0; i < 30; i++){
            if (cnt_diff[i] < 0){
                for (int j = 0; j < opps_pos[i]; j++){
                    cnt_diff[i] += 2;
                    cnt_diff[i+1]--;
                    if (cnt_diff[i] >= 0) break;
                }
            }
            else if (cnt_diff[i] > 0){
                for (int j = 0; j < opps_neg[i]; j++){
                    cnt_diff[i] -= 2;
                    cnt_diff[i+1]++;
                    if (cnt_diff[i] <= 0) break;
                }
            }
            if (cnt_diff[i] != 0){
                bad = true; break;
            }
        }
        if (bad){
            cout << "NO\n";
            continue;
        }
        if (cnt_diff[30] != 0){
            cout << "NO\n";
            continue;
        }
        cout << "YES\n";
    }
}