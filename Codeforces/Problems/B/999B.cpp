/*
Dont raise your voice,improve your argument
--Desmond Tutu
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
*/
set<int> div(int x){
    set<int>ret;
    for (int i = 1; i <= x; i++){
        if (x%i == 0){
            ret.insert(i);
            ret.insert(x/i);
        }
    }
    return ret;
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    vector<char>s(n+1);
    for (int i = 1; i <= n; i++)
        cin >> s[i];
    set<int>x = div(n);
    vector<pair<int,int>>iv;
    for (auto & i : x){
        iv.emplace_back(1,i);
    }
    for (auto & i : iv){
        cerr << i.first << " " << i.second << "\n";
    }
    for (auto & i : iv){
        reverse(s.begin()+i.first,s.begin()+i.second+1);
    }
    for (int i = 1; i <= n; i++){
        cout << s[i];
    }
    cout << "\n";
}

