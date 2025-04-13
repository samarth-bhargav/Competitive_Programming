#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;

#define int long long

namespace __gnu_pbds{
    typedef tree<int,
            null_type,
            less_equal<int>,
    rb_tree_tag,
    tree_order_statistics_node_update> ost;
}
using namespace __gnu_pbds;



int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q; cin >> n >> q;

    struct question{
        int a, b;
        question(int a, int b){
            this->a = a;
            this->b = b;
        }
        question(){}
    };

    vector<question> qs(n);
    for (int i = 0; i < n; i++){
        cin >> qs[i].a >> qs[i].b;
    }

    sort(qs.begin(), qs.end(), [&](question &x, question &y){
        if (x.b + x.a != y.b + y.a){
            return x.b + x.a < y.b + y.a;
        }
        return x.a > y.a;
    });

    vector<int> pfa(n+1, 0);
    for (int i = 1; i <= n; i++){
        pfa[i] = pfa[i-1] + qs[i-1].a;
    }

   for (int i = 0; i < q; i++){
        int k; cin >> k;
        int ans = -1e18;

        if (k == 0){
            cout << pfa[n] << "\n";
            continue;
        }

        ost b_vals;

        int b_sum = 0;

        for (int j = n-k; j < n; j++){
            b_vals.insert(qs[j].b);
            b_sum += qs[j].b;
        }

        ans = max(ans, -b_sum + pfa[n-k]);

        for (int j = n-k-1; j >= 0; j--){
            if (qs[j].b < *b_vals.find_by_order(k-1)){
                b_sum -= *b_vals.find_by_order(k-1);
                b_sum += qs[j].b;
            }
            b_vals.insert(qs[j].b);
            ans = max(ans, -b_sum + pfa[j]);
        }
        cout << ans << "\n";
    }


}