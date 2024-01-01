#include <bits/stdc++.h>

using namespace std;

vector<int> factors (int n){
    vector<int> ret;
    for (int i = 1; i * i <= n; i++){
        if (n % i == 0){
            ret.push_back(i);
            if (i * i != n){
                ret.push_back(n / i);
            }
        }
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n; cin >> n;
        vector<char> s(n, 'a');
        vector<int> f = factors(n);
        for (int i = 0; i < n; i++){
            for (int j : f){
                if (i + j < n){
                    if (s[i] == s[i + j]){
                        s[i + j]++;
                    }
                }
            }
        }
        for (int i = 0; i < n; i++){
            cout << s[i];
        }
        cout << "\n";
    }
}