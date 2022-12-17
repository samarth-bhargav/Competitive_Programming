#include <bits/stdc++.h>
using namespace std;

int main(){
    vector<int> buckets(64, 0);
    int x = 100;
    for (int a = 0; a < x; a++){
        for (int b = 0; b < x; b++){
            for (int c = 0; c < x; c++){
                for (int d = 0; d < x; d++){
                    buckets[(a + 2*b + 4*c + 8*d) % 64]++;
                }
            }
        }
        cout << "hi\n";
    }
    for (int i = 0; i < 64; i++){
        cout << buckets[i] << " ";
    }
    cout << "\n";
}