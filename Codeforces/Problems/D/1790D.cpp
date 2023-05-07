#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n; cin >> n;
        multiset<int> a;
        for (int i = 0; i < n; i++){
            int x; cin >> x;
            a.insert(x);
        }
        int ans = 0;
        while (!a.empty()){
            ans++;
            int ref = *a.begin();
            a.erase(a.find(ref));
            ref++;
            while (a.find(ref) != a.end()){
                a.erase(a.find(ref));
                ref++;
            }
        }
        cout << ans << "\n";
    }
}