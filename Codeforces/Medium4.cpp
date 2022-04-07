//babybeluga
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
*/
#define int ll
struct Interval {
    int start, end;
    bool operator ==(const Interval & o) const{
        return o.start == start && o.end == end;
    }
};

bool compare(Interval i1, Interval i2)
{ return i1.start < i2.start; }

vector<Interval> merge(vector<Interval>arr, int n){
    stack<Interval> s;
    sort(arr.begin(),arr.end(),compare);
    s.push(arr[0]);
    for (int i = 1 ; i < n; i++){
        Interval top = s.top();
        if (top.end < arr[i].start)
            s.push(arr[i]);
        else if (top.end < arr[i].end){
            top.end = arr[i].end;
            s.pop();
            s.push(top);
        }
    }
    vector<Interval>ret;
    while (!s.empty()){
        Interval t = s.top();
        ret.push_back(t);
        s.pop();
    }
    return ret;
}
signed main() {
    int N, M, R; cin >> N >> M >> R;
    vector<Interval> lit_regions;
    for(int i = 0; i < N; ++i){
        Interval r;
        int x; cin >> x;
        r.start = x-R;
        r.end = x+R;
        lit_regions.push_back(r);
    }
    vector<Interval>ans = merge(lit_regions, lit_regions.size());
    sort(ans.begin(),ans.end(),compare);
    ans.erase(unique(ans.begin(),ans.end()),ans.end());
    int answer = ans.size()-1;
    for (int i = 1; i < ans.size(); i++){
        if (ans[i].start - ans[i-1].end == 1){
            answer--;
        }
    }
    for (auto & i : ans){
        cerr << i.start << " " << i.end << "\n";
    }
    if (ans[0].start > 1){
        answer++;
    }
    if (ans[ans.size()-1].end < M){
        answer++;
    }
    cout << answer << "\n";
}

