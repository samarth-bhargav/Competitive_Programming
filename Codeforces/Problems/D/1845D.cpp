#include <bits/stdc++.h>

using namespace std;

#define int long long
const int INF = 1e18;

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n; cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++){
            cin >> a[i];
        }
        vector<int> b;
        bool pos = (a[0] > 0);
        int currsum = 0;
        for (int i = 0; i < n; i++){
            if ((a[i] > 0) == pos){
                currsum += a[i];
            }
            else{
                b.push_back(currsum);
                currsum = a[i];
                pos ^= 1;
            }
        }
        b.push_back(currsum);
        n = b.size();
        vector<int> p(n+1); p[0] = 0;
        for (int i = 1; i <= n; i++){
            p[i] = p[i-1] + b[i];
        }
        for (int i = 0; i < n; i++){
            if (p[i] >= 0){

            }
        }
    }
}