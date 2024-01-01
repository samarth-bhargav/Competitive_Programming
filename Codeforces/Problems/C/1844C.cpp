#include <bits/stdc++.h>

using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n; cin >> n;
        vector<int> a, b;
        for (int i = 0; i < n; i++){
            int x; cin >> x;
            if (i%2 == 0){
                a.push_back(x);
            }
            else{
                b.push_back(x);
            }
        }
        int asum = 0, bsum = 0;
        bool pos_found = false;
        for (int i = 0; i < a.size(); i++){
            if (a[i] >= 0){
                asum += a[i];
                pos_found = true;
            }
        }
        for (int i = 0; i < b.size(); i++){
            if (b[i] >= 0){
                bsum += b[i];
                pos_found = true;
            }
        }
        if (!pos_found){
            if (b.empty()){
                cout << *max_element(a.begin(), a.end()) << "\n";
            }
            else{
                cout << max(*max_element(a.begin(), a.end()), *max_element(b.begin(), b.end())) << "\n";
            }
        }
        else{
            cout << max(asum, bsum) << "\n";
        }
    }
}