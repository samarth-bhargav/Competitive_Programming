//babybeluga
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
*/
#define int ll
signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,q;
    cin >> n >> q;
    while (n--){
        vector<int>a(q);
        for (auto & i : a){
            cin >> i;
        }
        sort(a.rbegin(),a.rend());
        cout << a[0] * a[1] << "\n";
    }
}

