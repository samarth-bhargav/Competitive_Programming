#include <bits/stdc++.h>

typedef long long ll;
#define int ll
using namespace std;

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;
    vector<int> a(n+1);
    for (int i = 1; i <= n; i++){
        cin >> a[i];
    }
    vector<int> fl(n+1, n+1); fl[0] = 0;
    vector<int> sl(n+1, n+1); sl[0] = 0;
    vector<ll> sums(n+1); sums[0] = 0;
    for (int i = 1; i <= n; i++){
        sums[i] = sums[i-1] + i;
    }
    queue<int> q1, q2;
    for (int i = 1; i <= n; i++){
        q1.push(i);
        while (!q2.empty() && q2.front() < 1 + i - a[i]){
            sl[q2.front()] = i;
            q2.pop();
        }
        while (!q1.empty() && q1.front() < 1 + i - a[i]){
            fl[q1.front()] = i;
            q2.push(q1.front());
            q1.pop();
        }
    }
//    for (int i = 1; i <= n; i++){
//        cout << fl[i] << " ";
//    }
//    cout << "\n";
    vector<ll> pf(n+1), spf(n+1);
    pf[0] = 0; spf[0] = 0;
    for (int i = 1; i < n+1; i++){
        pf[i] = pf[i-1] + (ll)(fl[i] - i);
        spf[i] = spf[i-1] + (ll)(sl[i] - i);
    }
    vector<array<int, 2>> rng(n+2, {-1, -1});
    int curr = fl[1];
    int start = 1;
    for (int i = 2; i <= n; i++){
        if (fl[i] != curr){
            rng[curr] = {start, i-1};
            start = i; curr = fl[i];
        }
    }
    rng[curr] = {start, n};
    int queries; cin >> queries;
    for (int i = 0; i < queries; i++){
        int p, x; cin >> p >> x;
        if (x < a[p]){
            //everything will be replaced by p in this range
            int lb = max(1 + p - a[p], 1LL), ub = max(p - x, 0LL);
            lb = max((ll)lb, (ll)(upper_bound(fl.begin(), fl.end(), p) - fl.begin()));
            if (lb > ub){
                cout << pf.back() << "\n"; continue;
            }
            cout << (ub - lb + 1) * p - (sums[ub] - sums[lb-1]) + pf.back() - pf[ub] + pf[lb-1] << "\n";
        }
        else{
            //everything will shift to second in this range
            int lb = max(1 + p-x, 1LL), ub = max(p - a[p], 0LL);
            array<int, 2> bad = {-1, -1};
            if (rng[p] == bad){
                cout << pf.back() << "\n"; continue;
            }
            lb = max(lb, rng[p][0]);
            ub = min(ub, rng[p][1]);
            if (lb > ub){
                cout << pf.back() << "\n"; continue;
            }
            cout << pf[lb-1] + pf.back() - pf[ub] + spf[ub] - spf[lb-1] << "\n";
//            ans += (pf[max(p - a[p], 0)] - pf[max(p - x, 0)]);
        }
    }
}