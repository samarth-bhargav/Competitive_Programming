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
        int n,d;
        cin >> n >> d;
        map <int,int> mp;
        int init = 0;
        for (int i = 1; i < 100; i++){
            init = (init+d)%10;
            if (mp.find(init) != mp.end()){
                break;
            }
            mp[init] = d*i;
        }
        for (auto & i : mp){
            cerr << i.first << " " << i.second << "\n";
        }
        for (int i = 0; i < n; i++){
            string s;
            cin >> s;
            if (mp.find(CharToInt(s[s.size()-1])) == mp.end()){
                cout << "NO\n";
            }
            else if (StringtoInt(s) < mp[CharToInt(s[s.size()-1])]){
                cout << "NO\n";
            }
            else{
                cout << "YES\n";
            }
        }
    }
}

