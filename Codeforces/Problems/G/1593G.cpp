#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--){
        string s; cin >> s;
        int n = s.size();
        set<int> bracket_ind;
        for (int i = 0; i < n; i++){
            if (s[i] == '[' || s[i] == ']'){
                bracket_ind.insert(i);
            }
        }
        int pref_odd[n+1], pref_even[n+1];
        memset(pref_odd, 0, sizeof(pref_odd));
        memset(pref_even, 0, sizeof(pref_even));
        pref_odd[0] = 0; pref_even[0] = 0;
        for (int i = 1; i <= n; i++){
            pref_odd[i] = pref_odd[i-1];
            pref_even[i] = pref_even[i-1];
            if (bracket_ind.find(i-1) != bracket_ind.end()){
                if (i & 1){
                    pref_odd[i]++;
                }
                else{
                    pref_even[i]++;
                }
            }
        }
        int q;
        cin >> q;
        while (q--){
            int a,b;
            cin >> a >> b; a--; b--;
            int odds = pref_odd[b+1] - pref_odd[a];
            int evens = pref_even[b+1] - pref_even[a];
            cout << max(odds, evens) - min(odds, evens) << "\n";
        }
    }
}


