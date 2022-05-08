//babybeluga
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
*/
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,m;
    cin >> n >> m;
    vector<pair<int,int>>cereals;
    for (int i = 0; i < n; i++){
        int a,b;
        cin >> a >> b;
        cereals.emplace_back(a,b);
    }
    int used_in[m];
    memset(used_in, 0, sizeof(used_in));
    vector<int> solution;
    set<int> taken;
    set<int> seconds_available;
    for (int i = 0; i < n; i++){
        solution.push_back(i);
        int first = cereals[i].first;
        int second = cereals[i].second;
        if (seconds_available.find(first) != seconds_available.end()){
            seconds_available.erase(first);
            swap(solution[used_in[first]], solution[i]);
            used_in[first] = i;
            used_in[solution[i]]
        }
    }
}

