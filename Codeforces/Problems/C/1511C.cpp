/*
Dont raise your voice,improve your argument
--Desmond Tutu
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

#define oset tree<pair<int,int>, null_type,less<pair<int,int>>, rb_tree_tag,tree_order_statistics_node_update>
/*
*/
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,q;
    cin >> n >> q;
    map<int,int>mp; //maps color to first idx
    oset a;
    int index = 0;
    for (int i = 1; i <= n; i++){
        int x;
        cin >> x;
        if (mp.find(x) == mp.end()){
            mp[x] = i;
        }
        a.insert({i,x});
    }
    while (q--){
        int color;
        cin >> color;
        int idx = mp[color];
        cout << a.order_of_key(make_pair(idx,color))+1 << " ";
        a.erase(make_pair(idx,color));
        a.insert({index,color});
        mp[color] = index;
        index--;
    }
    cout << "\n";
}

