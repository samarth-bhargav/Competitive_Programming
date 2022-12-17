#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    for (int i = 0; i < t; i++){
        ull s, n, k;
        cin >> s >> n >> k;
        cout << (((n / k) * 2 * k + n % k <= s && s != k) ? "NO\n" : "YES\n");
    }
}
