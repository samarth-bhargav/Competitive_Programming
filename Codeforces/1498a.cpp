/*
Dont raise your voice,improve your argument
--Desmond Tutu
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
*/
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
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--){
        string s;
        cin >> s;
        while (true){
            ll sum = 0;
            for (int i = 0; i < s.size(); i++){
                sum += (CharToInt(s[i]));
            }
            ll n = stoll(s);
            if (__gcd(n,sum) > 1){
                cout << n << "\n";
                break;
            }
            n++;
            s = to_string(n);
        }
    }
}

