#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

map<int, vector<int>> mp = {{0, {1,2,3}},
                            {1, {1,2}},
                            {2, {0,2}},
                            {3, {0,1}},
                            {4, {2}},
                            {5, {0}}};

const int mxN = 1e5;
ll dp[3][mxN][6];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    int ar[3][n];
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < n; j++){
            cin >> ar[i][j];
        }
    }
    dp[0][0][0] = ar[0][0];
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < n; j++){
            for (int m = 0; m < 6; m++){

            }
        }
    }
}

