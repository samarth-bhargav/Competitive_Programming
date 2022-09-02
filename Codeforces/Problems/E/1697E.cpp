#include <bits/stdc++.h>
using namespace std;

const int mxN = 105, M = 998244353;

vector<array<int, 2>> points;
set<array<int, 2>> distances[mxN];
long long dp[mxN][mxN];
int nCr[mxN][mxN];
long long f[mxN];
vector<int> vis(mxN, false);

int dist(array<int, 2> a, array<int, 2> b){
    return ((abs(a[0] - b[0]) + abs(a[1] - b[1])) % M + M) % M;
}

int main(){
    int n;
    cin >> n;
    memset(nCr, 0, sizeof(nCr));
    for (int i = 0; i <= n; i++){
        nCr[i][0] = 1;
        nCr[i][1] = i;
    }
    for (int i = 2; i <= n; i++){
        for (int j = 2; j <= i; j++){
            nCr[i][j] = ((nCr[i-1][j-1] + nCr[i-1][j]) % M + M) % M;
        }
    }
    f[0] = 1;
    for (int i = 1; i <= n; i++){
        f[i] = ((f[i-1] * i) % M + M) % M;
    }
    for (int i = 0; i < n; i++){
        int a, b;
        cin >> a >> b;
        points.push_back({a,b});
    }
    //get distances
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (i != j){
                distances[i].insert({dist(points[i], points[j]), j});
            }
        }
    }
    //form groups
    vector<int> groups;
    for (int i = 0; i < n; i++){
        if (vis[i]){
            continue;
        }
        vector<int> viscpy(vis.begin(), vis.end());
        vector<int> curr_nodes;
        curr_nodes.push_back(i);
        vis[i] = true;
        int grp_size = 1, set_dist = -1;
        for (auto it = distances[i].begin(); it != distances[i].end(); it++){
            array<int, 2> x = *it;
            if (set_dist == -1){
                set_dist = x[0];
                grp_size++;
                vis[x[1]] = true;
                curr_nodes.push_back(x[1]);
            }
            else{
                if (x[0] != set_dist){
                    break;
                }
                else{
                    grp_size++;
                    vis[x[1]] = true;
                    curr_nodes.push_back(x[1]);
                }
            }
            vis[x[1]] = true;
        }
        //check if each condition is satisfied
        bool flag = false;
        for (int a : curr_nodes){
            for (int b : curr_nodes){
                if (a != b){
                    if (dist(points[a], points[b]) != set_dist){
                        flag = true;
                        break;
                    }
                }
            }
        }
        for (int a : curr_nodes){
            for (array<int, 2> x : distances[a]){
                if (x[0] < set_dist){
                    flag = true;
                    break;
                }
                else if (x[0] > set_dist){
                    break;
                }
                else{
                    if (find(curr_nodes.begin(), curr_nodes.end(), x[1]) == curr_nodes.end()){
                        flag = true;
                        break;
                    }
                }
            }
        }
        if (flag){
            for (int a : curr_nodes){
                if (a != i){
                    vis[a] = viscpy[a];
                }
            }
            groups.push_back(1);
        }
        else{
            if (grp_size == 2){
                for (int x : curr_nodes){
                    cerr << points[x][0] << " " << points[x][1] << "\n";
                }
                cerr << "\n";
            }
            for (int x : curr_nodes){
                vis[x] = true;
            }
            groups.push_back(grp_size);
        }
    }
    for (int i = 0; i < groups.size(); i++){
        cerr << groups[i] << " ";
    }
    cerr << "\n";
    memset(dp, 0, sizeof(dp));
    dp[0][1] = 1;
    dp[0][groups[0]] = f[groups[0]];
    for (int i = 1; i < groups.size(); i++){
        for (int c = 0; c <= n; c++){
            if (c - groups[i] >= 0){
                dp[i][c] = ((dp[i-1][c-groups[i]] * nCr[c][groups[i]]) % M + M) % M;
                dp[i][c] = ((dp[i][c] * f[groups[i]]) % M + M) % M;
            }
            if (c - 1 >= 0 && groups[i] != 1){
                dp[i][c] = ((dp[i][c] + (dp[i-1][c-1] * c)) % M + M) % M;
            }
        }
    }
    long long ans = 0;
    for (int c = 0; c <= n; c++){
        ans = ((ans + nCr[n][c] * dp[groups.size()-1][c]) % M + M) % M;
    }
    cout << ans << "\n";
}
