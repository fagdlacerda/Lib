#include <bits/stdc++.h>
using namespace std;

const int MAX = 2e5;
const int MAXM = 2e5;

vector<bool> bridge(MAXM);
vector<vector<pair<int, int>>> g(MAX);
vector<int> in(MAX, -1), low(MAX);
int t = 0, cnt = 1;

int dfsTree(int f, int id){
    low[f] = in[f] = t++;

    for(auto [i, w]:g[f]){
        if(w==id) continue;
        if(in[i] == -1){
            low[f] = min(low[f], dfsTree(i, w));
            if(low[i] == in[i]){
                bridge[w] = 1;
                cnt++;
            }
        }
        else{
            low[f] = min(low[f], in[i]);
        }
    }

    return low[f];
}

vector<int> comp;
vector<vector<int>> v;

void cond(int n){
    comp.resize(n);
    v.resize(n);
    vector<int> vis(n);
    int nxt = 1;
 
    function<void(int, int, int)> dfs = [&](int f, int p, int c){
        vis[f] = 1;
        comp[f] = c;
        for(auto [i, w]:g[f]){
            if(i==p) continue;
            if(!vis[i]){
                if(!bridge[w]){
                    dfs(i, f, c);
                }
                else{
                    v[c].push_back(nxt);
                    v[nxt].push_back(c);
                    dfs(i, f, nxt++);
                }
            }
        }
    };
}