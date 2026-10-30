#include <bits/stdc++.h>
using namespace std;

const int MAX = 2e5;

int sz[MAX], par[MAX];
vector<int> g[MAX];
vector<bool> vis(MAX);

int calc(int f, int p){
    sz[f] = 1;
    for(int i:g[f]){
        if(i==p || vis[i]) continue;
        sz[f] += calc(i, f);
    }
    return sz[f];
}

int cent(int f, int p, int m){
    for(int i:g[f]){
        if(i==p || vis[i]) continue;
        if(sz[i] > m/2){
            return cent(i, f, m);
        }
    }
    return f;
}

void dec(int f, int p){
    calc(f, -1);
    int c = cent(f, -1, sz[f]);
    par[c] = p;
    vis[c] = 1;

    for(int i:g[c]){
        if(vis[i]) continue;
        dec(i, c);
    }
}