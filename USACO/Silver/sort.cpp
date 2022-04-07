/*
Author: treewave
orz
*/
#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

#define ordered_set tree<int, null_type,less_equal<int>, rb_tree_tag,tree_order_statistics_node_update>


void DBG() {
    cout << "]" << endl;
}
template <class T> string to_string(vector<T>v){
    string s;
    s += '{';
    for (T i : v){
        s += to_string(i);
        s += ',';
    }
    s.erase(s.end()-1);
    s += '}';
    return s;
}
template <class T> void printmulti(vector<vector<T>> vii){
    for (int i = 0; i < vii.size(); i++){
        for (int j = 0; j < vii[0].size(); j++){
            cout << vii[i][j] << " ";
        }
        cout << "\n";
    }
}
template<class H, class... T> void DBG(H h, T... t) {
    cout << to_string(h);
    if(sizeof...(t))
        cout << ",";
    DBG(t...);
}
#define dbg(...) cout << "Line " << __LINE__ << " -> [" << #__VA_ARGS__ << "]: [", DBG(__VA_ARGS__)
int main() {
    freopen("sort.in", "r", stdin);
    freopen("sort.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    int ar[n];
    for (int i = 0; i < n; i++){
        cin >> ar[i];
    }
    int ans = 0;
    vector <int> curr;
    curr.push_back(ar[0]);
    for (int i = 1; i < n; i++){
        ans = max(ans,(int)(curr.size()-(upper_bound(curr.begin(), curr.end(), ar[i]) - curr.begin())+1));
//        dbg(ans,curr);
        vector <int> ::iterator pos = lower_bound(curr.begin(),curr.end(),ar[i]);
        curr.insert(pos,ar[i]);
    }
    cout << ans << "\n";
}

