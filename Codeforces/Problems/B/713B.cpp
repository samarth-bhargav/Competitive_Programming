/*
Dont raise your voice,improve your argument
--Desmond Tutu
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
*/
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--){
        int n;
        cin >> n;
        char ar[n][n];
        vector<array<int,2>>corners;
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                cin >> ar[i][j];
                if (ar[i][j] == '*'){
                    corners.push_back({i,j});
                }
            }
        }
        sort(corners.begin(),corners.end());
        if (corners[0][0] == corners[1][0]){
            //rows are the same
            if (corners[0][0] != 0){
                pair<int,int>first = {corners[0][0]-1,corners[0][1]};
                pair<int,int>second = {corners[1][0]-1,corners[1][1]};
                ar[first.first][first.second] = '*';
                ar[second.first][second.second] = '*';
            }
            else{
                pair<int,int>first = {corners[0][0]+1,corners[0][1]};
                pair<int,int>second = {corners[1][0]+1,corners[1][1]};
                ar[first.first][first.second] = '*';
                ar[second.first][second.second] = '*';
            }
        }
        else if (corners[0][1] == corners[1][1]){
            if (corners[0][1] != 0){
                pair<int,int>first = {corners[0][0],corners[0][1]-1};
                pair<int,int>second = {corners[1][0],corners[1][1]-1};
                ar[first.first][first.second] = '*';
                ar[second.first][second.second] = '*';
            }
            else{
                pair<int,int>first = {corners[0][0],corners[0][1]+1};
                pair<int,int>second = {corners[1][0],corners[1][1]+1};
                ar[first.first][first.second] = '*';
                ar[second.first][second.second] = '*';
            }
        }
        else{
            pair<int,int>first = {corners[1][0],corners[0][1]};
            pair<int,int>second = {corners[0][0],corners[1][1]};
            ar[first.first][first.second] = '*';
            ar[second.first][second.second] = '*';
        }
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                cout << ar[i][j];
            }
            cout << "\n";
        }
    }
}

