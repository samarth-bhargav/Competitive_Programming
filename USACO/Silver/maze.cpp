#include <bits/stdc++.h>
using namespace std;

const int MN = 25;
int N;
char G[MN][MN*3];
set<vector<vector<char>>>answers;

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
bool full(vector<vector<char>>board){
    if (board[0][0] != '.' && board[0][1] != '.' && board[0][2] != '.'){
        if (board[1][0] != '.' && board[1][1] != '.' && board[1][2] != '.'){
            if (board[2][0] != '.' && board[2][1] != '.' && board[2][2] != '.'){
                return true;
            }
        }
    }
    return false;
}
bool valid(int x, int y){
    if (x >= N || y >= 3*N || x < 0 || y < 0){
        return false;
    }
    if (G[x][y] == '#'){
        return false;
    }
    return true;
}
void dfs(int x, int y, vector<vector<char>>board, vector<vector<bool>>vis){
    if (winning(board)){
        answers.insert(board);
        return;
    }
    if (full(board)){
        return;
    }
    vis[x][y] = true;
    //update board
    if (G[x][y-1] == 'M'){
        int a = G[x][y] - 48;
        int b = G[x][y+1]-48;
        a--; b--;
        if (board[a][b] == '.'){
            board[a][b] = 'M';
        }
    }
    if (G[x][y-1] == 'O'){
        int a = G[x][y] - 48;
        int b = G[x][y+1]-48;
        a--; b--;
        if (board[a][b] == '.'){
            board[a][b] = 'O';
        }
    }
    if (valid(x,y+3)){
        if (!vis[x][y+3]){
            dfs(x,y+3,board,vis);
            vis[x][y+3] = false;
        }
    }
    if (valid(x,y-3)){
        if (!vis[x][y-3]){
            dfs(x,y-3,board,vis);
            vis[x][y-3] = false;
        }
    }
    if (valid(x+1,y)){
        if (!vis[x+1][y]){
            dfs(x+1,y,board,vis);
            vis[x+1][y] = false;
        }
    }
    if (valid(x-1,y)){
        if (!vis[x-1][y]){
            dfs(x-1,y,board,vis);
            vis[x-1][y] = false;
        }
    }
    vis[x][y] = false;
}
void solve(){
    cin >> N;
    vector<array<int,2>>init;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < 3*N; j++){
            cin >> G[i][j];
            if (G[i][j] == 'B'){
                init.push_back({i,j});
            }
        }
    }
    sort(init.begin(),init.end());
    vector<vector<char>>board(3,vector<char>(3,'.'));
    vector<vector<bool>>vis(N,vector<bool>(3*N,0));
    dfs(init[1][0],init[1][1],board,vis);
    cout << answers.size() << "\n";
    for (auto & x : answers){
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++){
                cerr << x[i][j] << " ";
            }
            cerr << "\n";
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    solve();
}

