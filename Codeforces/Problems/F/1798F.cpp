#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, k; cin >> n >> k;
    vector<int> gifts(n);
    for (int i = 0; i < n; i++){
        cin >> gifts[i];
    }
    vector<int> class_sizes(k);
    vector<array<int, 2>> old_class_sizes(k);
    for (int i = 0; i < k; i++){
        cin >> class_sizes[i];
        old_class_sizes[i] = {class_sizes[i], i};
    }
    sort(old_class_sizes.begin(), old_class_sizes.end());
    sort(class_sizes.begin(), class_sizes.end());
    vector<vector<int>> ans(k);
    int answer = -1;
    for (int i = 0; i < k; i++){
        if (i == k-1){
            //take sum of all gifts
            int curr_sum = accumulate(gifts.begin(), gifts.end(), 0LL);
            for (int j = 0; j < class_sizes[i]-1; j++){
                ans[old_class_sizes[i][1]].push_back(gifts[j]);
            }
            answer = ((class_sizes[i] - curr_sum) % class_sizes[i] + class_sizes[i]) % class_sizes[i];
            if (answer == 0) answer += class_sizes[i];
            ans[old_class_sizes[i][1]].push_back(answer);
            continue;
        }
        vector<vector<int>> dp(class_sizes[i], vector<int>(class_sizes[i]+1, -1));
        //dp[i][j] is i sum, j moves
        dp[0][0] = 0;
        for (int j = 0; j < gifts.size(); j++){
            //can either choose to add, or not to add
            vector<vector<int>> ndp = dp;
            for (int sum = 0; sum < class_sizes[i]; sum++){
                for (int moves = 0; moves < class_sizes[i]; moves++){
                    if (dp[sum][moves] != -1 && dp[(sum + gifts[j]) % class_sizes[i]][moves+1] == -1){
                        ndp[(sum + gifts[j]) % class_sizes[i]][moves+1] = gifts[j];
                    }
                }
            }
            swap(dp, ndp);
        }
        int curr_sz = class_sizes[i];
        int gift_used = dp[0][class_sizes[i]];
        int curr_sum = 0;
        while (curr_sz != 0){
            ans[old_class_sizes[i][1]].push_back(gift_used);
            gifts.erase(find(gifts.begin(), gifts.end(), gift_used));
            curr_sum = ((curr_sum - gift_used) % class_sizes[i] + class_sizes[i]) % class_sizes[i];
            curr_sz--;
            if (curr_sz != -1){
                gift_used = dp[curr_sum][curr_sz];
            }
        }
    }
    cout << answer << "\n";
    for (int i = 0; i < k; i++){
        for (int j : ans[i]){
            cout << j << " ";
        }
        cout << "\n";
    }
}