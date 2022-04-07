/*
Dont raise your voice,improve your argument
--Desmond Tutu
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
*/
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,m;
    cin >> n >> m;
    vector<ll>a(n);
    vector<ll>b(m);
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    for (int i = 0; i < m; i++){
        cin >> b[i];
    }
    sort(a.begin(),a.end());
    if (a.size() == 1){
        for (int i = 0; i < m; i++){
            cout << a[0]+b[i] << " ";
        }
        cout << "\n";
        return 0;
    }
    ll val = a[1]-a[0];
    for (int i = 1; i < n; i++){
        val = __gcd(val,a[i]-a[i-1]);
    }
    for (int i = 0; i < m; i++){
        cout << __gcd(a[0]+b[i],val) << " ";
    }
}

