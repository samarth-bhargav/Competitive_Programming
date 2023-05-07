#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, a, b;
    cin >> n >> a >> b;
    vector<int> ops(n);
    for (int i = 0; i < n; i++){
        cin >> ops[i];
    }
    auto answer = [&](int x, int y) -> int{
        int old_sum = x + y;
        for (int i = 0; i < n; i++){
            if (ops[i] < 0){
                x = min({x - ops[i], a, x + y});
                y = old_sum - x;
            }
            else{
                y = min({y + ops[i], b, x + y});
                x = old_sum - y;
            }
        }
        return x;
    };
    int ans[a+1][b+1];
    for (int sum = 0; sum <= a+b; sum++){
        int x_start = max(sum-b, 0), y_start = sum - x_start;
        int start_ans = answer(x_start, y_start);
        int x_end = min(sum, a), y_end = sum - x_end;
        int end_ans = answer(x_end, y_end);

//        cerr << x_start << " " << x_end << " " << sum << "\n";
        int lo = x_start, hi = x_end;
        while (lo < hi){
            int mid = (lo + hi + 1) / 2;
            if (answer(mid, sum-mid) > start_ans){
                hi = mid-1;
            }
            else{
                lo = mid;
            }
        }
        int start_until = lo;
        lo = x_start, hi = x_end;
        while (lo < hi){
            int mid = (lo + hi) / 2;
            if (answer(mid, sum - mid) < end_ans){
                lo = mid+1;
            }
            else{
                hi = mid;
            }
        }
        int end_until = lo;
        for (int x = x_start; x <= start_until; x++){
            ans[x][sum-x] = start_ans;
        }
        for (int x = start_until+1; x < end_until; x++){
            ans[x][sum-x] = (x-start_until) + start_ans;
        }
        for (int x = end_until; x <= x_end; x++){
            ans[x][sum-x] = end_ans;
        }
    }
    for (int i = 0; i <= a; i++){
        for (int j = 0; j <= b; j++){
            cout << ans[i][j] << " ";
        }
        cout << "\n";
    }
}
