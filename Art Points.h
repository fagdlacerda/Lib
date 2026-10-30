#include <bits/stdc++.h>
using namespace std;

const int MAX = 2e5;

vector<vector<int>> g(MAX);
vector<int> in(MAX, -1);
vector<bool> art(MAX);
int t = 0;

int dfs(int f, int p){
    int lo = in[f] = t++;
    int a=0;
    for(int i:g[f]){
        if(i==p) continue;
        if(in[i]==-1){
            a++;
            int tmp = dfs(i, f);
            if(tmp >= in[f] && p!=-1) art[f] = 1;
            lo = min(lo, tmp);
        }
        else{
            lo = min(lo, in[i]);
        }
    }

    if(p==-1 && a>1){
        art[f] = 1;
    }
    return lo;
};