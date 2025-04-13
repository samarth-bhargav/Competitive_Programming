#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n; cin >> n;
        vector<array<int, 2>> v1, v2, v3;

        int a_sum = 0, b_sum = 0;

        for (int i = 0; i < n; i++){
            int a, b; cin >> a >> b;
            a_sum += a; b_sum += b;
            if (a - b < 0){
                v1.push_back({a, b});
            }
            else if (a - b == 0){
                v3.push_back({a, b});
            }
            else{
                v2.push_back({a, b});
            }
        }

        sort(v1.begin(), v1.end(), [&](array<int, 2> &a, array<int, 2> &b){
            if (a[0] == b[0]){
                return a[1] > b[1];
            }
            return a[0] < b[0];
        });

        sort(v2.begin(), v2.end(), [&](array<int, 2> &a, array<int, 2> &b){
            if (a[1] == b[1]){
                return a[0] > b[0];
            }
            return a[1] > b[1];
        });

        sort(v3.begin(), v3.end());

        vector<array<int, 2>> v;

        for (auto x : v1){
            v.push_back(x);
        }

        for (auto x : v3){
            v.push_back(x);
        }

        for (auto x : v2){
            v.push_back(x);
        }

        vector<int> ans(n);
        int curr_a = 0, curr_b = 0;

        for (int i = 0; i < n; i++){
            curr_a += v[i][0];
            ans[i] = curr_a - curr_b;
            curr_b += v[i][1];
        }

        vector<int> p_max(n), s_max(n);
        p_max[0] = ans[0];
        for (int i = 1; i < n; i++){
            p_max[i] = max(p_max[i-1], ans[i]);
        }
        s_max[n-1] = ans[n-1];
        for (int i = n-2; ~i; i--){
            s_max[i] = max(s_max[i+1], ans[i]);
        }

        int min_ans = 1e18;

        for (int i = 0; i < n; i++){
            if (b_sum - v[i][1] >= a_sum){
                if (i == n-1){
                    min_ans = min(min_ans, p_max[i-1]);
                }
                else if (i == 0){
                    min_ans = min(min_ans, s_max[i+1] - (v[i][0] - v[i][1]));
                }
                else{
                    min_ans = min(min_ans, max(p_max[i-1], s_max[i+1] - (v[i][0] - v[i][1])));
                }
            }
        }

        if (min_ans == 1e18){
            cout << -1 << "\n";
            continue;
        }

        cout << min_ans + a_sum << "\n";
    }
}
