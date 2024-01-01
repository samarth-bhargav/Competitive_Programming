#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n, m;
        cin >> n >> m;
        long long sum1 = 0, sum2 = 0;
        for (int i = 0; i < n; i++){
            long long x; cin >> x;
            sum1 += x;
        }
        for (int i = 0; i < m; i++){
            long long x; cin >> x;
            sum2 += x;
        }
        if (sum1 == sum2){
            cout << "Draw\n";
        }
        else if (sum1 > sum2){
            cout << "Tsondu\n";
        }
        else{
            cout << "Tenzing\n";
        }
    }
}