#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m, k;
    cin >> n >> m >> k;
    vector<string> days = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    vector<vector<int>> schedules(n);
    for (int i = 0; i < n; i++){
        int sz; cin >> sz;
        for (int j = 0; j < sz; j++){
            string day; cin >> day;
            schedules[i].push_back((find(days.begin(), days.end(), day) - days.begin() + 1) % 7);
        }
    }
    set<int> holidays;
    for (int i = 0; i < m; i++){
        int h; cin >> h;
        holidays.insert(h);
    }
    vector<vector<int>> projects(k);
    for (int i = 0; i < k; i++){
        int sz; cin >> sz;
        for (int j = 0; j < sz; j++){
            int p; cin >> p; p--;
            projects[i].push_back(p);
        }
    }
    map<int, set<int>> active; // day of week -> people actively working on project that work that day
    map<int, set<int>> curr_projects; // person -> current projects they're working on
    int finished = 0;
    vector<int> ans(k);
    vector<int> proj_ptr(k, 0);
    //initialize everything
    for (int proj = 0; proj < k; proj++){
        int person = projects[proj][0];
        for (int day : schedules[person]){
            active[day].insert(person);
        }
        curr_projects[person].insert(proj);
    }
    for (int d = 1; finished < k; d++){
        if (holidays.count(d)){
            continue;
        }
        int dow = d % 7;
        vector<int> proj_to_upd;
        for (int person : active[dow]){
            //they finish their project part
            int project_working = *curr_projects[person].begin();
            curr_projects[person].erase(project_working);
            proj_to_upd.push_back(project_working);
        }
        for (int proj : proj_to_upd){
            proj_ptr[proj]++;
            if (proj_ptr[proj] == projects[proj].size()){
                ans[proj] = d;
                finished++;
                continue;
            }
            int person = projects[proj][proj_ptr[proj]];
            for (int day : schedules[person]){
                active[day].insert(person);
            }
            curr_projects[person].insert(proj);
        }
        set<int> to_erase;
        for (int person : active[dow]){
            if (curr_projects[person].empty()){
                to_erase.insert(person);
            }
        }
        for (int person : to_erase){
            for (int day : schedules[person]){
                active[day].erase(person);
            }
        }
    }
    for (int i = 0; i < k; i++){
        cout << ans[i] << " ";
    }
    cout << "\n";
}
