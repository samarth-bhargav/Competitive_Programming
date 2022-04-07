#include <bits/stdc++.h>
using namespace std;

const int MN = 28;

int N;
char G[MN][3*MN];
bool visited[MN][MN];
map<string,vector<array<string,2>>>W;

int dx[4] = {0,0,1,-1}, dy[4] = {3,-3,0,0};

bool winning(vector<vector<char>>board){
    if (board[0][0] == 'M' && board[1][0] == 'O' && board[2][0] == 'O'){return true;}
    if (board[0][1] == 'M' && board[1][1] == 'O' && board[2][1] == 'O'){return true;}
    if (board[0][2] == 'M' && board[1][2] == 'O' && board[2][2] == 'O'){return true;}
    if (board[0][0] == 'O' && board[1][0] == 'O' && board[2][0] == 'M'){return true;}
    if (board[0][1] == 'O' && board[1][1] == 'O' && board[2][1] == 'M'){return true;}
    if (board[0][2] == 'O' && board[1][2] == 'O' && board[2][2] == 'M'){return true;}
    if (board[0][0] == 'M' && board[0][1] == 'O' && board[0][2] == 'O'){return true;}
    if (board[1][0] == 'M' && board[1][1] == 'O' && board[1][2] == 'O'){return true;}
    if (board[2][0] == 'M' && board[2][1] == 'O' && board[2][2] == 'O'){return true;}
    if (board[0][0] == 'O' && board[0][1] == 'O' && board[0][2] == 'M'){return true;}
    if (board[1][0] == 'O' && board[1][1] == 'O' && board[1][2] == 'M'){return true;}
    if (board[2][0] == 'O' && board[2][1] == 'O' && board[2][2] == 'M'){return true;}
    if (board[0][0] == 'M' && board[1][1] == 'O' && board[2][2] == 'O'){return true;}
    if (board[2][0] == 'M' && board[1][1] == 'O' && board[0][2] == 'O'){return true;}
    if (board[0][0] == 'O' && board[1][1] == 'O' && board[2][2] == 'M'){return true;}
    if (board[2][0] == 'O' && board[1][1] == 'O' && board[0][2] == 'M'){return true;}
    return false;
}
vector<string>poss;
bool valid(int x, int y){
    if (x >= N || y >= 3*N || x < 0 || y < 0){
        return false;
    }
    return !visited[x][y];
}
map<string,vector<vector<string>>>mp;
void dfs(int x, int y, vector<string>crossed){
    visited[x][y] = true;
    if (G[x][y-1] == 'O' || G[x][y-1] == 'M'){
        string s;
        s += G[x][y-1];
        s += ((int)(G[x][y]-48)-1)+'0';
        s += ((int)(G[x][y+1]-48)-1)+'0';
        mp[s].push_back(crossed);
        crossed.push_back(s);
    }
    for (int i = 0; i < 4; i++){
        int x1 = x + dx[i]; int x2 = x + dy[i];
        if (valid(x1,x2)){
            dfs(x1,x2,crossed);
        }
    }
}
void solve(){
    cin >> N;
    vector<array<int,2>>init;
    for(int i = 0; i < N; i++){
        for (int j = 0; j < 3*N; j++){
            cin >> G[i][j];
            if (G[i][j] == 'B'){
                init.push_back({i,j});
            }
        }
    }
    sort(init.begin(),init.end());
    vector<string>V;
    dfs(init[1][0],init[1][1],V);
    array<char,2>chars = {'O','M'};
    array<char,3>xs = {'0','1','2'};
    array<char,3>ys = {'0','1','2'};
    for (auto & i : chars){
        for (auto & j : xs){
            for (auto & k : ys){
                string s;
                s += i; s += j; s += k;
                for (auto & v : mp[s]){
                    vector<vector<char>>board;
                    board.
                }
            }
        }
    }
}

/*
 Idea: Keep track of all tic tac toe thingies youve visited so
*/
int main(){
    cin.tie(0)->sync_with_stdio(0);
    solve();
}