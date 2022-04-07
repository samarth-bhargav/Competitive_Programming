/*
Author: treewave
orz
*/
#include <bits/stdc++.h>

using namespace std;

int main() {
    ifstream cin("reststops.in");
    ofstream cout("reststops.out");
    int l,n,rf,rb;
    cin >> l >> n >> rf >> rb;
    multiset<pair<int,int>>reverse;
    for (int i = 0; i < n; i++){
        int a,b;
        cin >> a >> b;
        reverse.insert({b,a});
    }
    stack<pair<long long,long long>>vals;
    for (auto & i : reverse){
        vals.push(i);
    }
    long long currpos = 0;
    pair<long long,long long>lastpair = {0LL,0LL};
    long long ans = 0;
    while (!vals.empty()){
        pair<int,int>p = vals.top();
        if (p.second < currpos){
            vals.pop();
            continue;
        }
        else{
            currpos = p.second;
            ans += (p.second-lastpair.second)*(rf-rb)*(p.first);
            lastpair = p;
            vals.pop();
            continue;
        }
   }
    cout << ans << "\n";
}

