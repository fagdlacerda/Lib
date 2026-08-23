#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int MAX = 1e5+1;

int sz[MAX], par[MAX], h[MAX], pos[MAX];
int seg[4*MAX], v[MAX];
vector<int> g[MAX];

void dfs(int f, int p){
    sz[f] = 1;
    int maior = 0;
    for(int &i:g[f]){
        if(i==p) continue;
        dfs(i, f);
        par[i] = f;
        sz[f] += sz[i];
        if(sz[i] > maior){
            swap(i, g[f][0]);
            maior = sz[i];
        }
    }
}

void build_hld(int f, int p, int head, int& t){
    pos[f] = t++;
    h[f] = head;
    bool fir = 1;
    for(int i:g[f]){
        if(i==p) continue;
        if(fir){
            fir = 0;
            build_hld(i, f, head, t);
        }
        else{
            build_hld(i, f, i, t);
        }
    }
};

int build_seg(int p, int l, int r){
    if(l==r) return seg[p] = v[l];
    int mid = (l+r)>>1;
    return seg[p] = build_seg(2*p, l, mid) + build_seg(2*p+1, mid+1, r);
}

int seg_update(int p, int l, int r, int idx, int val){
    if(l>idx || r<idx) return seg[p];
    if(r==l) return seg[p] = val;
    int mid = (l+r)>>1;
    return seg[p] = seg_update(2*p, l, mid, idx, val) +
                    seg_update(2*p+1, mid+1, r, idx, val);
}

int seg_query(int p, int l, int r, int a, int b){
    if(l>b || r<a) return 0;
    if(l>=a && r<=b) return seg[p];
    int mid = (l+r)>>1;
    return seg_query(2*p, l, mid, a, b) + 
           seg_query(2*p+1, mid+1, r, a, b);
}

int query(int a, int b, int n){
    if(pos[b] > pos[a]) swap(a, b);

    if(pos[h[a]] == pos[h[b]]){
        return seg_query(1, 0, n-1, pos[a], pos[b]);
    }

    int ans = seg_query(1, 0, n-1, pos[h[a]], pos[a]);
    ans += query(par[h[a]], b, n);
    return ans;
}

void update(int a, int val, int n){
    seg_update(1, 0, n-1, pos[a], val);
}

void build(int root, int n){
    dfs(0, -1);
    int t = 0;
    build_hld(root, -1, root, t);
    build_seg(1, 0, n-1);
}