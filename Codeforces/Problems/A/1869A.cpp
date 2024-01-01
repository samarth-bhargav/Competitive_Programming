#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n; cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++){
            cin >> a[i];
        }
        if (n%2 == 1){
            cout << 4 << "\n";
        }
        else{
            cout << 2 << "\n";
        }
        cout << 1 << " " << n << "\n";
        if (n % 2 == 1){
            cout << 1 << " " << n-1 << "\n";
            cout << n-1 << " " << n << "\n";
            cout << n-1 << " " << n << "\n";
        }
        else{
            cout << 1 << " " << n << "\n";
        }
    }
}