#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n; cin >> n;
        vector<int> a(n+1);
        for (int i = 1; i <= n; i++){
            cin >> a[i];
        }
        vector<int> neg_pre(n+1), pos_suf(n+2);
        //neg_pre[i] denotes prefix [0, i]
        //pos_suf[i] denotes suffix [i, n+1]
        int regions = 1;
        neg_pre[0] = 0; neg_pre[1] = 1;
        for (int i = 2; i <= n; i++){
            if (a[i-1] > a[i]){
                neg_pre[i] = neg_pre[i-1];
            }
            else{
                regions++;
                neg_pre[i] = regions;
            }
        }
        regions = 1;
        pos_suf[n+1] = 0; pos_suf[n] = 0;
        for (int i = n-1; i >= 1; i--){
            if (a[i] < a[i+1]){
                pos_suf[i] = pos_suf[i+1];
            }
            else{
                pos_suf[i] = regions; regions++;
            }
        }
//        for (int i = 1; i <= n; i++){
//            cerr << neg_pre[i] << " ";
//        }
//        cerr << endl;
//        for (int i = 1; i <= n; i++){
//            cerr << pos_suf[i] << " ";
//        }
//        cerr << endl;
        int ans = 1e9;
        for (int i = 0; i <= n; i++){
            ans = min(ans, neg_pre[i] + pos_suf[i+1]);
        }
        cout << ans << "\n";
    }
}