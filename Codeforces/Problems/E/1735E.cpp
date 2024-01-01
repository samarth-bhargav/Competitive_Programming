#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while (t--){
        int n; cin >> n;
        vector<int> d1(n), d2(n);
        for (int i = 0; i < n; i++){
            cin >> d1[i];
        }
        for (int i = 0; i < n; i++){
            cin >> d2[i];
        }
        vector<int> poss_dst;
        for (int i = 0; i < n; i++){
            poss_dst.push_back(d1[0] + d2[i]);
            poss_dst.push_back(abs(d1[0] - d2[i]));
        }
        bool solved = false;
        for (int l : poss_dst){
            multiset<array<int, 2>> combined;
            for (int i = 0; i < n; i++){
                combined.insert({d1[i], 0});
                combined.insert({d2[i], 1});
            }
            vector<int> match;
            while (!combined.empty()){
                array<int,2> bk = *prev(combined.end());
                int val = bk[0], og = bk[1];
                auto it = combined.find({abs(val - l), og ^ 1});
                if (it != combined.end()){
                    if (og == 0){
                        match.push_back(val);
                    }
                    else{
                        match.push_back(l-val);
                    }
                    combined.erase(it);
                    combined.erase(prev(combined.end()));
                }
                else{
                    break;
                }
            }
            if (combined.empty()){
                solved = true;
                cout << "YES\n";
                //normalize match
                int minelem = min(*min_element(match.begin(), match.end()), 0);
                for (int i = 0; i < n; i++){
                    cout << match[i] - minelem << " ";
                }
                cout << "\n";
                cout << -minelem << " " << -minelem + l << "\n";
                break;
            }
        }
        if (!solved){
            cout << "NO\n";
        }
    }
}