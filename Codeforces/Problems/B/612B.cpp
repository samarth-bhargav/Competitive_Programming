#include <bits/stdc++.h>
using namespace std;
string check(string a, string b){
    string result;
    for (int i = 0; i < a.length(); ++i) {
        if(a[i] == b[i])
            result.push_back(a[i]);
        else
        {
            if(a[i] != 'S' && b[i] != 'S')
                result.push_back('S');
            else if(a[i] != 'T' && b[i] != 'T')
                result.push_back('T');
            else
                result.push_back('E');
        }
    }
    return result;
}
int main() {
    //setIO();
    map <string, long long> mp;
    int n,k;
    cin >> n >> k;
    vector <string> cards;
    for (int i = 0; i < n; i++){
        string s;
        cin >> s;
        cards.push_back(s);
        mp[cards[i]]++;
    }
    for (int i = 0; i < )
}

