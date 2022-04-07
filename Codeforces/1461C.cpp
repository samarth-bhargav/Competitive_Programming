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
        int n,m;
        cin >> n >> m;
        vector<int>perm(n);
        vector<pair<int,double>>prob(m);
        for (auto & i : perm){
            cin >> i;
        }
        for (int i = 0; i < m; i++){
            int a; double b;
            cin >> a >> b;
            prob[i] = {a,b};
        }
        if (is_sorted(perm.begin(),perm.end())){
            cout << 1 << "\n";
            continue;
        }
        int last = n;
        for (int i = n-1; i >= 0; i--){
            if (perm[i]-1 == i){
                last = i;
                continue;
            }
            else{
                break;
            }
        }
        cerr << last << "\n";
        double ans = 1;
        sort(prob.begin(),prob.end());
        auto lower = lower_bound(prob.begin(),prob.end(),make_pair(last,0.0));
        for (auto it = lower; it != prob.end(); it++){
            ans *= (1.0-it->second);
        }
        cout << fixed;
        cout << setprecision(10) << 1.0-ans << "\n";
    }
}

