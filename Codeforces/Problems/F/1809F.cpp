#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main(){
    int t; cin >> t;
    while (t--){
        int n, k;
        cin >> n >> k;
        vector<int> a(n), f(n);
        for (int i = 0; i < n; i++){
            cin >> a[i];
        }
        for (int i = 0; i < n; i++){
            cin >> f[i];
        }
        vector<int> c(n);//chain idx
        vector<int> cval;//chain val
        vector<vector<int>> cpref;
        vector<array<int, 2>> lr;
        auto it = find(f.begin(), f.end(), 1);
        auto it2 = find(f.begin(), f.end(), 2);
        if (it != f.end() && it2 != f.end()){
            //mark first chain
            auto it3 = find(it, f.end(), 2);
            if (it3 == f.end()){
                it3 = f.begin();
            }
            int start = it3 - f.begin();
            int curr = 0, ans = 0, curr_f = k - (a[((start - 1) % n + n) % n]);
            cpref.push_back({0, a[((start - 1) % n + n) % n]});
            lr.push_back({((start - 1) % n + n) % n, 0});
            for (int i = start; i < start+n; i++){
                int idx = (i % n + n) % n;
                if (f[idx] == 1){
                    c[idx] = curr;
                    lr[curr][1] = idx;
                    cval.push_back(ans + (k - curr_f));
                    curr++; ans = 0; curr_f = k - a[idx];
                    lr.push_back({(idx % n + n) % n, 0});
                    if (i != start + n - 1){
                        cpref.push_back({0, a[idx]});
                    }
                }
                else{
                    if (curr_f < a[idx]){
                        //fill up with twos
                        ans += 2 * (a[idx] - curr_f);
                        curr_f = a[idx];
                    }
                    curr_f -= a[idx];
                    c[idx] = curr;
                    cpref[curr].push_back(cpref.back().back() + a[idx]);
                }
            }

            int cval_sum = accumulate(cval.begin(), cval.end(), 0LL);
            for (int i = 0; i < n; i++){
                int answer = cval_sum - cval[c[i]];
                //now add in own chain cost
                int l = 0, r = ((i - lr[c[i]][0]) % n + n) % n + (lr[c[i]][0] == lr[c[i]][1] && lr[c[i]][0] == i ? n : 0);
                int old_r = r;
                while (l < r){
                    int mid = (l + r + 1) / 2;
                    if (cpref[c[i]][mid] > k){
                        r = mid-1;
                    }
                    else{
                        l = mid;
                    }
                }
                if (l == old_r){
                    answer -= (k - cpref[c[i]][l]);
                }
                else{
                    answer -= 2 * (k - cpref[c[i]][l]);
                }
                answer += k + 2 * (cpref[c[i]].back() - cpref[c[i]][l]);
                cout << answer << " ";
            }
            cout << "\n";
        }
        else{
            //either all 2s or all 1s
            if (it == f.end()){
                //all 2s
                int ans = accumulate(a.begin(), a.end(), 0LL);
                for (int i = 0; i < n; i++){
                    cout << ans*2 << " ";
                }
                cout << "\n";
            }
            else{
                //all 1s
                int ans = accumulate(a.begin(), a.end(), 0LL);
                for (int i = 0; i < n; i++){
                    cout << ans << " ";
                }
                cout << "\n";
            }
        }
    }
}
