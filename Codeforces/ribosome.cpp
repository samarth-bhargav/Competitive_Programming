#include <bits/stdc++.h>
using namespace std;


vector <pair<double,double>> coords;
int n, l;

bool ok(double x){
    vector <pair <double,double>> intervals;
    for (int i = 0; i < coords.size(); i++){
        double a = coords[i].first;
        double b = coords[i].second;
        if (b*b > x*x){
            continue;
        }
        double intervala = a - sqrt(x*x - b*b);
        double intervalb = a + sqrt(x*x - b*b);
        intervals.emplace_back(min(intervala,intervalb),max(intervala,intervalb));
    }
    sort(intervals.begin(), intervals.end());
    if (intervals.empty()){
        return false;
    }
    if (intervals[0].first > 0){
        return false;
    }
    double maxsecond = intervals[0].second;
    bool alg = false;
    while (true){
        alg = false;
        for (int i = 1; i < intervals.size(); i++){
            if (intervals[i].first <= intervals[i-1].second){
                pair <double,double> p = make_pair(intervals[i-1].first,max(intervals[i].second,intervals[i-1].second));
                intervals.erase(intervals.begin()+i-1, intervals.begin()+i+1);
                auto pos = intervals.begin() + i - 1;
                intervals.insert(pos,p);
                alg = true;
            }
        }
        if (!alg){
            break;
        }
    }
    for (auto & i : intervals){
        if (i.first <= 0 && i.second >= l){
            return true;
        }
    }
    return false;
}

int main(){
    cin >> n >> l;
    for (int i = 0; i < n; i++){
        int a,b;
        cin >> a >> b;
        coords.emplace_back(a,b);
    }
    double lo = 0;
    double hi = 1e18;
    for (int i = 0; i < 100; i++){
        double mid = (lo+hi)/2;
        if (ok(mid)){
            hi = mid;
        }
        else{
            lo = mid;
        }
    }
    cout << fixed;
    cout << setprecision(7) << lo << "\n";
}