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
    while (t--) {
        int a, b;
        string s;
        cin >> a >> b >> s;
        if (a + b != s.size()) {
            cout << -1 << "\n";
            continue;
        }
        if (s.size() % 2 == 0 && a % 2 == 1) {
            cout << -1 << "\n";
            continue;
        }
        int n = s.size();
        int change = 0;
        bool bad = false;
        for (int i = 0; i < s.size() / 2; i++) {
            if (s[i] == '0') {
                if (s[n - i - 1] == '?') {
                    s[n - i - 1] = '0';
                } else if (s[n - i - 1] == '1') {
                    cout << -1 << "\n";
                    bad = true;
                    break;
                }
            } else if (s[i] == '1') {
                if (s[n - i - 1] == '?') {
                    s[n - i - 1] = '1';
                } else if (s[n - i - 1] == '0') {
                    cout << -1 << "\n";
                    bad = true;
                    break;
                }
            } else {
                if (s[n - i - 1] == '?') {
                    change++;
                } else if (s[n - i - 1] == '0') {
                    s[i] = '0';
                } else {
                    s[i] = '1';
                }
            }
        }
        if (bad) {
            continue;
        }
        int curra = count(s.begin(), s.end(), '0');
        int currb = count(s.begin(), s.end(), '1');
        if (curra > a || currb > b) {
            cout << -1 << "\n";
            continue;
        }
        int adiff = a - curra;
        int bdiff = b - currb;
        if (adiff % 2 == 1 && bdiff % 2 == 1) {
            cout << -1 << "\n";
            continue;
        }
        if (n%2 == 1){
            if (a%2 == 1){
                if (s[n/2] == '?'){
                    s[n/2] = '0';
                    adiff--;
                }
                else if (s[n/2] == '1'){
                    cout << -1 << "\n";
                    continue;
                }
            }
            else if (b%2 == 1){
                if (s[n/2] == '?'){
                    s[n/2] = '1';
                    bdiff--;
                }
                else if (s[n/2] == '0'){
                    cout << -1 << "\n";
                    continue;
                }
            }
        }
        for (int i = 0; i < n/2; i++){
            if (s[i] == '?'){
                if (adiff > 0){
                    adiff -= 2;
                    s[i] = '0';
                    s[n-i-1] = '0';
                }
                else if (bdiff > 0){
                    bdiff -= 2;
                    s[i] = '1';
                    s[n-i-1] = '1';
                }
            }
        }
        if (adiff == 0 && bdiff == 0){
            cout << s << "\n";
        }
        else{
            assert(false);
        }
    }
}

