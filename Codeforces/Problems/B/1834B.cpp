#include <bits/stdc++.h>

using namespace std;

bool validSuf(string &l, string &r, string suf){
    for (int i = 0; i < l.size() - suf.size(); i++){
        if (l[i] != r[i]){
            return true;
        }
    }
    bool f1 = true, f2 = true;
    for (int i = l.size() - suf.size(); i < l.size(); i++){
        if (f1){
            if (l[i] > suf[i - l.size() + suf.size()]){
                return false;
            }
        }
        else{
            if (l[i] < suf[i - l.size() + suf.size()]){
                return true;
            }
        }
        if (f2){
            if (r[i] < suf[i - l.size() + suf.size()]){
                return false;
            }
        }
        else{
            if (r[i] > suf[i - l.size() + suf.size()]){
                return true;
            }
        }
        if (l[i] != r[i] && suf[i - l.size() + suf.size()] != r[i] && suf[i - l.size() + suf.size()] != l[i]){
            return true;
        }
        else{
            if (l[i] != r[i]){
                if (suf[i - l.size() + suf.size()] == r[i]){
                    f2 = false;
                }
                else if (suf[i - l.size() + suf.size()] == l[i]){
                    f1 = false;
                }
            }
        }
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--){
        string a, b; cin >> a >> b;
        a = "0" + a; b = "0" + b;
        if (a.size() > b.size()){
            string s;
            while (b.size() + s.size() < a.size()){
                s += '0';
            }
            b = s + b;
        }
        else if (b.size() > a.size()){
            string s;
            while (a.size() + s.size() < b.size()){
                s += '0';
            }
            a = s + a;
        }
        string less = "", more = "";
        int ans = 0;
        for (int i = a.size()-2; i >= 0; i--){
            char lo = '0', hi = '9';
            while (!validSuf(a, b, hi + less)){
                hi--;
            }
            while (!validSuf(a, b, lo + more)){
                lo++;
            }
            less = hi + less;
            more = lo + more;
            ans += abs(hi - lo);
        }
        cout << ans << "\n";
    }
}