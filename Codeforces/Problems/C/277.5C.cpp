/*
ID: samarth10
LANG: C++11
TASK: 
*/
#include <bits/stdc++.h>

using namespace std;


void setIO(string name) {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen((name + ".in").c_str(), "r", stdin);
    freopen((name + ".out").c_str(), "w", stdout);
}
int CharToInt (char c){
    return c-48;
}
// O(1) Time Complexity
char IntToChar (int c){
    return c + '0';
}
// O(1) Time Complexity

//For Int To String, Float to String, etc. use std::to_string
long long StringtoLL (string s){
    return stoll(s);
}
double StringtoDouble (string s){
    return stod(s);
}
int StringtoInt (string s){
    return stoi(s);
}
string least (int sum, int length){
    int digit;
    string s;
    for (int i = 9; i >= 1; i--){
        if ((sum - i) > 9 * (length-1)){
            s += IntToChar(i+1);
            sum-=i+1;
            break;
        }
        if (i == 1){
            s += IntToChar(1);
            sum-=1;
        }
    }
    length-=1;
    int charleft = length;
    for (int i = 0; i < length; i++){
        for (int k = 9; k >= 0; k--){
            if ((sum - k) > 9 * (charleft-1)){ //sum-k divided by 9 represents how many 9s you can fit in
                s += IntToChar(k+1);
                sum-=k+1;
                charleft-=1;
                break;
            }
            if (k == 0){
                s += IntToChar(0);
                sum -= 0;
                charleft -= 1;
            }
        }
    }
    return s;
}
string greatest (int sum, int length){
    int digit;
    string s;
    for (int i = 1; i < 10; i++){
        if (sum-i < 0){
            digit = i-1;
            sum-=i-1;
            break;
        }
        if (i == 9){
            digit = 9;
            sum-=9;
        }
    }
    s += IntToChar(digit);
    for (int i = 0; i < length-1; i++){
        for (int k = 1; k < 10; k++){
            if (sum-k < 0){
                digit = k-1;
                sum-=k-1;
                break;
            }
            if (k == 9){
                digit = 9;
                sum-=9;
            }
        }
        s += IntToChar(digit);
    }
    return s;
}
int main() {
    //setIO();
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int length,sum;
    cin >> length >> sum;
    if (sum == 0 && length != 1){
        cout << -1 << " " << -1 << "\n";
    }
    else if (sum == 0 && length == 1){
        cout << 0 << " " << 0 << "\n";
    }
    else if(sum == 1 && length == 1){
        cout << 1 << " " << 1 << "\n";
    }
    else if (sum == 1 && length != 1){
        cout << 1;
        for (int i = 0; i < length-1; i++){
            cout << 0;
        }
        cout << " ";
        cout << 1;
        for (int i = 0; i < length-1; i++){
            cout << 0;
        }
        cout << "\n";
    }
    else if (length * 9 < sum){
        cout << -1 << " " << -1 << "\n";
    }
    else{
        string less = least(sum,length);
        string great = greatest(sum,length);
        cout << less << " " << great << "\n";
    }
}

