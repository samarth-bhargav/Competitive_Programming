#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;
    vector<int> a(2 * n - 1);
    string s; cin >> s;
    for (int i = 0; i < 2 * n - 1; i++){
        if (s[i] == 'R') a[i] = 0;
        else a[i] = 1;
    }
    vector<int> pf(2 * n); pf[0] = 0;
    for (int i = 1; i < 2 * n; i++){
        pf[i] = pf[i-1] + a[i-1];
    }
    int ans = 0;
    for (int i = n; i <= 2 * n - 1; i++){
        ans = max(ans, pf[i] - pf[i - n]);
    }
    cout << ans << "\n";
}