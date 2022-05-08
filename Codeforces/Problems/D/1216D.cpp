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
    int n;
    cin >> n;
    vector<ll>a(n);
    for (auto & i : a){
        cin >> i;
    }
    ll x = *max_element(a.begin(),a.end());
    vector<ll>b;
    for (auto & i : a){
        b.push_back(x-i);
    }
    ll z = b[0];
    for (auto & i : b){
        z = __gcd(z,i);
    }
    ll y = 0;
    for (auto & i : b){
        y += (i/z);
    }
    cout << y << " " << z << "\n";
}

