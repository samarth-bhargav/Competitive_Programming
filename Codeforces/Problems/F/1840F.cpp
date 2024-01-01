#include <bits/stdc++.h>

using namespace std;

int dx[4] = {0,  1 };
int dy[4] = {1,  0};
const int INF = 2e9;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        int n, m; cin >> n >> m;
        int numShots; cin >> numShots;
        vector<array<int,3>> shots(numShots);
        for (int i = 0; i < numShots; i++){
            cin >> shots[i][0] >> shots[i][1] >> shots[i][2];
        }
        numShots++;
        sort(shots.begin(), shots.end());
        shots.push_back({INF, 1, 0});
        queue<pair<array<int, 2>, int>> bfs;
        vector<vector<bool>> vis(n+1, vector<bool>(m+1, false));
        vis[0][0] = true;
        int currTime = 0;
        bool solved = false;
        for (int i = 0; i < numShots; i++){
            int depth = shots[i][0] - currTime;
            for (int j = 0; j <= n; j++){
                for (int k = 0; k <= m; k++){
                    if (vis[j][k]){
                        bfs.push({{j, k}, 0});
                    }
                }
            }
            vector<vector<int>> depthReached(n+1, vector<int> (m+1, 0));
            while (!bfs.empty()){
                array<int, 2> top = bfs.front().first;
                int currDepth = bfs.front().second;
                depthReached[top[0]][top[1]] = currDepth;
                bfs.pop();
                if (currDepth == depth) continue;
                for (int d = 0; d < 2; d++){
                    int newx = top[0]+dx[d], newy = top[1]+dy[d];
                    if (0 <= newx && newx <= n && 0 <= newy && newy <= m && !vis[newx][newy]){
                        bfs.push({{newx, newy}, currDepth+1});
                        vis[newx][newy] = true;
                    }
                }
            }
            if (vis[n][m] && depthReached[n][m] != depth){
                cout << currTime + depthReached[n][m] << "\n";
                solved = true;
                break;
            }
            if (shots[i][1] == 1){
                //horizontal
                for (int j = 0; j <= m; j++){
                    vis[shots[i][2]][j] = false;
                }
            }
            else{
                for (int j = 0; j <= n; j++){
                    vis[j][shots[i][2]] = false;
                }
            }
            currTime = shots[i][0];
        }
        if (!solved){
            cout << -1 << "\n";
        }
    }
}