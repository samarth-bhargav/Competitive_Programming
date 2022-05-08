#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define ar2 array<int, 2>
#define ar4 array<int, 4>
#define pi pair<int, int>

const int MN = 1e2+3;

struct dsu{
    vector<int> sz; vector<int> parent;
    void init(int N){
        sz = vector<int>(N, 1);
        parent = vector<int>(N);
        std::iota(all(parent), 0);
    }

    int find(int x){
        return x == parent[x] ? x : parent[x] = find(parent[x]);
    }
    bool join(int a, int b){
        a = find(a); b = find(b);
        if(a == b){
            return false;
        }
        if (sz[a] > sz[b]) swap(a, b);
        parent[a] = b;
        sz[b] += sz[a];
        return true;
    }
    bool sameSet(int a, int b){
        return find(a) == find(b);
    }
    int size(int x){
        return sz[find(x)];
    }
    void print(int N){
        for(int i = 0; i < N; ++i){
            cerr << find(i) << " ";
        }
        cerr << endl;
    }
} d;

int N, K, R;
int G[MN][MN], grid[MN][MN];
int cows[MN];
const int dx[4]={-1, 1, 0, 0}, dy[4] = {0, 0, 1, -1};
ar4 roads[MN];
map<int, ar2> mp;
map<ar2, int> mp1;

bool valid(int x, int y){
    if(x < 0 || y < 0 || x >= N || y >= N){
        return false;
    }
    return true;
}

void solve(){
    cin >> N >> K >> R;
    d.init(N*N);
    int cnt = 0;
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < N; ++j){
            grid[i][j] = cnt;
            mp[cnt] = {i, j};
            mp1[{i, j}] = cnt;
            ++cnt;
        }
    }

    // Add Roads
    set<ar2> found;
    for(int i = 0; i < R; ++i){
        cin >> roads[i][0] >> roads[i][1] >> roads[i][2] >> roads[i][3];
        --roads[i][0], --roads[i][1], --roads[i][2], --roads[i][3];
        ar2 r = {grid[roads[i][0]][roads[i][1]], grid[roads[i][2]][roads[i][3]]};
        ar2 r1 = {grid[roads[i][2]][roads[i][3]], grid[roads[i][0]][roads[i][1]]};
        found.insert(r); found.insert(r1);
    }

    for(int i = 0; i < N*N; ++i){
        for(int k = 0; k < 4; ++k){
            int nx = mp[i][0]+dx[k], ny = mp[i][1]+dy[k];
            if(valid(nx, ny)){
                if(found.find({i, mp1[{nx, ny}]})==found.end() || found.find({mp1[{nx, ny}], i})==found.end()){
                    d.join(i, mp1[{nx, ny}]);
                    found.insert({i, mp1[{nx, ny}]});
                    found.insert({mp1[{nx, ny}], i});
                }
            }
        }
    }

    for(int i = 0; i < K; ++i){
        ar2 cow = {0, 0};
        cin >> cow[0] >> cow[1]; --cow[0], --cow[1];
        cows[i] = grid[cow[0]][cow[1]];
    }

    int ans = 0;
    set<ar2> seen;
    for(int i = 0; i < K; ++i){
        for(int j = 0; j < K; ++j){
            if((seen.find({cows[i], cows[j]}) == seen.end()) || seen.find({cows[j], cows[i]}) == seen.end()){
                if(!d.sameSet(cows[i], cows[j])){
                    ans++;
                    seen.insert({cows[i], cows[j]});
                    seen.insert({cows[j], cows[i]});
                }
            }
        }
    }
    cout << ans << "\n";
}

int main(){
//    freopen("countcross.in", "r", stdin); freopen("countcross.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);
    solve();
}