#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n; cin >> n;
        vector<int> a(n);
        int tot;
        for (int i = 0; i < n; i++){
            cin >> a[i];
            if (i == 0) tot = a[i];
            tot &= a[i];
        }
        if (tot > 0){
            cout << 1 << "\n";
            continue;
        }
        int ans = (a[0] == 0 ? 1 : 0);
        int curr = (a[0] == 0 ? a[1] : a[0]);
        for (int i = 1; i < n; i++){
            if ((curr & a[i]) == 0){
                ans++;
                if (i != n-1){
                    curr = a[i+1];
                }
                else{
                    curr = 0;
                }
            }
            else{
                curr &= a[i];
            }
        }
        cout << ans << "\n";
    }
}