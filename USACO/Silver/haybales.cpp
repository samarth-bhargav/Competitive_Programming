/*
ID: samarth10
LANG: C++11
TASK: 
*/

#include <bits/stdc++.h>
using namespace std;


void setIO(string name) {
	ios_base::sync_with_stdio(0); cin.tie(0);
	freopen((name+".in").c_str(),"r",stdin);
	freopen((name+".out").c_str(),"w",stdout);
}


int main() {
    //setIO("haybales");
    vector <int> haybales;
    int n,q;
    cin >> n >> q;
    for (int i = 0; i < n; i++){
        int j;
        cin >> j;
        haybales.push_back(j);
    }
    sort(haybales.begin(), haybales.end());
    for (int i = 0; i < q; i++){
        int a,b;
        cin >> a >> b;
        int it = 0;
        if (!binary_search(haybales.begin(), haybales.end(), a)){
            it = upper_bound(haybales.begin(), haybales.end(), a) - haybales.begin();
        }
        else{
            it = lower_bound(haybales.begin(), haybales.end(), a) - haybales.begin();
        }
        int it1 = 0;
        if (!binary_search(haybales.begin(), haybales.end(), b)){
            it1 = lower_bound(haybales.begin(), haybales.end(), b) - haybales.begin() - 1;
        }
        else{
            it1 = lower_bound(haybales.begin(), haybales.end(), b) - haybales.begin();
        }
        cout << it1 - it + 1 << "\n";
    }
}

/*
//Second approach using Prefix Sums
//wait nvm it dont work
#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin >> t;
    int ar[100005];
    for (int i = 0)
    for (int i = 0; i < t; i++){

    }
}
*/