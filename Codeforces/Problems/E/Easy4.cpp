//babybeluga
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
*/
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    string t; double s,d;
    cin >> t >> s >> d;
    int first,second;
    if (t.size() == 4){
        first = stoi(t.substr(0,1));
        second = stoi(t.substr(2,4));
    }
    else{
        first = stoi(t.substr(0,2));
        second = stoi(t.substr(3,5));
    }
    double hourstotake = d/s;
    double hours = floor(d/s);
    double minutes = (hourstotake - floor(d/s))*60;
    int firstans,secondans;
    if (second + minutes >= 60){
        hours++;
        secondans = second+minutes-60;
    }
    else{
        secondans = second+minutes;
    }
    firstans = ((int)hours+first)%24;
    if (firstans < 10){
        if (secondans < 10){
            cout << 0 << firstans << ':' << 0 << secondans << "\n";
        }
        else{
            cout << 0 << firstans << ':' << secondans << "\n";
        }
    }
    else {
        if (secondans < 10){
            cout << firstans << ':' << 0 << secondans << "\n";
        }
        else{
            cout << firstans << ':' << secondans << "\n";
        }
    }
}

