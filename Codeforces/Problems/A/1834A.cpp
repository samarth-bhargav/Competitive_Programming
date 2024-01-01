#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n; cin >> n;
        vector<int> a(n);
        int neg = 0, pos = 0;
        for (int i = 0; i < n; i++){
            cin >> a[i];
            if (a[i] == -1) neg++;
            else pos++;
        }
        int ops = 0;
        while (neg > pos){
            neg--; pos++; ops++;
        }
        if (neg & 1){
            neg--; pos++; ops++;
        }
        cout << ops << "\n";
    }
}