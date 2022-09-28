#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main(){
    int n, k;
    vector<int> min_psum = {0};
    vector<int> max_psum = {0};
    cin >> n >> k;
    for (int i = 0; i < n; i++){
        int x; cin >> x;
        if (x == 0){
            min_psum.push_back(min_psum.back()-k);
            max_psum.push_back(max_psum.back()+k);
        }
        else{
            min_psum.push_back(min_psum.back()+x);
            max_psum.push_back(max_psum.back()+x);
        }
    }
    if (max_psum.back() < 0LL || min_psum.back() > 0LL){
        cout << -1 << "\n";
        return 0;
    }
    auto q_min = [&](int i, int j) -> int{
        return min_psum[j+1] - min_psum[i];
    };
    auto q_max = [&](int i, int j) -> int{
        return max_psum[j+1] - max_psum[i];
    };
    int ans = 0;
    for (int mn = 0; mn < n; mn++){
        for (int mx = mn+1; mx < n; mx++){
            vector<int> a(3), b(3);
            a[0] = q_min(0, mn);
            b[0] = q_max(0, mn);
            a[1] = q_min(mn+1, mx);
            b[1] = q_max(mn+1, mx);
            a[2] = -q_min(mx+1, n-1);
            b[2] = -q_max(mx+1, n-1);
            // we basically have
            // a[0] <= p[mn] <= b[0]
            // a[1] <= p[mx] - p[mn] <= b[1]
            // a[2] <= p[mx] <= b[2]
            for (int i = 0; i < 3; i++){
                if (a[i] > b[i]){
                    swap(a[i], b[i]);
                }
            }
            ans = max(ans, min(b[2] - a[0], b[1]));
        }
    }
    for (int mx = 0; mx < n; mx++){
        for (int mn = mx+1; mn < n; mn++){
            vector<int> a(3), b(3);
            a[0] = q_min(0, mx);
            b[0] = q_max(0, mx);
            a[1] = -q_max(mx+1, mn);
            b[1] = -q_min(mx+1, mn);
            a[2] = -q_min(mn+1, n-1);
            b[2] = -q_max(mn+1, n-1);
            for (int i = 0; i < 3; i++){
                if (a[i] > b[i]){
                    swap(a[i], b[i]);
                }
            }
            ans = max(ans, min(b[0] - a[2], b[1]));
        }
    }
    cout << ans+1 << "\n";
}
