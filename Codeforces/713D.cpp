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
    int t;
    cin >> t;
    while (t--){
        int n;
        cin >> n; n+=2;
        vector<ll>b(n);
        for (auto & i : b){
            cin >> i;
        }
        sort(b.begin(),b.end());
        ll sum = 0;
        for (int i = 0; i < n; i++){
            sum += b[i];
        }
        multiset<ll>bcurr;
        for (auto & i : b){
            bcurr.insert(i);
        }
        bool good = false;
        for (int i = 0; i < n; i++){
            ll x = b[i];
            ll sumremaining = sum-x;
            ll value = sumremaining - x;
            bcurr.erase(bcurr.lower_bound(x));
            auto it = bcurr.lower_bound(value);
            if (it != bcurr.end() && *it == value){
                for (auto iter = bcurr.begin(); iter != bcurr.end(); iter++){
                    if (iter != it){
                        cout << *iter << " ";
                    }
                }
                cout << "\n";
                good = true;
                break;
            }
            bcurr.insert(x);
        }
        if (!good){
            cout << -1 << "\n";
        }
    }
}

