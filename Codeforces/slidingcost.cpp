#include <bits/stdc++.h>
using namespace std;

int main(){
    string s = "9";
    for (int i = 0; i < 100000; i++){
        int x = s.size();
        for (int j = 0; j < x; j++){
            if (s[j] != '9'){
                s[j]++;
            }
            else{
                s.erase(s.begin()+j);
                s.insert(s.begin()+j,'0');
                s.insert(s.begin()+j,'1');
                j++;
            }
        }
        cout << s.size() << " " << i+1 << "\n";
    }
}