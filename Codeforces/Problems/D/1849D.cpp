#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    vector<int> chain = {a[0]};
    bool hasTwo = false;
    int numZeroes = (a[0] == 0);
    int ans = 0;
    //if theres ever 2 consecutive 0s, chain breaks
    for (int i = 1; i < n; i++){
        if (a[i] == 0 && a[i-1] == 0){
            //you have a chain
            if (hasTwo){
                ans += numZeroes-1;
                if (chain[0] != 0) ans++;
            }
            else{
                ans += numZeroes;
            }
            chain = {0};
            numZeroes = 1;
            hasTwo = false;
        }
        else{
            if (a[i] == 2 && i != n-1) hasTwo = true;
            else if (a[i] == 0) numZeroes++;
            chain.push_back(a[i]);
        }
    }
    if (hasTwo){
        ans += numZeroes-1;
        if (chain[0] != 0){
            ans++;
        }
        if (chain.back() != 0){
            ans++;
        }
    }
    else{
        ans += numZeroes;
        if (chain[0] != 0 && chain.back() != 0) ans++;
    }
    cout << ans << "\n";
}