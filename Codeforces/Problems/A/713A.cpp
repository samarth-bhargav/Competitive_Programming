/*
Dont raise your voice,improve your argument
--Desmond Tutu
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
*/
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--){
        int n;
        cin >> n;
        vector<int>a(n);
        for (auto & i : a){
            cin >> i;
        }
        map<int,set<int>>mp;
        for (int i = 0; i < n; i++){
            mp[a[i]].insert(i);
        }
        for (auto & i : mp){
            if (i.second.size() == 1){
                cout << *i.second.begin()+1 << "\n";
                break;
            }
        }
    }
}

