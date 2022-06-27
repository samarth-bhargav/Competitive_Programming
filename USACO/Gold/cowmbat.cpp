#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e5;
int n, m, k; string s;
int pref[mxN+1][26], dp[mxN][26];

int range_to_letter(int a, int b, int l){
    if (a > b){
        swap(a,b);
    }
    return pref[b+1][l] - pref[a][l];
}

int optimal_letter(int a, int b){
    int letter = 0, ans = range_to_letter(a,b,0);
    for (int l = 1; l < n; l++){
        int temp = range_to_letter(a, b, l);
        if (range_to_letter(a, b, l) < ans){
            letter = l;
            ans = temp;
        }
    }
    return letter;
}

int main(){
    ifstream cin("cowmbat.in");
    ofstream cout("cowmbat.out");
    cin >> n >> m >> k >> s;
    int dist[m][m];
    vector<int> a(n);
    for (int i = 0; i < n; i++){
        a[i] = s[i] - 'a';
    }
    for (int i = 0; i < m; i++){
        for (int j = 0; j < m; j++){
            cin >> dist[i][j];
        }
    }
    //floyd-warshall
    for (int v2 = 0; v2 < m; v2++){
        for (int v1 = 0; v1 < m; v1++){
            for (int v3 = 0; v3 < m; v3++){
                dist[v1][v3] = min(dist[v1][v3], dist[v1][v2] + dist[v2][v3]);
            }
        }
    }
    for (int i = 0; i < m; i++){
        for (int j = 0; j < m; j++){
            cerr << dist[i][j] << " ";
        }
        cerr << endl;
    }
    memset(pref, 0, sizeof(pref));
    for (int l = 0; l < 26; l++){
        for (int i = 1; i <= n; i++){
            pref[i][l] = pref[i-1][l] + dist[a[i-1]][l];
        }
    }
    //tests
//    cerr << "(0,1) to 'b': " << range_to_letter(0, 1, 1) << "\n"; //change (0,1) to 'b'
//    cerr << "(2,4) to 'c': " << range_to_letter(2, 4, 2) << "\n"; //change (2,4) to 'c'
//    cerr << "(2,4) optimal letter: " << optimal_letter(2,4) << "\n";
    //end of tests
    memset(dp, 0x3f, sizeof(dp));
    for (int l = 0; l < 26; l++){
        dp[k-1][l] = range_to_letter(0, k-1, l);
    }
    for (int i = k; i < n; i++){
        for (int l = 0; l < m; l++){
            dp[i][l] = min(dp[i][l], dp[i-1][l] + dist[a[i]][l]);
            if (i-k >= k-1){
                for (int l1 = 0; l1 < m; l1++){
                    dp[i][l] = min(dp[i][l], dp[i-k][l1] + range_to_letter(i-k+1, i, l));
                }
            }
        }
    }
    int ans = 1e9;
    for (int l = 0; l < 26; l++){
        ans = min(ans, dp[n-1][l]);
    }
    cout << ans << "\n";
}