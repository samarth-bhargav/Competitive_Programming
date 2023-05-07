#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while (t--){
        int n; cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++){
            cin >> a[i];
        }
        int ans = 0;
        for (int i = 0; i < n; i++){
            if (i != 0 && a[i] == a[i-1]){
                continue;
            }
            int curr_diff = 0;
            int pos = i, temp = 1;
            while (true){
                auto it = lower_bound(a.begin() + pos + 1   , a.end(), a[pos] + curr_diff);
                if (it != a.end()){
                    curr_diff = *it - a[i];
                    pos = it - a.begin();
                    temp++;
                }
                else{
                    break;
                }
            }
            ans = max(ans, temp);
        }
        cout << a.size() - ans << "\n";
    }
}
