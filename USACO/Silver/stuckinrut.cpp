#include <bits/stdc++.h>
using namespace std;

vector<int>adj[1005];

int main(){
    int n;
    cin >> n;
    vector<pair<int,int>>east;
    vector<pair<int,int>>north;
    map<pair<int,int>,int>mp;
    for (int i = 0; i < n; i++){
        char c; int a,b;
        cin >> c >> a >> b;
        if (c == 'N'){
            north.emplace_back(a,b);
        }
        else{
            east.emplace_back(a,b);
        }
        mp[{a,b}] = i+1;
    }
    sort(east.begin(),east.end());

}