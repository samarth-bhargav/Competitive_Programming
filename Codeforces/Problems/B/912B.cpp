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
    ll n,k;
    cin >> n >> k;
    ll init = 1;
    while (init <= n){
        init *= 2;
    }
    cout << (k == 1 ? n : init-1) << "\n";
}

