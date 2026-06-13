#include <bits/stdc++.h>
using namespace std;

int timer = 1, l = 21, n;
vector<int> dist(n), in(n), out(n);
vector<vector<int>> g(n), up(n, vector<int>(l));

void dfs(int f, int p){
    in[f] = timer++;
    dist[f] = dist[p]+1;
    up[f][0] = p;
    for(int i=1; i<l; i++) up[f][i] = up[up[f][i-1]][i-1];
    for(int i:g[f]){
        if(i==p) continue;
        dfs(i, f);
    }
    out[f] = timer++;
}

bool anc(int a, int b){
    return in[a] <= in[b] && out[a] >= out[b];
}

int lca(int a, int b){
    if(anc(a, b)) return a;
    if(anc(b, a)) return b;
    for(int i=l-1; i>=0; i--){
        if(!anc(up[a][i], b)) a = up[a][i];
    }
    return up[a][0];
}

int d(int a, int b){
    return dist[a] + dist[b] - 2*dist[lca(a, b)]; 
}