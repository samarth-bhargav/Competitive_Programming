#include <bits/stdc++.h>

using namespace std;

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n; cin >> n;
        int ans = 0;
        for (int pj = 1; pj <= n; pj++){
            for (int j = 1; j <= n; j++){
                vector<int> b;
                set<int> a;
                for (int i = 1; i <= n; i++){
                    if (i != pj){
                        a.insert(i);
                    }
                    if (i != j){
                        b.push_back(i);
                    }
                }
                int temp = 0;
                for (int i = n-2; i >= 0; i--){
                    int elem1 = *prev(b.end());
                    auto it = a.lower_bound((pj * j) / elem1);
                    if (it == a.end()){
                        it--;
                    }
                    if (it == a.begin() && (*it) * elem1 > (pj * j)){
                        temp = 0;
                        break;
                    }
                    if ((*it) * elem1 > (pj * j)){
                        it--;
                    }
                    temp += (*it) * elem1;
                    a.erase(it);
                    b.pop_back();
                }
                ans = max(ans, temp);
            }
        }
        cout << ans << "\n";
    }
}