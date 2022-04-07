#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
*/
using pii = pair<int,int>;

int answer = 0;
map<pii,int>nextto;
map<pii,int>occured;

void dfs(int a, int b){
    vector<pii>havetocheck;
    occured[{a,b}] = 1;
    havetocheck.emplace_back(a,b);
    nextto[{a,b}] = 0;

    auto trav = [&](int a, int b, int c, int d) -> void{
        if(occured.find({c,d}) != occured.end()){
            nextto[{a,b}]++;
            nextto[{c,d}]++;
            havetocheck.emplace_back(c,d);
        }
    };
    //you are adding a new coordinate, so just
    //check if the adjacent ones are filled
    trav(a,b,a-1,b);
    trav(a,b,a+1,b);
    trav(a,b,a,b-1);
    trav(a,b,a,b+1);
    for (auto & i : havetocheck){
        //cerr << i.first << " " << i.second << "\n";
        if (nextto[{i.first,i.second}] == 3){
            answer++;
            pii x;
            if (!(occured.find({i.first-1,i.second}) != occured.end())) {
                x = make_pair(i.first-1,i.second);
            }
            else if (!(occured.find({i.first+1,i.second}) != occured.end())){
                x = make_pair(i.first+1,i.second);
            }
            else if (!(occured.find({i.first,i.second-1}) != occured.end())){
                x = make_pair(i.first,i.second-1);
            }
            else if (!(occured.find({i.first,i.second+1}) != occured.end())){
                x = make_pair(i.first,i.second+1);
            }
            //cerr << x.first << " " << x.second << "\n";
            dfs(x.first,x.second);
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++){
        int x,y;
        cin >> x >> y;
        if (occured.find({x,y}) != occured.end()){
            //if ar[a][b] is already filled
            answer--;
        }
        else{
            dfs(x,y);
        }
        cout << answer << "\n";
    }
}



