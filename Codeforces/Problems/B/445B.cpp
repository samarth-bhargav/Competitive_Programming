/*
Author: treewave
orz
*/
#include <iostream>
#include <map>
#include <vector>

const int mxN = 55;
int n,one,two,three,four;
bool ar[mxN][mxN], vis[mxN][mxN];

struct dsu{
    std::map <std::pair<int,int>,std::pair<int,int>>parent;
    void init(){
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                parent.insert(make_pair(std::make_pair(i,j),std::make_pair(i,j)));
            }
        }
    }
    std::pair<int,int> find(std::pair <int,int> x){
        if (parent[x] == x){
            return x;
        }
        return parent[x] = find(parent[x]);
    }
    void join(std::pair<int,int>a, std::pair<int,int>b) {
        std::pair<int, int> c = find(a);
        std::pair<int, int> d = find(b);
        parent[c] = d;
    }
    std::vector <std::pair<int,int>> acnt;
    std::vector <std::pair<int,int>> bcnt;
    void solve(){
        std::pair<int,int> a = find({one,two});
        std::pair<int,int> b = find({three,four});
        for (auto & i : parent){
            if (i.second == a){
                acnt.push_back(i.first);
            }
            if (i.second == b){
                bcnt.push_back(i.first);
            }
        }
        int ans = 1e9;
        for (auto & i : acnt){
            for (auto & j : bcnt){
                ans = std::min(ans,(i.first-j.first) * (i.first-j.first) + (i.second - j.second) * (i.second - j.second));
            }
        }
        std::cout << ans << "\n";
    }
} ans;

bool valid(std::pair<int,int>a){
    if (a.first >= n || a.first < 0 || a.second >= n || a.second < 0){
        return false;
    }
    if (vis[a.first][a.second] || ar[a.first][a.second] == 1){
        return false;
    }
    return true;
}

void dfs(std::pair<int,int>c,std::pair<int,int>a){
    vis[c.first][c.second] = true;
    ans.join(c,a);
    if (valid({c.first+1,c.second})){
        dfs({c.first+1,c.second},c);
    }
    if (valid({c.first,c.second+1})){
        dfs({c.first,c.second+1},c);
    }
    if (valid({c.first-1,c.second})){
        dfs({c.first-1,c.second},c);
    }
    if (valid({c.first,c.second-1})){
        dfs({c.first,c.second-1},c);
    }
}

int main() {
    std::cin >> n;
    std::cin >> one >> two >> three >> four;
    one--; two--; three--; four--;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            char h;
            std::cin >> h;
            ar[i][j] = h == '1';
        }
    }
    ans.init();
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (ar[i][j] == 0){
                dfs({i,j},{i,j});
            }
        }
    }
    ans.solve();
}