#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n; cin >> n;
        vector<int> a(n), b(n);

        int neg_sum = 0;

        for (int i = 0; i < n; i++){
            cin >> a[i] >> b[i];
            if (a[i] - b[i] < 0){
                neg_sum += (a[i] - b[i]);
            }
        }

        int b_sum = accumulate(b.begin(), b.end(), 0LL);
        int a_sum = accumulate(a.begin(), a.end(), 0LL);

        if (b_sum - *min_element(b.begin(), b.end()) < a_sum){
            cout << -1 << "\n";
            continue;
        }

        multiset<int> posi_a, negi_a, all_a;
        for (int i = 0; i < n; i++){
            all_a.insert(a[i]);
            if (a[i] - b[i] < 0){
                negi_a.insert(b[i] - a[i] + a[i]);
            }
            else{
                posi_a.insert(a[i]);
            }
        }

        int min_ans = 1e18;

        for (int i = 0; i < n; i++){
            if (b_sum - b[i] < a_sum){
                continue;
            }
            int temp_ans = 0;
            int temp_neg = neg_sum;

            all_a.erase(all_a.find(a[i]));
            temp_ans = max(temp_ans, *all_a.begin());

            if (a[i] - b[i] < 0){
                temp_neg += b[i] - a[i];
                negi_a.erase(negi_a.find(b[i]));
                if (!posi_a.empty()){
                    temp_ans = max(temp_ans, temp_neg + *prev(posi_a.end()));
                }
                if (!negi_a.empty()){
                    temp_ans = max(temp_ans, temp_neg + *prev(negi_a.end()));
                }

                negi_a.insert(b[i]);
            }
            else{
                posi_a.erase(posi_a.find(a[i]));
                if (!posi_a.empty()){
                    temp_ans = max(temp_ans, temp_neg + *prev(posi_a.end()));
                }
                if (!negi_a.empty()){
                    temp_ans = max(temp_ans, temp_neg + *prev(negi_a.end()));
                }
                posi_a.insert(a[i]);
            }

            all_a.insert(a[i]);

            min_ans = min(min_ans, temp_ans);

        }

        cout << min_ans + a_sum << "\n";

    }
}