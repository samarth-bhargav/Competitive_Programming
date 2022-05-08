/*
ID: samarth10
LANG: C++11
TASK: 
*/
#include <bits/stdc++.h>

using namespace std;

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
    int t;
    cin >> t;
    while (t--){
        string n; int sum;
        cin >> n >> sum;
        bool alg = false;
        int totsum = 0;
        for (char i : n){
            totsum += CharToInt(i);
        }
        if (totsum < sum){
            cout << "0" << "\n";
            continue;
        }
        else{
            int reachsum = totsum - sum;
            int currtotsum = 0;
            int currlength = 0;
            string currnum;
            for (int i = n.size()-1; i >= 0; i++){
                currnum.insert(n.begin(),n[i]);
                currtotsum += CharToInt(n[i]);
                currlength++;
                if (currtotsum < reachsum){
                    continue;
                }
                else{
                    int ansnum;
                    int anssum = 0; // ans you are trying to develop
                    bool alg = false;
                    for (int k = 0; k < currlength; k++){
                        if (CharToInt(currnum[k])+anssum > reachsum){
                            break;
                        }
                        else{

                        }
                    }
                }
            }
        }
    }
}

