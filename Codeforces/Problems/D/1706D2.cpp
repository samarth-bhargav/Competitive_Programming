#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e5;
int n, k, p;
vector<int> a(mxN, -1);

int cV(int x, int d){
    p = (x + d - 1) / d > k ? k : (x + d - 1) / d;
    return (x / p);
}

int fV(int x, int d){
    p = x / d > k ? k : x / d;
    return (x / p);
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    unordered_set<int> dUsed;
    while (t--){
        cin >> n >> k;
        for (int i = 0; i < n; i++){
            cin >> a[i];
        }
        int ans = 1e9;
        set<pair<int,int>> b_a;
        for (int x = 1; x <= a[0]; x++){
            int d = dUsed.find(a[0] / x) != dUsed.end() ? -1 : a[0] / x;
            if (d == -1) {
                continue;
            }
            for (int i = 0; i < n; i++){
                b_a.insert({cV(a[i], d), fV(a[i], d)});
            }
            int max_up = -1, min_up = 1e9;
            for (auto it = b_a.begin(); it != b_a.end(); it++){
                if (it -> first > min_up){
                    break;
                }
                ans = min(ans, max(max_up, prev(b_a.end())->first) - it->first);
                max_up = max(max_up, it->second);
                min_up = min(min_up, it->second);
            }
            b_a.clear();
        }
        cout << ans << "\n";
        dUsed.clear();
    }
}
