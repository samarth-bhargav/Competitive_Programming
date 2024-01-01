#include <bits/stdc++.h>

using namespace std;

#define int long long
int k, n, q;
vector<int> a;
vector<int> minp;
int totSum = 0;

bool ok(int threshold){
    int num_lower = lower_bound(a.begin(), a.end(), threshold) - a.begin();
    if (num_lower == 0 && n != 1) return true;
    // a[i] + k - i >= threshold
    if (num_lower != 0 && minp[num_lower - 1] + k < threshold){
        return false;
    }
    int sumLast = k * (k + 1) / 2 - (k - num_lower) * (k - num_lower + 1) * (k - num_lower > 0) / 2;
    if ((k - num_lower) % 2 == 1){
        num_lower++;
        sumLast += (k - num_lower);
        if (num_lower > n){
            return false;
        }
    }
    if ((totSum + sumLast - threshold * n) * 2 >= (k - num_lower)){
        return true;
    }
    return false;
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> q;
    a.resize(n);
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    totSum = accumulate(a.begin(), a.end(), 0LL);
    minp.resize(n);
    int minelem = a[0] - 0;
    for (int i = 0; i < n; i++){
        minelem = min(minelem, a[i] - i);
        minp[i] = minelem;
    }
    for (int i = 0; i < q; i++){
        cin >> k;
        int lo = -2e9, hi = 2e9;
        while (lo < hi){
            int mid = (lo + hi + 1) / 2;
            if (ok(mid)){
                lo = mid;
            }
            else{
                hi = mid-1;
            }
        }
        cout << lo << " ";
    }
    cout << "\n";
}