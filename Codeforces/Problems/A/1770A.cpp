#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--){
        int n, m;
        cin >> n >> m;
        vector<int> a(n);
        vector<int> b(m);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        for (int i = 0; i < m; i++){
            cin >> b[i];
        }
        for (int i = 0; i < m; i++){
            int min_elem = min_element(a.begin(), a.end()) - a.begin();
            a[min_elem] = b[i];
        }
        cout << accumulate(a.begin(), a.end(), 0LL) << "\n";
    }
}
