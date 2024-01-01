#include <bits/stdc++.h>

using namespace std;
#define int long long

const int mxN = 3e5;
int LOG[mxN + 1];

struct SparseTable {
    vector<vector<int>> sparseTable;
    SparseTable(vector<int>& a) {
        sparseTable.assign(a.size(), vector<int>(LOG[a.size()] + 1));
        for(int i = 0; i < a.size(); i++) {
            sparseTable[i][0] = a[i];
        }
        for(int i = 1; i <= LOG[a.size()]; i++) {
            for(int j = 0; j + (1 << i) - 1 < a.size(); j++) {
                sparseTable[j][i] = max(sparseTable[j][i - 1], sparseTable[j + (1 << (i - 1))][i - 1]);
            }
        }
    }
    int query(int i, int j) {
        int lg = LOG[j - i + 1];
        return max(sparseTable[i][lg], sparseTable[j - (1 << lg) + 1][lg]);
    }
};

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    LOG[1] = 0;
    for (int i = 2; i <= mxN; i++) {
        LOG[i] = LOG[i / 2] + 1;
    }
    int t; cin >> t;
    for (int tt = 0; tt < t; tt++){
        int n; cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++){
            cin >> a[i];
        }
        vector<int> r_notsort(n, n), l_notsort(n, -1), r_less(n, n), l_greater(n, -1), r_greater(n, n), l_less(n, -1);
        vector<int> stk;
        stk.push_back(n-1);
        for (int i = n-2; ~i; i--){
            if (a[i] > a[i+1]){
                while (!stk.empty()){
                    l_notsort[stk.back()] = i;
                    stk.pop_back();
                }
            }
            stk.push_back(i);
        }
        stk.clear();
        stk.push_back(0);
        for (int i = 1; i < n; i++){
            while (!stk.empty() && a[i] < a[stk.back()]){
                r_less[stk.back()] = i;
                stk.pop_back();
            }
            stk.push_back(i);
        }
        stk.clear();
        stk.push_back(0);
        for (int i = 1; i < n; i++){
            while (!stk.empty() && a[i] > a[stk.back()]){
                r_greater[stk.back()] = i;
                stk.pop_back();
            }
            stk.push_back(i);
        }
        stk.clear();
        stk.push_back(n-1);
        for (int i = n-2; ~i; i--){
            while (!stk.empty() && a[i] > a[stk.back()]){
                l_greater[stk.back()] = i;
                stk.pop_back();
            }
            stk.push_back(i);
        }
        stk.clear(); stk.shrink_to_fit();
        stk.push_back(n-1);
        for (int i = n-2; ~i; i--){
            while (!stk.empty() && a[i] < a[stk.back()]){
                l_less[stk.back()] = i;
                stk.pop_back();
            }
            stk.push_back(i);
        }
        int ans = 0;
        SparseTable st(a);
        vector<int> l_sz(n);
        for (int i = 0; i < n; i++){
            if (i == 0 || l_greater[i-1] == -1){
                l_sz[i] = 1;
            }
            else{
                l_sz[i] = max(l_greater[i-1] - l_greater[i] + 1, 1LL);
            }
        }
        vector<int> pref_lsz(n+1);
        vector<int> pref_lsz_with_mul(n+1);
        pref_lsz[0] = 0;
        pref_lsz_with_mul[0] = 0;
        for (int i = 1; i <= n; i++){
            pref_lsz[i] = pref_lsz[i-1] + l_sz[i-1];
            pref_lsz_with_mul[i] = pref_lsz_with_mul[i-1] + l_sz[i-1] * (i-1);
        }
        for (int ep = 0; ep < n; ep++){
            int r_sz;
            if (ep == n-1 || r_less[ep+1] == n){
                r_sz = 1;
            }
            else{
                assert(ep != n-1);
                r_sz = max(r_less[ep] - r_less[ep+1] + 1, 1LL);
            }
            int tot_rangesz = ep - l_notsort[ep];
            int tot_lsz = pref_lsz[ep+1] - pref_lsz[l_notsort[ep]+1];
            int tot_lsz_with_mul = pref_lsz_with_mul[ep+1] - pref_lsz_with_mul[l_notsort[ep]+1];
            //(l_sz) * (ep - sp + 1 - ep + sp - 2 + r_sz * (ep - sp + 2)) = (l_sz) * (r_sz * (ep - sp + 2) - 1)
            //ep - sp + (r_sz - 1) * (ep - sp + 1) + (r_sz - 1) * (-1) * (ep - sp + 2)
            int epminussp = (tot_rangesz - 1) * (tot_rangesz) / 2;
            int l_contrib = r_sz * ep * tot_lsz - tot_lsz_with_mul * r_sz + tot_lsz * (2 * r_sz - 1);
            int rest = -r_sz * tot_rangesz;
            ans += l_contrib + rest;
            //consider empty interval
            //right endpoint is min(b)
            int pivot = l_less[ep];
            if (pivot == -1 || pivot == ep-1) continue;
            int maxa = l_greater[pivot];
            if (maxa == -1 || a[maxa] > a[ep]) continue;
            int lo = 0, hi = maxa;
            while (lo < hi){
                int mid = (lo + hi + 1) / 2;
                if (st.query(mid, maxa) > a[ep]){
                    lo = mid;
                }
                else{
                    hi = mid-1;
                }
            }
            if (lo == 0 && a[lo] < a[ep]){
                lo--;
            }
            ans += (maxa - lo) * (r_less[ep] - ep);
        }
        cout << (n+1) * n * (n-1) / 6 - ans << "\n";
    }
}