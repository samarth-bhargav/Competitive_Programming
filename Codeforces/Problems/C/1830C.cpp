#include <bits/stdc++.h>

using namespace std;

const int mxI = 1e6;
const int mxN = 3e5 + 5;
const int M = 998244353;
vector<int> adj[mxI];
long long invf[mxN+1], fac[mxN+1], cat[mxN+1];
vector<array<int,2>> decomp_intervals;

long long binpow(long long x, int e){
    long long res = 1;
    while (e > 0){
        if (e & 1){
            res = (res * x) % M;
        }
        x = (x * x) % M;
        e >>= 1;
    }
    return (res % M + M) % M;
}

int nCr(int n, int r){
    long long res = fac[n];
    res *= invf[r]; res %= M;
    res *= invf[n-r]; res = (res % M + M) % M;
    return res;
}

void precalc(){
    fac[0] = 1;
    invf[0] = binpow(fac[0], M-2);
    for (int i = 1; i <= mxN; i++){
        fac[i] = (fac[i-1] * i % M + M) % M;
        invf[i] = binpow(fac[i], M-2);
    }
    memset(cat, 0, sizeof(cat));
    for (int i = 0; i < (mxN >> 1); i++){
        cat[i] = (long long)(nCr(2 * i, i)) * binpow(i+1, M-2);
        cat[i] = (cat[i] % M + M) % M;
    }
}

int dfs(int u, int v){
    vector<array<int, 2>> intervals;
    long long ans = 1;
    int tot_size = decomp_intervals[u][1] - decomp_intervals[u][0] + 1;
    for (int neighbor : adj[u]){
        if (neighbor != v){
            ans *= dfs(neighbor, u);
            ans = (ans % M + M) % M;
            tot_size -= (decomp_intervals[neighbor][1] - decomp_intervals[neighbor][0] + 1);
        }
    }
    return ((cat[tot_size >> 1] * ans) % M + M) % M;
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    precalc();
    int t; cin >> t;
    while (t--){
        int n, k; cin >> n >> k;
        vector<array<int,2>> intervals(k+1);
        for (int i = 0; i < k; i++){
            cin >> intervals[i][0] >> intervals[i][1];
        }
        intervals[k] = {1, n};
        bool bad = false;
        for (int i = 0; i <= k; i++){
            if ((intervals[i][1] - intervals[i][0] + 1) % 2 == 1){
                bad = true;
                cout << 0 << "\n";
                break;
            }
        }
        if (bad) continue;
        //remove multiplicity of start points
        vector<set<int>> originating(n+1);
        for (int i = 0; i < intervals.size(); i++){
            originating[intervals[i][0]].insert(intervals[i][1]);
        }
        for (int i = 1; i <= n; i++){
            if (!originating[i].empty()){
                int curr = *originating[i].begin() + 1;
                for (auto it = next(originating[i].begin()); it != originating[i].end(); it++){
                    originating[curr].insert(*it);
                    curr = *it + 1;
                }
                curr = *originating[i].begin();
                originating[i].clear();
                originating[i].insert(curr);
            }
        }
        intervals.clear(); intervals.shrink_to_fit();
        for (int i = 1; i <= n; i++){
            for (int elem : originating[i]){
                intervals.push_back({i, elem});
            }
        }
        bad = false;
        for (int i = 0; i < intervals.size(); i++){
            if ((intervals[i][1] - intervals[i][0] + 1) % 2 == 1){
                bad = true;
                cout << 0 << "\n";
                break;
            }
        }
        if (bad) continue;
        set<array<int,3>> events;
        set<array<int, 2>> curr_intervals;
        for (int i = 0; i < intervals.size(); i++){
            events.insert({intervals[i][0], 0, intervals[i][1]});
            events.insert({intervals[i][1], 1, intervals[i][0]});
        }
        decomp_intervals.clear();
        bad = false;
        int iterations = 0;
        while (!events.empty()){
            iterations++;
            array<int, 3> event = *events.begin();
            int point = event[0];
            bool endpoint = event[1];
            int opp_point = event[2];
            events.erase(events.begin());
            if (endpoint){
                curr_intervals.erase({opp_point, point});
                auto it = curr_intervals.upper_bound({opp_point+1, -1});
                if (it == curr_intervals.end() || (*it)[0] > point){
                    it = curr_intervals.lower_bound({opp_point, point});
                    if (it == curr_intervals.end() || (*it)[0] > point){
                        decomp_intervals.push_back({opp_point, point});
                        continue;
                    }
                }
                array<int,2> to_merge = *it;
                curr_intervals.erase(it);

                vector<array<int, 3>> inserts = {
                        {to_merge[1], 1, to_merge[0]},
                        {point, 1, to_merge[0]},
                        {to_merge[0], 0, point},
                        {point+1, 0, to_merge[1]},
                        {to_merge[1], 1, point+1},
                        {opp_point, 0, to_merge[0]-1},
                        {to_merge[0]-1, 1, opp_point}
                };
                events.erase(inserts[0]);
                if (opp_point != to_merge[0]){
                    events.insert(inserts.begin()+5, inserts.end());
                }
                if (point != to_merge[0]){
                    events.insert(inserts.begin()+1, inserts.begin()+3);
                }
                else{
                    cout << 0 << "\n";
                    bad = true;
                    break;
                }
                if (point != to_merge[1]){
                    events.insert(inserts.begin()+3, inserts.begin()+5);
                }
            }
            else{
                curr_intervals.insert({point, opp_point});
            }
        }
        if (bad) continue;
        sort(decomp_intervals.begin(), decomp_intervals.end());
//        for (int i = 0; i < decomp_intervals.size(); i++){
//            cout << decomp_intervals[i][0] << " " << decomp_intervals[i][1] << "\n";
//        }
//        cout << "\n";
        bad = false;
        for (int i = 0; i < decomp_intervals.size(); i++){
            if ((decomp_intervals[i][1] - decomp_intervals[i][0]) % 2 == 0){
                cout << 0 << "\n";
                bad = true;
                break;
            }
        }
//        for (array<int, 2> r1 : decomp_intervals){
//            for (array<int, 2> r2 : decomp_intervals){
//                assert((r1[0] <= r2[0] && r2[1] <= r1[1]) || (r2[0] <= r1[0] && r1[1] <= r2[1]));
//            }
//        }
        if (bad) continue;
        events.clear();
        curr_intervals.clear();
        for (int i = 0; i < decomp_intervals.size(); i++){
            events.insert({decomp_intervals[i][0], 1, i});
            events.insert({decomp_intervals[i][1], 0, i});
        }
        vector<int> roots;
        for (array<int, 3> event : events){
            bool startpoint = event[1];
            int idx = event[2];
            if (!startpoint){
                curr_intervals.erase({decomp_intervals[idx][0], idx});
            }
            else{
                if (curr_intervals.empty()){
                    roots.push_back(idx);
                }
                else{
                    adj[idx].push_back((*curr_intervals.rbegin())[1]);
                    adj[(*curr_intervals.rbegin())[1]].push_back(idx);
                }
                curr_intervals.insert({decomp_intervals[idx][0], idx});
            }
        }
        long long ans = 1;
        for (int root : roots){
            ans *= dfs(root, -1);
            ans = (ans % M + M) % M;
        }
        cout << ans << "\n";
        for (int i = 0; i < decomp_intervals.size(); i++){
            adj[i].clear();
            adj[i].shrink_to_fit();
        }
    }
}