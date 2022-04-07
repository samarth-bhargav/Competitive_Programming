#include <bits/stdc++.h>
using namespace std;

const int mxN = 2e5;
const int mxB = 18;

char segTree[mxN][mxB];

char other(char fc, char sc){
    char set;
    if (fc == 'C'){
        if (sc == 'O'){
            set = 'W';
        }
        else{
            set = 'O';
        }
    }
    else{
        if (sc == 'C'){
            if (fc == 'O'){
                set = 'W';
            }
            else{
                set = 'O';
            }
        }
        else{
            set = 'C';
        }
    }
    return set;
}
char combine(char fc, char sc){
    if (fc == sc){
        return ' ';
    }
    else if (fc == ' ' || sc == ' '){
        return (fc == ' ' ? sc : fc);
    }
    return other(fc, sc);
}
void bld(string s){
    for (int i = 0; i < s.length(); i++){
        segTree[i][0] = s[i];
    }
    for (int j = 1; j < mxB; j++){
        for (int i = 0; (i + (1 << j)) < mxN; i += (1 << j)){
            char fc = segTree[i][j-1];
            char sc = segTree[i + (1 << (j-1))][j-1];
            segTree[i][j] = combine(fc, sc);
        }
    }
}
char qry(int lb, int rb){
    if (rb - lb <= 4){
        char res = segTree[lb][0];
        for (int i = lb + 1; i <= rb; i++){
            res = combine(res, segTree[i][0]);
        }
        return res;
    }
    int range = rb - lb;
    int val = 1 << int(log2(range));
    int value_in_between = (lb / val) * val;
    if (value_in_between < lb){
        value_in_between += val;
    }
    char curr;
    curr = qry(lb, value_in_between - 1);
    curr = combine(curr, segTree[value_in_between][int(log2(range)) - 1]);
    curr = combine(curr, qry(value_in_between + val/2, rb));
    return curr;
}
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string s;
    cin >> s;

    bld(s);

    int n; cin >> n;
    for (int i = 0; i < n; i++){
        int a,b;
        cin >> a >> b; a--; b--;
        if (a == b){
            cout << (s[a] == 'C' ? "Y" : "N");
        }
        else if (s[a] == 'C'){
            cout << (qry(a+1, b) == ' ' ? "Y" : "N");
        }
        else{
            if (s[a] == 'O'){
                cout << (combine('W', qry(a+1, b)) == ' ' ? "Y" : "N");
            }
            else{
                cout << (combine('O', qry(a+1, b)) == ' ' ? "Y" : "N");
            }
        }
    }
    cout << "\n";
}

