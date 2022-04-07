/*
ID: samarth10
LANG: C++11
TASK: 
*/
#include <bits/stdc++.h>

using namespace std;


void setIO(string name) {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen((name + ".in").c_str(), "r", stdin);
    freopen((name + ".out").c_str(), "w", stdout);
}


int main() {
//    setIO("homework");
    vector <long double> mins;
    deque <pair <long long, long long>> dp;
    vector <pair <long double, long double>> ans;
    vector <long double> nums;
    long long sum = 0;
    int t;
    cin >> t;
    for (int i = 0; i < t; i++){
        long long x;
        cin >> x;
        nums.push_back(x);
        sum += x;
    }
    for (int i = 0; i < t; i++){
        dp.emplace_back(nums[i], i); //i stands for position of element
    }
    sort(dp.begin(), dp.end());
    mins.push_back(0);
    for (int i = 1; i <= t; i++){ // i is number of elements removed
        if (dp[0].second > i-1){
            mins.push_back(dp[0].first);
        }
        else{
            if (!dp.empty()){
                dp.pop_front();
                i--;
            }
            else{
                break;
            }
        }
    }
    /*
    for (auto x: mins){
        cout << x << "\n";
    }
    */
    ans.emplace_back(0,0);
    for (int i = 0; i < t-1; i++){
        sum -= nums[i];
        if ((sum-mins[i+1])/(t-(i+1)) > ans[0].second){
            ans.clear();
            ans.emplace_back(i+1,(sum-mins[i+1])/(t-(i+1)));
        }
        else if (((sum-mins[i+1])/(t-(i+1)) == ans[0].second)){
            ans.emplace_back(i+1,(sum-mins[i+1])/(t-(i+1)));
        }
        else{
            continue;
        }
    }
    sort(ans.begin(), ans.end());
    for (auto x: ans){
        cout << x.first << "\n";
    }
}

