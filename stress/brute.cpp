#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n; cin >> n;
        string s; cin >> s;
        int ans = 0;
        for (int i = 0; i < n; i++){
            for (int j = i; j < n; j++){
                stack<int> x;
                for (int k = i; k <= j; k++){
                    if (s[k] == ')'){
                        if (!x.empty() && x.top() == '('){
                            x.pop();
                        }
                        else{
                            x.push(')');
                        }
                    }
                    else{
                        x.push('(');
                    }
                }
                int onect = 0, negct = 0;
                while (!x.empty()){
                    char c = x.top();
                    x.pop();
                    if (c == '('){
                        onect++;
                    }
                    else{
                        negct++;
                    }
                }
                ans += negct;
            }
        }
        cout << ans << "\n";
    }
}
