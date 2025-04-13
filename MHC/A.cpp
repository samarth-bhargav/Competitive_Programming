#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ifstream cin("input.txt");
    ofstream cout("output.txt");

    int t; cin >> t;
    for (int tt = 0; tt < t; tt++){
        int n; cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++){
            cin >> a[i];
        }
        sort(a.begin(), a.end());
        cout << setprecision(15);
        cout << fixed;
        if (n >= 6 || n == 4){
            cout << "Case #" << tt+1 << ": " << ((double)a[n-1] + a[n-2]) / 2 - ((double)a[0] + a[1]) / 2 << "\n";
        }
        else{
            cout << "Case #" << tt+1 << ": " << max(((double)a[n-1] + a[n-3]) / 2.0 - ((double)a[0] + a[1]) / 2.0,
                                                    -((double)a[2] + a[0]) / 2.0 + ((double)a[n-1] + a[n-2]) / 2.0) << "\n";
        }
    }
}