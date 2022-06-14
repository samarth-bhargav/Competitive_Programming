//code doesn't work due to a malformed idea
//because taking the most optimal rectangle as your first isn't necessarily optimal
//this is because there could be a rectangle that yields the same benefit, but then use less 'useful' squares. unclear.
#include <bits/stdc++.h>
using namespace std;

#define int long long

const int mxN = 201;
int dp[mxN][mxN], a[mxN][mxN], p[mxN][mxN+1];
vector<array<int,4>> coords;

int row1 = 0, row2 = 0, col1 = 0, col2 = 0;

int kadane(vector<int> v){
    int currSum = 0;
    int maxSum = INT_MIN;
    for (int i = 0; i < (int)v.size(); i++) {
        currSum += v[i];
        if (currSum > maxSum) {
            maxSum = currSum;
        }
        if (currSum < 0) {
            currSum = 0;
        }
    }
    return maxSum;
}

int qry(){
    //prefix sum of each row
    for (int r = 0; r < mxN; r++){
        p[r][0] = 0;
        for (int c = 1; c <= mxN; c++){
            p[r][c] = p[r][c-1] + a[r][c-1];
        }
    }
    int ans = -1;

    vector<int> temp;
    for (int c1 = 0; c1 < mxN; c1++){
        for (int c2 = c1; c2 < mxN; c2++){
            for (int r = 0; r < mxN; r++){
                temp.push_back(p[r][c2+1] - p[r][c1]);
            }
            int currSum = 0;
            int maxSum = INT_MIN;
            for (int i = 0; i < (int)temp.size(); i++) {
                currSum += temp[i];
                if (currSum > maxSum) {
                    maxSum = currSum;
                }
                if (currSum < 0) {
                    currSum = 0;
                }
            }
            int tans = maxSum;
            if (tans > ans){
                col1 = c1;
                col2 = c2;
                ans = tans;
            }
            temp.clear();
        }
    }
    int tempSum = 0;
    for (int r1 = 0; r1 < mxN; r1++){
        bool flag = false;
        for (int r2 = r1; r2 < mxN; r2++){
            for (int r = r1; r <= r2; r++){
                tempSum += p[r][col2+1] - p[r][col1];
            }
            if (tempSum == ans && !flag){
                row1 = r1;
                row2 = r2;
                flag = true;
            }
            tempSum = 0;
        }
    }
    return ans;
}

int32_t main(){
    ifstream cin("paintbarn.in");
    ofstream cout("paintbarn.out");
    int n,k;
    cin >> n >> k;
    memset(dp, 0, sizeof(dp));
    for (int i = 0; i < n; i++){
        int ax,ay,bx,by;
        cin >> ax >> ay >> bx >> by;
        dp[ax][ay]++;
        dp[bx][by]++;
        dp[ax][by]--;
        dp[bx][ay]--;
        coords.push_back({ax, ay, bx, by});
    }
    for (int i = 0; i < mxN; i++){
        for (int j = 0; j < mxN; j++){
            if (i > 0){
                dp[i][j] += dp[i-1][j];
            }
            if (j > 0){
                dp[i][j] += dp[i][j-1];
            }
            if (i > 0 && j > 0){
                dp[i][j] -= dp[i-1][j-1];
            }
        }
    }
//    for (int i = 0; i < coords.size(); i++){
//        dp[coords[i][0]][coords[i][3]]++;
//        dp[coords[i][2]][coords[i][1]]++;
//    }
//    for (int i = 0; i < 9; i++){
//        for (int j = 0; j < 9; j++){
//            cerr << dp[i][j] << " ";
//        }
//        cerr << "\n";
//    }
//    cerr << "\n" << "\n";
    for (int i = 0; i < mxN; i++){
        for (int j = 0; j < mxN; j++){
            if (dp[i][j] == k-1){
                a[i][j] = 1;
            }
            else if (dp[i][j] == k){
                a[i][j] = -1;
            }
            else{
                a[i][j] = 0;
            }
        }
    }
//    for (int i = 0; i < 9; i++){
//        for (int j = 0; j < 9; j++){
//            cerr << a[i][j] << " ";
//        }
//        cerr << "\n";
//    }
    int ans = max(qry(), 0LL);
    for (int i = 0; i < mxN; i++){
        for (int j = 0; j < mxN; j++){
            if (a[i][j] == -1){
                ans++;
            }
        }
    }
//    cerr << "row1: " << row1 << "\n";
//    cerr << "row2: " << row2 << "\n";
//    cerr << "col1: " << col1 << "\n";
//    cerr << "col2: " << col2 << "\n";
    if (ans > 0){
        for (int r = row1; r <= row2; r++){
            for (int c = col1; c <= col2; c++){
                a[r][c] = -1e9;
            }
        }
//        for (int i = 0; i < 9; i++){
//            for (int j = 0; j < 9; j++){
//                cerr << a[i][j] << " ";
//            }
//            cerr << "\n";
//        }
//        cerr << "answer: " << ans << "\n";
        ans = ans + max(qry(), 0LL);
//        cerr << "row1: " << row1 << "\n";
//        cerr << "row2: " << row2 << "\n";
//        cerr << "col1: " << col1 << "\n";
//        cerr << "col2: " << col2 << "\n";
        for (int r = row1; r <= row2; r++){
            for (int c = col1; c <= col2; c++){
                a[r][c] = -1e9;
            }
        }
//        for (int i = 0; i < 9; i++){
//            for (int j = 0; j < 9; j++){
//                cerr << a[i][j] << " ";
//            }
//            cerr << "\n";
//        }
    }
    cout << ans << "\n";
}