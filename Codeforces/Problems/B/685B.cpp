/*
Author: treewave
orz
*/
#include <bits/stdc++.h>

using namespace std;

int main() {
    //setIO();
    int t;
    cin >> t;
    while (t--){
        int n,q;
        cin >> n >> q;
        string s;
        cin >> s;
        int firstzero = -1e9, firstone = -1e9, lastzero = -1e9,lastone = -1e9;
        for (int i = 0; i < n; i++){
            if (s[i] == '0'){
                if (firstzero == -1e9){
                    firstzero = i;
                }
                lastzero = i;
            }
            else{
                if (firstone == -1e9){
                    firstone = i;
                }
                lastone = i;
            }
        }
        while (q--){
            int a,b;
            cin >> a >> b;
            a--; b--;
            char one = s[a];
            char two = s[b];
            if (s[a] == '0'){
                if (a > firstzero){
                    cout << "YES" << "\n";
                    continue;
                }
                else{
                    if (s[b] == '0'){
                        if (b < lastzero){
                            cout << "YES" << "\n";
                            continue;
                        }
                        else{
                            cout << "NO" << "\n";
                            continue;
                        }
                    }
                    else{
                        if (b < lastone){
                            cout << "YES" << "\n";
                            continue;
                        }
                        else{
                            cout << "NO" << "\n";
                            continue;
                        }
                    }
                }
            }
            else{
                if (a > firstone){
                    cout << "YES" << "\n";
                    continue;
                }
                else{
                    if (s[b] == '0'){
                        if (b < lastzero){
                            cout << "YES" << "\n";
                            continue;
                        }
                        else{
                            cout << "NO" << "\n";
                            continue;
                        }
                    }
                    else{
                        if (b < lastone){
                            cout << "YES" << "\n";
                            continue;
                        }
                        else{
                            cout << "NO" << "\n";
                            continue;
                        }
                    }
                }
            }
        }
    }
}

