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
        ll n,w;
        cin >> n >> w;
        multiset<ll>widths;
        for (int i = 0; i < n; i++){
            ll x;
            cin >> x;
            widths.insert(x);
        }
        ll height = 1;
        ll currwidth = 0;
        while (!widths.empty()){
            auto it = widths.lower_bound(w-currwidth);
            if (*widths.begin() > w-currwidth){
                height++;
                currwidth = 0;
            }
            else{
                if (it == widths.end() || *it > w-currwidth){
                    it--;
                }
                currwidth += *it;
                widths.erase(it);
            }
        }
        cout << height << "\n";
    }
}

