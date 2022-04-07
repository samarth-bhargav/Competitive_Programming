/*
Author: treewave
orz
*/
#include <bits/stdc++.h>

using namespace std;
const int mxN = 1e5;
const int MOD = 1e9+7;
int CharToInt (char c){
    return c-48;
}
// O(1) Time Complexity
char IntToChar (int c){
    return c + '0';
}
// O(1) Time Complexity

//For Int To String, Float to String, etc. use std::to_string
long long StringtoLL (string s){
    return stoll(s);
}
double StringtoDouble (string s){
    return stod(s);
}
int StringtoInt (string s){
    return stoi(s);
}
int main() {
    //setIO();
    string s;
    cin >> s;
    int arr[mxN+5]; //stores the modulo of number with *index position* 1s;
    arr[1] = 1;
    for (int i = 2; i < mxN+1; i++){
        arr[i] = ((arr[i-1]*10+1)%MOD+MOD)%MOD;
    }
    long long ans = 0;
    int dp[mxN+5];
    dp[1] = 1;
    for (int i = 2; i < mxN+1; i++){
        dp[i] = ((dp[i-1]*10+arr[i-1])%MOD+MOD)%MOD;
    }
    for (int i = 0; i < s.size(); i++){
        ans += ((dp[s.size()-i]*CharToInt(s[i]))%MOD+MOD)%MOD;
    }
    cout << ans << "\n";
}

