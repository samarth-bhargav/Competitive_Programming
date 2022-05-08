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
        string s;
        cin >> s;
        for (int i = 0; i < s.size(); i++){
            if (i%2 == 0){
                //alice
                if (s[i] == 'a'){
                    s[i] = 'b';
                }
                else{
                    s[i] = 'a';
                }
            }
            else{
                if (s[i] == 'z'){
                    s[i] = 'y';
                }
                else{
                    s[i] = 'z';
                }
            }
        }
        cout << s << "\n";
    }
}

