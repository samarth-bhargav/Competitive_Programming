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

int main(){
    int ar[100005];
    string s;
    cin >> s;
    for (int i = 0; i < s.length(); i++){
        ar[i] = CharToInt(s[i]);
    }
    int n = s.length();
    int curr = 0;
    long long ans = 1;
    for (int i = 1; i < n; i++){
        if (ar[i]+ar[i-1] == 9){
            curr++;
            continue;
        }
        else{
            if (curr%2 == 1){
                curr = 0;
            }
            else{
                if (curr == 0){
                    continue;
                }
                ans *= (curr/2)+1;
                curr = 0;
            }
        }
    }
    if (curr%2 == 1){
        curr = 0;
    }
    else{
        if (curr != 0){
            ans *= (curr/2)+1;
        }
        curr = 0;
    }
    cout << ans << "\n";
}