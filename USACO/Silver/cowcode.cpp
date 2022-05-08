/*
Author: treewave
orz
*/
#include <bits/stdc++.h>

using namespace std;

long long calcbase(long long n, long long lim){
    for (int i = 0; i < 60; i++){
        if (n*pow(2,i) < lim && n*pow(2,i+1) >= lim){
            return n*pow(2,i);
        }
    }
}

int main() {
    //setIO();
    ifstream cin("cowcode.in");
    ofstream cout("cowcode.out");
    string s; long long x;
    cin >> s >> x;
    long long n = s.length();
    while (x > n){
        long long base = calcbase(n,x);
        //base+1 maps to base
        if (x == base+1){
            x = base;
            continue;
        }
        //base+2 maps to 1 . . . etc
        x = (x-(base+2)+1);
    }
    cout << s[x-1] << "\n";
}

