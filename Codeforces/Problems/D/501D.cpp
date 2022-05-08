#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

typedef tree<int, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update> ost;

int main(){
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    for (int i = 0; i < n; i++){
        cin >> b[i];
    }
    vector<int> ao, bo;
    ost ah, bh;
    for (int i = 0; i < n; i++){
        ah.insert(i);
        bh.insert(i);
    }
    for (int i = 0; i < n; i++){
        ao.push_back(ah.order_of_key(a[i]));
        ah.erase(ah.find(a[i]));
        bo.push_back(bh.order_of_key(b[i]));
        bh.erase(bh.find(b[i]));
    }
    vector <int> so(n);
    for (int i = 0; i < n; i++){
        so[i] = ao[i] + bo[i];
    }
    for (int i = n-1; i > 0; i--){
        int lim = (n - i);
        if (so[i] >= lim){
            int div = so[i] / lim;
            int rem = so[i] % lim;
            so[i] = rem;
            so[i-1] += div;
        }
    }
    so[0] %= n;
    vector<int> ans;
    ost sh;
    for (int i = 0; i < n; i++){
        sh.insert(i);
    }
    for (int i = 0; i < n; i++){
        auto it = sh.find_by_order(so[i]);
        ans.push_back(*it);
        sh.erase(it);
    }
    for (int i = 0; i < n; i++){
        cout << ans[i] << " ";
    }
    cout << "\n";
}