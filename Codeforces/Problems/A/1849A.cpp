#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int b, c, h;
        cin >> b >> c >> h;
        cout << min(b + b-1, 2 * (c + h) + 1) << "\n";
    }
}