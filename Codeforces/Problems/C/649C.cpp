/*
Author: treewave
orz
*/
#include <bits/stdc++.h>

using namespace std;

const int mxN = 1e6;

int main() {
    //setIO();
    int t;
    cin >> t;
    int a[t];
    for (int i = 0; i < t; i++){
        cin >> a[i];
        if (a[i] > i+1){
            cout << -1 << "\n";
            break;
        }
    }
    int b[t];
    memset(b,0,sizeof(b));
    map <int,int>mp;
    int cnt = a[0] == 0;
    map <int,int> bad;
    for (int i = 1; i < t; i++){
        if (a[i] != a[i-1]){
            b[i] = a[i-1];
            mp.insert(make_pair(i,b[i]));
            bad.insert(make_pair(b[i],1));
        }
        bad.insert(make_pair(a[i],1));
    }
    while (true){
        if (bad.find(cnt) == bad.end()){
            b[0] = cnt;
            break;
        }
        else{
            cnt++;
        }
    }
    for (int i = 1; i < t; i++){
        if (mp.find(i) == mp.end()){
            if (bad.find(cnt+1) == bad.end()){
                cnt++;
                b[i] = cnt;
            }
            else{
                cnt++;
                while (true){
                    if (bad.find(cnt) == bad.end()){
                        b[i] = cnt;
                        break;
                    }
                    else{
                        cnt++;
                    }
                }
            }
        }
    }
    for (int i : b){
        cout << i << " ";
    }
    cout << "\n";
}

