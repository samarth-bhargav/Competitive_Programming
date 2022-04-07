/*
Dont raise your voice,improve your argument
--Desmond Tutu
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
*/

struct pt{
    ll val;
    int idx;
    bool operator <(const pt & o) const{
        return val < o.val;
    }
};
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--){
        int n;
        cin >> n;
        vector<pt>a(n);
        for (int i = 0; i < n; i++){
            cin >> a[i].val;
            a[i].idx = i;
        }
        sort(a.begin(),a.end());
        ll prefix[n+1]; prefix[0] = 0;
        for (int i = 1; i <= n; i++){
            prefix[i] = prefix[i-1] + a[i-1].val;
        }
        vector<int>ans = {a[n-1].idx};
        for (int i = n-1; i >= 1; i--){
            if (prefix[i] >= a[i].val){
                ans.push_back(a[i-1].idx);
            }
            else{
                break;
            }
        }
        cout << ans.size() << "\n";
        sort(ans.begin(),ans.end());
        for (auto & i : ans){
            cout << i+1 << " ";
        }
        cout << "\n";
    }
}

