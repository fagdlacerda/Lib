#include <bits/stdc++.h>
using namespace std;

const int MAX = 2e5;
const int MAXM = 2e5;

vector<bool> bridge(MAXM);
vector<vector<pair<int, int>>> g(MAX);
vector<int> in(MAX, -1), low(MAX);
int t = 0;

int dfsTree(int f, int id){
    low[f] = in[f] = t++;

    for(auto [i, c]:g[f]){
        if(c==id) continue;
        if(in[i] == -1){
            low[f] = min(low[f], dfsTree(i, c));
            if(low[i] == in[i]){
                bridge[c] = 1;
            }
        }
        else{
            low[f] = min(low[f], in[i]);
        }
    }

    return low[f];
}