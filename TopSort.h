#include <bits/stdc++.h>
using namespace std;

const int MAX = 2e5;

vector<vector<int>> g(MAX);
vector<int> grau(MAX);

void read(int m){
    for(int i=0; i<m; i++){
        int a, b; cin>>a>>b; --a, --b;
        g[a].push_back(b);
        grau[b]++;
    }

}

vector<int> top(int n){
    vector<int> ord;
    queue<int> q;
    for(int i=0; i<MAX; i++) if(!grau[i]) q.push(i);
    
    while(q.size()){
        int f = q.front(); q.pop();
        ord.push_back(f);
        for(int i:g[f]){
            grau[i]--;
            if(!grau[i]) {
                q.push(i);
            }
        }
    }
    if(ord.size() != n) return {};
    return ord;
}