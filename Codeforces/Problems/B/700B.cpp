/*
Dont raise your voice,improve your argument
--Desmond Tutu
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
*/
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--){
        ll A, B; int n;
        cin >> A >> B >> n;
        vector<ll>a(n);
        vector<ll>h(n);
        for (auto & i : a){
            cin >> i;
        }
        for (auto & i : h){
            cin >> i;
        }
        ll ans = 0;
        ll maxhealthtaken = -1e9;
        for (int i = 0; i < n; i++){
            ans += ((h[i]+A-1)/A)*(a[i]);
            maxhealthtaken = max(maxhealthtaken,a[i]);
        }
        cout << (ans-maxhealthtaken > B ? "NO": "YES") << "\n";
    }
}

