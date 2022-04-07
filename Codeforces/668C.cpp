/*
ID: samarth10
LANG: C++11
TASK: 
*/
#include <bits/stdc++.h>

using namespace std;
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
    int t;
    cin >> t;
    while (t--){
        int n, k;
        cin >> n >> k;
        string s;
        cin >> s;
        int ar[n+1]; ar[0] = 0; int questions[n+1]; questions[0] = 0;
        for (int i = 0; i < s.length(); i++){
            if (s[i] == '?'){
                ar[i+1] = ar[i];
                questions[i+1] = questions[i] + 1;
            }
            else{
                ar[i+1] = ar[i] + CharToInt(s[i]);
                questions[i+1] = questions[i];
            }
        }
        int currquestions = 0;
        int used[n+1];
        bool flag = true;
        memset(used, 0, sizeof(used));
        for (int i = k; i <= n; i++){
            currquestions = questions[i]-questions[i-1];
            if (ar[i] - ar[i-k] - k/2 + currquestions < 0){
                flag = false;
                break;
            }
            if (ar[i] - ar[i-k] - k/2 > 0){
                flag = false;
                break;
            }
            used[i] = used[i-1] + abs(ar[i] - ar[i-k] - k/2);
        }
        cout << (flag ? "YES\n" : "NO\n");
    }
}

