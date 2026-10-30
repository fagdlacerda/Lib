#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int MAX = 1e5+1;

int sz[MAX], par[MAX], pos[MAX], seg[MAX*4], lazy[MAX*4], h[MAX];
vector<int> g[MAX];
 
int dfs(int f, int p){
    sz[f] = 1;
    int big = 0;
    for(int &i:g[f]){
        if(i==p) continue;
        par[i] = f;
        sz[f] += dfs(i, f);
        if(sz[i] > big){
            big = sz[i];
            swap(i, g[f][0]);
        }
    }
    return sz[f];
}
 
void build_hld(int f, int p, int head, int &t){
    pos[f] = t++;
    h[f] = head;
    bool heavy = 1;
    for(int i: g[f]){
        if(i==p) continue;
        if(heavy){
            heavy = 0;
            build_hld(i, f, head, t);
        }
        else{
            build_hld(i, f, i, t);
        }
    }
}
 
void build_seg(){
    for(int i=0; i<4*MAX; i++){
        lazy[i] = seg[i] = 0;
    }
}
 
void prop(int p, int l, int r){
    if(!lazy[p]) return;
    seg[p] += (lazy[p] * (r-l+1));
    if(l!=r){
        lazy[2*p] += lazy[p];
        lazy[2*p+1] += lazy[p];
    }
    lazy[p] = 0;
}
 
int seg_update(int p, int l, int r, int i, int j, int v){
    prop(p, l, r);
    if(l>j || r<i) return seg[p];
    if(l>=i && r<=j){
        lazy[p] += v;
        prop(p, l, r);
        return seg[p];
    }
    int m = (l+r)>>1;
    return seg[p] = seg_update(2*p, l, m, i, j, v) +
                    seg_update(2*p+1, m+1, r, i, j, v);
}
 
int seg_query(int p, int l, int r, int i, int j){
    prop(p, l, r);
    if(l>j || r<i) return 0;
    if(l>=i && r<=j) return seg[p];
    int m = (l+r)>>1;
    return seg_query(2*p, l, m, i, j) + seg_query(2*p+1, m+1, r, i, j);
}
 
void update(int a, int b, int n, int v){
    while(h[a] != h[b]){
        if(pos[a] < pos[b]) swap(a, b);
        seg_update(1, 0, n-1, pos[h[a]], pos[a], v);
        a = par[h[a]];
    }
    if(pos[a] < pos[b]) swap(a, b);
    if(a != b) seg_update(1, 0, n-1, pos[b]+1, pos[a], v);
}
 
int query(int a, int b, int n){
    int ans = 0;
    while(h[a] != h[b]){
        if(pos[a] < pos[b]) swap(a, b);
        ans += seg_query(1, 0, n-1, pos[h[a]], pos[a]);
        a = par[h[a]];
    }
    if(pos[a] < pos[b]) swap(a, b);
    if(a != b) ans += seg_query(1, 0, n-1, pos[b]+1, pos[a]);
    return ans;
}
 
void build(int n){
    dfs(0, -1);
    int t = 0;
    build_hld(0, -1, 0, t);
    build_seg();
}