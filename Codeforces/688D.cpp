#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
*/
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n,k;
    cin >> n >> k;
    ll crt = 1;
    for (int i = 0; i < n; i++){
        ll a; cin >> a;
        crt = ((a * crt) / __gcd(a, crt))%k;
    }
    cerr << crt << "\n";
    cout << ((crt % k == 0) ? "Yes" : "No");
}

