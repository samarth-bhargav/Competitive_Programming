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
    int n,m,k;
    cin >> n >> m >> k;
    string s;
    for (int i = 0; i < n-1; i++){
        s += 'U';
    }
    for (int i = 0; i < m-1; i++){
        s += 'L';
    }
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m-1; j++){
            if (i%2 == 0){
                s += 'R';
            }
            else{
                s += 'L';
            }
        }
        s += 'D';
    }
    assert(s.size() <= 2*m*n);
    cout << s.size() << "\n" << s << "\n";
}

