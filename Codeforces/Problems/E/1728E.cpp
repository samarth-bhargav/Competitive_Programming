#include <bits/stdc++.h>
using namespace std;

#define int long long

int gcd(int a, int b, int& x, int& y) {
    x = 1, y = 0;
    int x1 = 0, y1 = 1, a1 = a, b1 = b;
    while (b1) {
        int q = a1 / b1;
        tie(x, x1) = make_tuple(x1, x - q * x1);
        tie(y, y1) = make_tuple(y1, y - q * y1);
        tie(a1, b1) = make_tuple(b1, a1 - q * b1);
    }
    return a1;
}

int32_t main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    vector<array<int, 2>> dishes;
    for (int i = 0; i < n; i++){
        int a, b; cin >> a >> b;
        dishes.push_back({a,b});
    }
    //construct dp array
    vector<int> dp(n+1, 0); //dp[i] = i red, n-i black
    vector<int> sorted_dishes;
    for (int i = 0; i < n; i++){
        sorted_dishes.push_back(dishes[i][0] - dishes[i][1]);
    }
    sort(sorted_dishes.rbegin(), sorted_dishes.rend());
    //prefix red, suffix black
    for (int i = 0; i < n; i++){
        dp[0] += dishes[i][1];
    }
    int inflection = -1;
    for (int i = 1; i <= n; i++){
        dp[i] = dp[i-1] + sorted_dishes[i-1];
        if (dp[i] < dp[i-1] && inflection == -1){
            inflection = i-1;
        }
    }
//    for (int i = 0; i <= n; i++){
//        cout << dp[i] << " ";
//    }
//    cout << "\n";
//    cerr << inflection << "\n";
    int m; cin >> m;
    for (int i = 0; i < m; i++){
        int xi, xj;
        cin >> xi >> xj;
        if (n % __gcd(xi, xj) != 0){
            cout << -1 << "\n";
            continue;
        }
        int x, y;
        gcd(xi, xj, x, y);
        //xi * x + xj * y = gcd(xi, xj), now scale up
        x = x * (n / __gcd(xi, xj));
        y = y * (n / __gcd(xi, xj));
//        cerr << "xi: " << xi << " x: " << x << " xj: " << xj << " y: " << y << " n: " << n << "\n";
        //now x * xi + y * xj = n
        vector<int> candidates;
        candidates.push_back(((inflection - x*xi) / (xj * xi / __gcd(xi, xj))) * (xj * xi / __gcd(xi, xj)) + x*xi);
        if (abs(candidates[0] - inflection) > (xj * xi / __gcd(xi, xj))){
            assert(false);
        }
        for (int j = 1; j <= 5; j++){
            candidates.push_back(candidates[0] + j * (xj * xi / __gcd(xi, xj)));
            candidates.push_back(candidates[0] - j * (xj * xi / __gcd(xi, xj)));
        }
        set<int> answers;
        for (int cand : candidates){
            if (0 <= cand && cand <= n){
                answers.insert(dp[cand]);
            }
        }
//        cout << cand_1 << " " << cand_2 << " " << cand_3 << "\n";
        if (answers.empty()){
            cout << -1 << "\n";
            continue;
        }
        cout << *prev(answers.end()) << "\n";
    }
}
