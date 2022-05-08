#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

typedef tree<int, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update> ost;


int main(){
    ifstream cin("sleepy.in");
    ofstream cout("sleepy.out");
    int n;
    cin >> n;
    vector<int> cows(n);
    for (int i = 0; i < n; i++){
        cin >> cows[i];
    }
    int pos = 0;
    for (int i = 1; i < n; i++){
        if (cows[i] < cows[i-1]){
            pos = i;
        }
    }
    cout << pos << "\n";
    vector<int> fhalf;
    ost shalf;
    for (int i = 0; i < n; i++){
        if (i >= pos){
            shalf.insert(cows[i]);
        }
        else{
            fhalf.push_back(cows[i]);
        }
    }
    for (int i = 0; i < pos; i++){
        shalf.insert(fhalf[i]);
        int index = shalf.order_of_key(fhalf[i]);
        index += pos-i-1;
        cout << index;
        if (i < pos-1){
            cout << " ";
        }
    }
}
