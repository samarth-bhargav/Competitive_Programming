#include <bits/stdc++.h>

using namespace std;

#define int long long
int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int e, b, m, r, x, y, z;
    cin >> e >> b >> m >> r >> x >> y >> z;
    cout << e + (b < 0 ? b : 0) * -x + (m < 0 ? m : 0) * -y + (r < 0 ? r : 0) * -z << "\n";
}