#include <bits/stdc++.h>
using namespace std;

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, q; cin>>n>>m>>q;
    vector<int> pos(m), fds(m);
    for(int &i:pos) cin>>i, --i;
    for(int &i:fds) cin>>i;
    set<pair<int, int>> pt;

    struct node{
        int r;
        long long v;
        bool has;
    };

    vector<node> lazy(4*n);

    vector<long long> seg(n*4);

    auto prop = [&](int p, int l, int r){
        if(!lazy[p].has) return;
        auto [j, v, has] = lazy[p];
        long long ff = (j-l+1) * v; // dist de l até o cara a direita * valor da esq
        long long ss = (j-r+1) * v; // dist de r até o cara a direita * valor da esq
        long long len = r-l+1; // numero de caras entre l e r
        seg[p] = (ff+ss)*len/2;
        if(l!=r){
            lazy[2*p].has = lazy[2*p+1].has = 1;
            lazy[2*p].r = lazy[2*p+1].r = lazy[p].r;
            lazy[2*p].v = lazy[2*p+1].v = lazy[p].v;
        }
        lazy[p].has = 0;
    }; 

    function<void(int, int, int, int, int, long long)> upd = [&](int p, int l, int r, int i, int j, long long v){
        prop(p, l, r);
        if(l>j || r<i) return;
        if(l>=i && r<=j){
            lazy[p].r = j;
            lazy[p].v = v;
            lazy[p].has = 1;
            prop(p, l, r);
            return;
        }
        int mid = (l+r)>>1;
        upd(2*p, l, mid, i, j, v);
        upd(2*p+1, mid+1, r, i, j, v);
        seg[p] = seg[2*p] + seg[2*p+1];
    };

    function<void(int, int, int, int, long long)> updcaba = [&](int p, int l, int r, int idx, long long v){
        prop(p, l, r);
        if(l>idx || r<idx) return;
        if(l==r){
            seg[p] = 0;
            auto it = pt.lower_bound({l, v});
            --it;
            auto tmp = *it;
            upd(1, 0, n-1, tmp.first+1, l-1, tmp.second);
            it = pt.upper_bound({l, v});
            tmp = *it;
            upd(1, 0, n-1, l+1, tmp.first-1, v);
            return;
        }
        int mid = (l+r)>>1;
        updcaba(2*p, l, mid, idx, v);
        updcaba(2*p+1, mid+1, r, idx, v);
        seg[p] = seg[2*p] + seg[2*p+1];
    };

    function<long long(int, int, int, int, int)> qry = [&](int p, int l, int r, int i, int j){
        prop(p, l, r);
        if(l>j || r<i) return 0LL;
        if(l>=i && r<=j){
            return seg[p];
        }
        int mid = (l+r)>>1;
        return qry(2*p, l, mid, i, j) + qry(2*p+1, mid+1, r, i, j);
    };

    for(int i=0; i<m; i++){
        pt.insert({pos[i], fds[i]});
    }
    for(int i=0; i<m; i++){
        updcaba(1, 0, n-1, pos[i], fds[i]);
    }

    
    while(q--){
        int t; cin>>t;
        if(t==1){
            int idx, val;
            cin>>idx>>val;
            --idx;
            pt.insert({idx, val});
            updcaba(1, 0, n-1, idx, val);
        }
        else{
            int l, r; cin>>l>>r;
            cout<<qry(1, 0, n-1, --l, --r)<<'\n';
        }
    }

    return 0;
}