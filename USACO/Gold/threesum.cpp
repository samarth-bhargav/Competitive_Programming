#include <bits/stdc++.h>
using namespace std;

#define int long long

const int mxN = 5000;
const int offset = 1000001;
int qry[mxN][mxN];
int occ[2*offset];

int32_t main(){
    ifstream cin("threesum.in");
    ofstream cout("threesum.out");
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    if (n < 3){
        for (int i = 0; i < q; i++){
            cout << 0 << "\n";
        }
        return 0;
    }
    vector<int> a(n);
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    //iterating over endpoint
    occ[a[0]+offset]++;
    for (int e = 2; e < n; e++){
        if (e%2 == 0){
            //everything gets set to 0
            occ[a[e-1]+offset]++;
            for (int f = 0; f <= e-1; f++){
                occ[a[f]+offset]--;
                if (offset >= abs(a[e]+a[f])){
                    qry[f][e] = occ[offset-a[e]-a[f]];
                }
            }
        }
        else{
            //everything is initially 0
            for (int f = e-1; f >= 0; f--){
                if (offset >= abs(a[e]+a[f])){
                    qry[f][e] = occ[offset-a[e]-a[f]];
                }
                occ[a[f]+offset]++;
            }
        }
    }
    for (int e = 2; e < n; e++){
        for (int f = e-2; f >= 0; f--){
            qry[f][e] = qry[f][e] + qry[f+1][e];
        }
    }
    //qry[f][e] is the number of triples with a
    //set endpoint and begin point >= f
    //now prefix sum the queries themselves
    for (int f = 0; f < n; f++){
        for (int e = f+3; e < n; e++){
            qry[f][e] += qry[f][e-1];
        }
    }

    for (int i = 0; i < q; i++){
        int f, e;
        cin >> f >> e; f--; e--;
        cout << qry[f][e] << "\n";
    }
}