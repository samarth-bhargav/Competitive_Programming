//babybeluga
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
*/
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    int k = -1;
    cin >> n;
    vector<int>a(n);
    for (int i = 0; i < n; i++){
        cin >> a[i]; a[i]--;
        k = max(k, (a[i] - i)*2);
    }
    vector<ll>ret(n, 0); ret[0] = 1;
    for (int i = 0; i < n; i++){
        if (ret[i] == 0){
            ret[i] = ret[i-1] + 1;
        }
        if (a[i] != n-1){
            ret[a[i]+1] = ret[i] + k + 1;
        }
    }
    cout << k << "\n";
    for (int i = 0; i < n; i++){
        cout << ret[i] << "\n";
    }
}

