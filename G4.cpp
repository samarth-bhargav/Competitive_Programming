#include <bits/stdc++.h>

using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    //upper bound for number of elements


    //returns sum of consecutive squares in range [l, r]
    auto sos_in_range = [&](int l, int r){
        l--;
        return r * (r + 1) * (2 * r + 1) / 6 - l * (l + 1) * (2 * l + 1) / 6;
    };

    auto solve = [&](int n) -> int{
        int ub = 3 * pow(n, 1.0 / 3) + 1;
        const int SQRT_N = sqrt(n) + 5;

        //stores answers in the format [l, r] where squares go from l to r
        vector<array<int, 2>> valid;

        //iterating over number of elements
        for (int i = 1; i <= ub; i++){
            //binary search for top value
            int lo = i, hi = SQRT_N;
            while (lo < hi){
                int mid = (lo + hi) / 2;
                if (sos_in_range(mid - i + 1, mid) >= n){
                    hi = mid;
                }
                else{
                    lo = mid+1;
                }
            }
            int sum = sos_in_range(lo - i + 1, lo);
            if (sum > n){
                continue;
            }
            else{
                if (sum == n){
                    valid.push_back({lo - i + 1, lo});
                }
            }
        }
        for (auto x : valid){
            cout << x[0] << " " << x[1] << "\n";
        }
        return valid.size();
    };

    solve(147441);
    return 0;

    for (int i = 1; i <= 150000; i++){
        if (solve(i) >= 3 && (int)(sqrt(i)) * (int)(sqrt(i)) != i){
            cout << i << "\n";
            return 0;
        }
    }
}