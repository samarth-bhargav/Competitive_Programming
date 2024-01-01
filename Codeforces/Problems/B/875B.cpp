#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n; cin >> n;
        vector<int> a(n), b(n);
        map<int,int> mp, mp1;
        for (int i = 0; i < n; i++){
            cin >> a[i];
        }
        for (int i = 0; i < n; i++){
            cin >> b[i];
        }
        int curr = a[0];
        int run = 1;
        for (int i = 1; i < n; i++){
            if (a[i] == curr){
                run++;
            }
            else{
                mp[curr] = max(mp[curr], run);
                run = 1;
                curr = a[i];
            }
        }
        mp[curr] = max(mp[curr], run);
        curr = b[0];
        run = 1;
        for (int i = 1; i < n; i++){
            if (b[i] == curr){
                run++;
            }
            else{
                mp1[curr] = max(mp1[curr], run);
                run = 1;
                curr = b[i];
            }
        }
        mp1[curr] = max(mp1[curr], run);
        int ans = 0;
        for (pair<int,int> elem : mp){
            ans = max(ans, elem.second + mp1[elem.first]);
        }
        for (pair<int,int> elem : mp1){
            ans = max(ans, elem.second + mp[elem.first]);
        }
        cout << ans << "\n";
    }
}