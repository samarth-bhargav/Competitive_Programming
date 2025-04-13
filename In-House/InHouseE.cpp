#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;
    vector<int> a(n+1);
    for (int i = 1; i <= n; i++){
        cin >> a[i];
    }

    int ans = 1e9;

    for (int x = 1; x <= n; x++){
        if (is_sorted(a.begin()+x, a.end())){
            //LIS on a[1:x-1]
            set<int> lis;
            for (int i = 1; i <= x-1; i++){
                if (a[i] < a[n]){
                    continue;
                }
                auto it = lis.upper_bound(a[i]);
                if (it == lis.end()){
                    lis.insert(a[i]);
                    continue;
                }
                lis.erase(it);
                lis.insert(a[i]);
            }
            ans = min(ans, x - 1 + (x - 1 - (int)lis.size()));
        }
        else{
            //LIS on a[x+1:n]
            set<int> lis;
            for (int i = x+1; i <= n; i++){
                if (a[i] < a[x]){
                    continue;
                }
                auto it = lis.upper_bound(a[i]);
                if (it == lis.end()){
                    lis.insert(a[i]);
                    continue;
                }
                lis.erase(it);
                lis.insert(a[i]);
            }
            ans = min(ans, n + (x - 1 + (n - x - (int)lis.size())));
        }
    }

    cout << ans << "\n";

}