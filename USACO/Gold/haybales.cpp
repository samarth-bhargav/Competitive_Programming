#include <bits/stdc++.h>
using namespace std;

#define int long long
const int mxN = 1e5;
int k = 1e5;

vector<int> solved(mxN, -1), deltas(mxN+1, -1);
//deltas[x] = solved[x+1] - solved[x]
int solve(vector<pair<int,int>> vals, int delta){
    solved[vals[0].first] = delta;
    map<int,int> defaults, plusk;
    for (int i = 0; i < vals.size(); i++){
        if (vals[i].second == 0){
            defaults[vals[i].first] = i;
        }
        else{
            plusk[vals[i].first] = i;
        }
    }
    queue<int> processed;
    processed.push(vals[0].first);
    while (!processed.empty()){
        int idx = processed.front();
        int last_val = solved[idx] + k;
        for (int i = plusk[idx]-1; i >= defaults[idx]; i--){
            if (solved[vals[i].first] != -1){
                continue;
            }
            if (vals[i].second == 0){
                solved[vals[i].first] = last_val - 1;
                processed.push(vals[i].first);
                last_val--;
            }
            else{
                solved[vals[i].first] = last_val - 1 - k;
                last_val--;
            }
        }
        processed.pop();
    }
    return solved[vals[vals.size() - 1].first];
}

int32_t main(){
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++){
        cin >> a[i]; a[i]--;
    }
    vector<pair<int,int>> sorted_order;
    for (int i = 0; i < n; i++){
        sorted_order.push_back({i, 0});
        sorted_order.push_back({i, 1});
    }
    sort(sorted_order.begin(), sorted_order.end(), [&](pair<int, int> x, pair<int,int> y){
       if (x.second == y.second){
           return x < y;
       }
       if (x.first == y.first){
           return x.second == 0;
       }
       if (x.second == 1){
           return a[x.first] <= y.first;
       }
       return x.first <= a[y.first];
    });
    set<int> unfinished;
    vector<pair<int, int>> curr;
    int initial = 1;
    for (int i = 0; i < 2*n; i++){
        if (sorted_order[i].second == 0){
            unfinished.insert(sorted_order[i].first);
            curr.push_back(sorted_order[i]);
        }
        else{
            unfinished.erase(sorted_order[i].first);
            curr.push_back(sorted_order[i]);
            if (unfinished.empty()){
                initial = solve(curr, initial) + 2*k;
                curr.clear();
                curr.shrink_to_fit();
            }
        }
    }
    cout << k << "\n";
    for (int i = 0; i < n; i++){
        cout << solved[i] << "\n";
    }
}