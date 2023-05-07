#include <iostream>
#include <string>
#include <cassert>
#include <fstream>
using namespace std;

int main(){
    ifstream cin("flag.txt");
    string flag; cin >> flag;
    string aux_flag = "";
    string abet;
    for (int i = 97; i < 123; i++){
        abet += char(i);
    }
    assert(flag.size() <= abet.size());
    for (int i = 0; i < flag.size(); i++){
        aux_flag += char(int(flag[i])) ^ abet[i];
    }
    cout << aux_flag << "\n";
}
