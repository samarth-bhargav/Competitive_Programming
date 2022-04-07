//babybeluga
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
*/
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int k,m,n;
    cin >> k >> m >> n;
    vector<pair<int,int>>grass;
    for (int i = 0; i < k; i++){
        int a,b;
        cin >> a >> b;
        grass.emplace_back(a,b);
    }
    sort(grass.begin(),grass.end());
    vector<int>nhoj;
    for (int i = 0; i < m; i++){
        int a; cin >> a;
        nhoj.push_back(a);
    }
    sort(nhoj.begin(),nhoj.end());
    vector<pair<pair<int,int>,int>> intervals;
    for (auto & i : grass){
        int loc = i.first;
        int closest_distance;
        vector<int>::iterator closest2 = lower_bound(nhoj.begin(),nhoj.end(),loc);
        vector<int>::iterator closest1;
        if (closest2 != nhoj.begin()){
            closest1 = prev(closest2);
        }
        else{
            closest1 = closest2;
        }
        if (closest2 != nhoj.end()){
            closest_distance = min(abs(*closest2-loc),abs(*closest1-loc));
        }
        else{
            closest_distance = abs(*closest1-loc);
        }
        intervals.push_back({{loc-closest_distance,loc+closest_distance},i.second});
    }
    sort(intervals.begin(),intervals.end());
    int iter = 0;
    for (int i = 1; i < intervals.size(); i++){
        if (intervals[iter].first.second > intervals[i].first.first){
            intervals[iter].first.first = max(intervals[iter].first.first,intervals[i].first.first);
            intervals[iter].first.second = min(intervals[iter].first.second,intervals[i].first.second);
            intervals[iter].second += intervals[i].second;
        }
        else{
            iter++;
            
        }
    }
    for (auto & i : intervals){
        cerr << "((" << i.first.first << ", " << i.first.second << "), " << i.second << ")";
        cerr << "\n";
    }
    set<int> answers;
    for (int i = 0; i <= iter; i++){
        answers.insert(intervals[i].second);
    }
    ll ans = 0;
    for (int i = 0; i < n && !answers.empty(); i++){
        ans += *prev(answers.end());
        answers.erase(prev(answers.end()));
    }
    cout << ans << "\n";
}

