#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#define ordered_set tree<pair<int,int>, null_type,less<pair<int,int>>, rb_tree_tag,tree_order_statistics_node_update>

void printoset(ordered_set x){
    cerr << '[';
    for (auto & i : x){
        cerr << '(';
        cerr << i.first << ", " << i.second;
        cerr << ')';
    }
    cerr << ']';
    cerr << "\n";
}

int main(){
    ifstream cin("measurement.in");
    ofstream cout("measurement.out");
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,g;
    cin >> n >> g;
    map <int,int> mp;
    multiset<pair<int,pair<int,int>>>events; //.first = day, .second.first = id, .second.second = change
    ordered_set cows; //.first milk .second id
    for (int i = 0; i < n; i++){
        int a,b,c;
        cin >> a >> b >> c;
        events.insert({a,{b,c}});
    }
    for (auto & i : events){
        mp[i.second.first] = g;
    }
    for (auto & i : mp){
        cows.insert({g,i.first});
    }
    int numbestcows = mp.size();
    int bestcow = g; //if there only one best cow
    int ans = 0;
    for (auto & i : events){
        int id = i.second.first;
        int change = i.second.second;
        auto it = cows.lower_bound({mp[id],id});
        cows.erase(it);
        mp[id] += change;
        cows.insert({mp[id],id});
        if (cows.upper_bound({prev(cows.end())->first,0}) == prev(cows.end())){
            if (bestcow != prev(cows.end())->second){
                bestcow = prev(cows.end())->second;
                numbestcows = 1;
                ans++;
            }
        }
        else{
            int x = mp.size()-cows.order_of_key({prev(cows.end())->first,0});
            if (x != numbestcows){
                numbestcows = x;
                ans++;
            }
        }
    }
    cout << max(ans,1) << "\n";
}