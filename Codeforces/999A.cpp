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
    int n,k;
    cin >> n >> k;
    vector<int>a(n); for (auto & i : a) cin >> i;
    int bg = -1, ed = n;
    for (int i = 0; i < n; i++){
        if (a[i] > k){
            break;
        }
        bg = i;
    }
    for (int i = n-1; i >= 0; i--){
        if (a[i] > k){
            break;
        }
        ed = i;
    }
    if (bg >= ed){
        cout << n << "\n";
    }
    else{
        cout << bg+n-ed+1 << "\n";
    }
}

