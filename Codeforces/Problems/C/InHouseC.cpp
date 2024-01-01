#include <bits/stdc++.h>

using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m, E, k;
    cin >> n >> m >> E >> k;
    vector<int> a(m);
    for (int i = 0; i < m; i++){
        cin >> a[i];
    }
    //choose which interval youre going to rest in and compute answer
    int maxD = 0;
    for (int i = 0; i < m-1; i++){
        maxD = max(maxD, a[i+1] - a[i]);
    }
    if (maxD > E){
        cout << 0 << "\n";
        return 0;
    }
    cout << (E - maxD) / k + 1 << "\n";
}