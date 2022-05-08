//babybeluga
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
*/
const int mxN = 3e5+2;
const int lgmxN = 19;
vector<int> arr;

int dp[mxN][lgmxN+1];

void rmq(){
    int n = arr.size();
    for (int i = 0; i < n; i++){
        dp[i][0] = i;
    }
    for (int j = 1; j <= lgmxN; j++){
        for (int i = 0; i + (1 << j) < mxN; i++){
            if (arr[dp[i][j - 1]] < arr[dp[i + (1 << (j - 1))][j - 1]]){
                dp[i][j] = dp[i+(1<<(j-1))][j-1];
            }
            else{
                dp[i][j] = dp[i][j-1];
            }
        }
    }
}
int rmq(int a, int b){
    if (a == b){
        return a;
    }
    if (a > b){
        return a-1;
    }
    int ret = a;
    for (int j = lgmxN; j >= 0; j--){
        if (a + ((1 << j) - 1) <= b){
            if (arr[dp[a][j]] > arr[ret]){
                ret = dp[a][j];
            }
            a += (1 << j);
        }
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n; arr.resize(n);
    for (int i = 0; i < n; i++){
        cin >> arr[i];
    }
    vector<int>firstocc(n+1, -1);
    set<int>curr;
    for (int i = 0; i < n; i++){
        curr.insert(arr[i]);
        auto it = curr.find(arr[i]);
        if (it == curr.begin()){
            continue;
        }
        for (auto iter = prev(it); iter != curr.begin(); iter--){
            firstocc[*iter] = i;
        }
        firstocc[*curr.begin()] = i;
        while (*curr.begin() != arr[i]){
            curr.erase(curr.begin());
        }
    }
//    for (int i = 0; i < n+1; i++){
//        cout << firstocc[i] << " ";
//    }
    rmq();
    ll ans = 0;
    for (int i = 0; i < n-1; i++){
        int upper = firstocc[arr[i]];
        if (upper == -1){
            upper = rmq(i+1, n-1);
        }
        while (upper != i){
            ans += upper - i + 1;
            upper = rmq(i+1, upper-1);
        }
    }
    cout << ans << "\n";
}

