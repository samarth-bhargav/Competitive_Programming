#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n; cin >> n;
        string s; cin >> s;
        if (n%2 == 1){
            cout << "-1\n";
            continue;
        }
        deque<int> str;
        for (int i = 0; i < s.size(); i++){
            str.push_back(s[i] - '0');
        }
        unordered_set<string> memo;
        vector<int> ops;

        auto dq_to_string = [&](deque<int> &d){
            string ret;
            for (int i = 0; i < d.size(); i++){
                ret.push_back(d[i] + '0');
            }
            return ret;
        };

        bool bad = false;

        string acc_string = s;
        int start_dq = 0;

        for (int i = 0; i < 300; i++){
            string dq = dq_to_string(str);
            if (memo.contains(dq)){
                bad = true; break;
            }
            memo.insert(dq);
            if (str.empty()) break;
            if (str[0] != str.back()){
                start_dq++;
                i--; str.pop_front(); str.pop_back(); continue;
            }
            if (str[0] == 0){
                acc_string.insert(start_dq + str.size(), "01");
                ops.push_back(start_dq + str.size());
                str.push_back(0); str.push_back(1);
                str.pop_front(); str.pop_back();
                start_dq++;
            }
            else{
                acc_string.insert(start_dq, "01");
                ops.push_back(start_dq);
                str.push_front(1); str.push_front(0);
                str.pop_front(); str.pop_back();
                start_dq++;
            }
        }

        if (bad){
            cout << "-1\n";
        }
        else{
            cout << ops.size() << "\n";
            for (int i = 0; i < ops.size(); i++){
                cout << ops[i] << " ";
            }
            cout << "\n";
        }
    }
}