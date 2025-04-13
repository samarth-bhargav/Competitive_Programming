#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main(){
    int n, k; cin >> n >> k;
    vector<int> a(n), b(n);
    for (int &x : a) cin >> x;
    for (int &x : b) cin >> x;

    if (accumulate(a.begin(), a.end(), 0LL) != accumulate(b.begin(), b.end(), 0LL)){
        cout << "NO\n";
        return 0;
    }
    for (int i = 0; i < n; i++){
        if (a[i] % k != b[i] % k){
            cout << "NO\n";
            return 0;
        }
    }
    cout << "YES\n";
    int sum = 0;
    for (int i = 0; i < n; i++){
        sum += abs((a[i] - b[i]) / k);
    }
    cout << sum / 2 << "\n";
}