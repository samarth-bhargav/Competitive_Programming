#include <bits/stdc++.h>
using namespace std;

int rnd(int l, int r) {
    return l + (rand() * rand()) % (r - l + 1);
}

long long naive(vector<int> a, int n){
    auto brute = [&](auto self, vector<int> a, bool mi) -> int{
        if (a.size() == 1){
            return a[0];
        }
        int ans = 0;
        for (int i = 0; i < a.size()-1; i++){
            vector<int> aa = a;
            if (mi){
                aa[i] = min(a[i], a[i+1]);
            }
            else{
                aa[i] = max(a[i], a[i+1]);
            }
            aa.erase(aa.begin() + i + 1);
            ans = max(ans, self(self, aa, mi ^ 1));
        }
        return ans;
    };

    long long ans = 0;

    for (int i = 0; i < n; i++){
        multiset<int> elems;
        for (int j = i; j < n; j++){
            elems.insert(a[j]);
            if (j - i + 1 >= 7){
                if ((j - i + 1) % 2 == 0){
                    ans += (long long)(*prev(prev(elems.end())));
                }
                else{
                    ans += (long long)(*prev(elems.end()));
                }
            }
            else{
                ans += brute(brute, vector<int>(a.begin() + i, a.begin() + j + 1), 1);
            }
        }
    }
    return ans;
}

struct rmq{
    int n;
    vector<int> a;
    vector<vector<int>> sparse;
    rmq(vector<int> a){
        this->a = a;
        this->n = a.size();
        sparse.resize(n, vector<int>(20, 0));
        bld();
    }
    void bld(){
        for (int i = 0; i < n; i++){
            sparse[i][0] = a[i];
        }
        for (int b = 1; b < 20; b++){
            for (int i = 0; (i + (1 << b)) <= n; i++){
                sparse[i][b] = max(sparse[i][b-1], sparse[i + (1 << (b-1))][b-1]);
            }
        }
    }
    int query(int lo, int hi){
        int lg = 31 - __builtin_clz(hi - lo + 1);
        return max(sparse[lo][lg], sparse[hi - (1 << lg) + 1][lg]);
    }
    int left_geq(int i, int val){
        if (i == 0){
            return -1;
        }
        int lo = 0, hi = i-1;
        while (lo < hi){
            int mid = (lo + hi + 1) / 2;
            if (query(mid, i-1) >= val){
                lo = mid;
            }
            else{
                hi = mid-1;
            }
        }
        if (lo == 0){
            if (a[0] >= val){
                return 0;
            }
            else{
                return -1;
            }
        }
        return lo;
    }

    int right_g(int i, int val){
        if (i == n-1){
            return n;
        }
        int lo = i+1, hi = n-1;
        while (lo < hi){
            int mid = (lo + hi) / 2;
            if (query(i+1, mid) > val){
                hi = mid;
            }
            else{
                lo = mid+1;
            }
        }
        if (lo == n-1){
            if (a[n-1] > val){
                return n-1;
            }
            else{
                return n;
            }
        }
        return lo;
    }

};

int main(){
    srand(time(NULL));
    std::random_device rd;
    std::mt19937 g(rd());
    ios_base::sync_with_stdio(0);
    cin.tie(0);

//    for (int tt = 0; tt < 100; tt++) {
        int n;
        cin >> n;
//        n = 6;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
//            a[i] = rnd(1, 10);
        }

        rmq table(a);

//        for (int i = 0; i < n; i++){
//            cout << table.left_geq(i, a[i]) << " ";
//        }
//        cout << "\n";
//        for (int i = 0; i < n; i++){
//            cout << table.right_g(i, a[i]) << " ";
//        }
//        cout << "\n";

        auto solve = [&](int a, int b, bool odd) -> long long {
            //a to the left, b to the right, trying to get [odd] sum
            long long num_a_odd = (a + 1) / 2;
            long long num_a_even = a + 1 - num_a_odd;

            long long num_b_odd = (b + 1) / 2;
            long long num_b_even = b + 1 - num_b_odd;

            if (odd) {
                return num_a_odd * num_b_even + num_b_odd * num_a_even;
            } else {
                return num_a_odd * num_b_odd + num_a_even * num_b_even;
            }
        };


        long long ans = 0;

        for (int i = 0; i < n; i++) {
            //i is maximum. left geq right g, odd length

            int lgeq = table.left_geq(i, a[i]);
            int rg = table.right_g(i, a[i]);

            {
                int left_boundary = lgeq + 1;
                int right_boundary = rg - 1;
                ans += (long long) a[i] * solve(i - left_boundary, right_boundary - i, false);
            }
            //i is second maximum. aa and ba case
            {
                int left_boundary = lgeq;
                if (left_boundary != -1) {
                    int actual_left = table.left_geq(left_boundary, a[i]) + 1;
                    int right_boundary = rg - 1;

                    bool invert_choice = (i - left_boundary) % 2 == 0 ? 0 : 1;

                    ans += (long long) a[i] *
                           solve(left_boundary - actual_left, right_boundary - i, true ^ invert_choice);
                }
            }
            //i is second maximum. ab case
            {
                int left_boundary = lgeq + 1;
                int right_boundary = rg;
                if (right_boundary == n) {
                    continue;
                }
                int actual_right = table.right_g(right_boundary, a[i]) - 1;

                bool invert_choice = (right_boundary - i) % 2 == 0 ? 0 : 1;
                ans += (long long) a[i] * solve(i - left_boundary, actual_right - right_boundary, true ^ invert_choice);
            }
        }

        for (int i = 0; i < n; i++) {
            multiset<int> elems;
            for (int j = i; j < min(i + 6, n); j++) {
                elems.insert(a[j]);
                if ((j - i + 1) % 2 == 0) {
                    int mx = (*prev(elems.end())), mx2 = (*prev(prev(elems.end())));
                    if (j - i + 1 == 4) {
                        if ((a[i] == mx && a[i + 2] == mx2) || (a[i] == mx2 && a[i + 2] == mx) ||
                            (a[i + 1] == mx && a[i + 3] == mx2) || (a[i + 1] == mx2 && a[i + 3] == mx)
                            || (a[i + 1] == mx && a[i + 2] == mx2) || (a[i + 1] == mx2 && a[i + 2] == mx)) {
                            ans -= mx2;
                            ans += *next(elems.begin());
                        }
                    } else if ((j - i + 1) == 6) {
                        if ((a[i + 1] == mx && a[i + 4] == mx2) || (a[i + 1] == mx2 && a[i + 4] == mx) ||
                            (a[i + 1] == mx && a[i + 3] == mx2) || (a[i + 1] == mx2 && a[i + 3] == mx) ||
                            (a[i + 2] == mx && a[i + 4] == mx2) || (a[i + 2] == mx2 && a[i + 4] == mx)){
                            ans -= mx2;
                            ans += *prev(prev(prev(elems.end())));
                        }
                    }
                } else {
                    if (j - i + 1 == 3 && a[i + 1] == *prev(elems.end())) {
                        ans -= (long long) (*prev(elems.end()));
                        ans += (long long) (*prev(prev(elems.end())));
                    }
                }
            }
        }

        cout << ans << "\n";
//        if (ans != naive(a, n)){
//            for (int i = 0; i < n; i++){
//                cerr << a[i] << " ";
//            }
//            cerr << "\n";
//            assert(false);
//        }
//    }
}