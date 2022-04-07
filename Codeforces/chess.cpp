/*
Dont raise your voice,improve your argument
--Desmond Tutu
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
*/

bool valid(int x, int y){
    return (x >= 0 && y >= 0 && x < 8 && y < 8);
}

set<pair<int,int>>whitecovered;
set<pair<int,int>>black;

void blackking(int x, int y){
    if (valid(x+1,y)) black.insert({x+1,y});
    if (valid(x-1,y)) black.insert({x-1,y});
    if (valid(x,y-1)) black.insert({x,y-1});
    if (valid(x,y+1)) black.insert({x,y+1});
    if (valid(x+1,y-1)) black.insert({x+1,y-1});
    if (valid(x+1,y+1)) black.insert({x+1,y+1});
    if (valid(x-1,y-1)) black.insert({x-1,y-1});
    if (valid(x-1,y+1)) black.insert({x-1,y+1});
}
void king(int x, int y){
    if (valid(x+1,y)) whitecovered.insert({x+1,y});
    if (valid(x-1,y)) whitecovered.insert({x-1,y});
    if (valid(x,y-1)) whitecovered.insert({x,y-1});
    if (valid(x,y+1)) whitecovered.insert({x,y+1});
    if (valid(x+1,y-1)) whitecovered.insert({x+1,y-1});
    if (valid(x+1,y+1)) whitecovered.insert({x+1,y+1});
    if (valid(x-1,y-1)) whitecovered.insert({x-1,y-1});
    if (valid(x-1,y+1)) whitecovered.insert({x-1,y+1});
}
void knight(int x, int y){
    if (valid(x+2,y+1)) whitecovered.insert({x+2,y+1});
    if (valid(x+1,y+2)) whitecovered.insert({x+1,y+2});
    if (valid(x+2,y-1)) whitecovered.insert({x+2,y-1});
    if (valid(x+1,y-2)) whitecovered.insert({x+1,y-2});
    if (valid(x-2,y+1)) whitecovered.insert({x-2,y+1});
    if (valid(x-2,y-1)) whitecovered.insert({x-2,y-1});
    if (valid(x-1,y+2)) whitecovered.insert({x-1,y+2});
    if (valid(x-1,y-2)) whitecovered.insert({x-1,y-2});
}
void rook(int x, int y){
    for (int i = 0; i < 8; i++){
        whitecovered.insert({x,i});
    }
    for (int i = 0; i < 8; i++){
        whitecovered.insert({i,y});
    }
}
void bishop(int x, int y){
    int x1 = x,y1 = y,x2 = x,y2 = y,x3 = x,y3 = y,x4 = x,y4 = y;
    while (valid(x1,y1)){
        whitecovered.insert({x1,y1});
        x1--; y1--;
    }
    while (valid(x2,y2)){
        whitecovered.insert({x2,y2});
        x2--; y2++;
    }
    while (valid(x3,y3)){
        whitecovered.insert({x3,y3});
        x3++; y3--;
    }
    while (valid(x4,y4)){
        whitecovered.insert({x4,y4});
        x4++; y4++;
    }
}
void queen(int x, int y){
    bishop(x,y);
    rook(x,y);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    string a,b,c,d,e,f;
    cin >> a >> b >> c >> d >> e >> f;
    pair<int,int>bk,wk,wr,wb,wn,wq;
    bk.first = a[0]-'a'; bk.second = a[1]-'0'-1;
    wk.first = b[0]-'a'; wk.second = b[1]-'0'-1;
    wr.first = c[0]-'a'; wr.second = c[1]-'0'-1;
    wb.first = d[0]-'a'; wb.second = d[1]-'0'-1;
    wn.first = e[0]-'a'; wn.second = e[1]-'0'-1;
    wq.first = f[0]-'a'; wq.second = f[1]-'0'-1;
    vector<pair<int,int>>white;
    white.push_back(wk); white.push_back(wr);
    white.push_back(wb); white.push_back(wn);
    white.push_back(wq);
    for (auto & i : white){
        whitecovered.insert(i);
    }
    king(wk.first,wk.second);
    knight(wn.first,wn.second);
    rook(wr.first,wr.second);
    bishop(wb.first,wb.second);
    queen(wq.first,wq.second);
    blackking(bk.first,bk.second);
    int common = 0, wherecanmove = 0;
    for (auto & i : black){
        if (whitecovered.find(i) != whitecovered.end()){
            common++;
        }
        else{
            wherecanmove++;
        }
    }
    const bool check = (whitecovered.find({bk.first,bk.second}) != whitecovered.end());
    if (wherecanmove == 0 && !check){
        cout << "STALEMATE\n";
    }
    else if (wherecanmove == 0 && check){
        cout << "CHECKMATE\n";
    }
    else{
        cout << wherecanmove << "\n";
    }
}

