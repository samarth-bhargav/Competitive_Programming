#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int tc; cin >> tc;
    while (tc--){
        int n; cin >> n;
        string s, t; cin >> s >> t;
        int ans = 1e9;
        for (int re = 0; re < 2; re++){
            int diff = 0;
            for (int i = 0; i < n; i++){
                if (s[i] != t[i]){
                    diff++;
                }
            }
            if (diff % 2 == 0){
                if (re == 0){
                    ans = min(ans, 2 * diff);
                }
                else{
                    ans = min(ans, max(2 * diff - 1, 2));
                }
            }
            else{
                if (re == 0){
                    ans = min(ans, 2 * diff - 1);
                }
                else{
                    ans = min(ans, 2 * diff);
                }
            }
            reverse(s.begin(), s.end());
        }
        cout << ans << "\n";
    }
}