#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int M = 998244353;
const int mxN = 1e5+1;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--){
        int n; cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++){
            cin >> a[i];
        }
        ll ans = 0;
        unordered_map<ll, int> st1, st2;
        st1[a[n-1]] = 1;
        ll past_ans = 0;
        for (int i = n-2; ~i; i--){
            ll temp = past_ans;
            for (pair<int,int> p : st1){
                if (a[i] <= p.first){
                    st2[a[i]] += p.second;
                    continue;
                }
                ll lo = (a[i] + p.first - 1) / p.first;
                temp += (lo-1) * p.second;
                temp = (temp % M + M) % M;
                st2[a[i] / lo] += p.second;
            }
            past_ans = temp;
            ans += temp;
            ans = (ans % M + M) % M;
            swap(st1, st2);
            st1[a[i]]++; // new subarray
            st2.clear();
        }
        cout << ans << "\n";
    }
}
