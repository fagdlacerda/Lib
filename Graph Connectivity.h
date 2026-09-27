#include <bits/stdc++.h>
using namespace std;

//SCC
struct SCC{
    vector<vector<int>> g;
    stack<int> s;
    vector<int> vis, comp, id;
    int n, timer;

    SCC(int N){
        g.resize(N), vis.resize(N), comp.resize(N), id.resize(N), n = N, timer = 0;
    }

    void add(int a, int b){
        g[a].push_back(b);
    }

    int dfs(int f){
        int lo = id[f] = timer++;
        s.push(f);
        vis[f] = 2;

        for(int &i:g[f]){
            if(!vis[i]) lo = min(lo, dfs(i));
            else if(vis[i]==2) lo = min(lo, id[i]);
        }

        if(lo == id[f]) while(1){ //raiz
            int i = s.top(); s.pop();
            vis[i] = 1, comp[i] = f;
            if(i==f) break;
        }
        return lo;
    }

    void build(){
        for(int i=0; i<n; i++){
            if(!vis[i]) dfs(i);
        }
    }

    vector<vector<int>> cond(){ //lembra de chamar o build antes
        vector<vector<int>> v(n);
        for(int i=0; i<n; i++){
            for(auto j:g[i]){
                if(comp[i] != comp[j]){
                    v[comp[i]].push_back(comp[j]);
                }
            }
        }
        return v;
    }
};

//TopSort
struct topsort{
    vector<vector<int>> g;
    vector<int> vis, ret;
    bool dag;
    int n, pos;

    topsort(int N){
        g.resize(N), vis.resize(N), ret.assign(N, -1), n = N, dag = 1, pos = N-1;
    }

    void add(int a, int b){
        g[a].push_back(b);
    }

    vector<int> build(){
        function<void(int)> dfs = [&](int f){
            vis[f] = 1;
            for(int i:g[f]){
                if(vis[i]==1) dag=0;
                else if(!vis[i]) dfs(i);
            }
            ret[pos--] = f, vis[f] = 2;
        };
        for(int i=0; i<n; i++){
            if(!vis[i]) dfs(i);
        }
        if(!dag) ret.clear();
        return ret;
    }
};

struct dfstree{
    bool bridge;
    vector<vector<int>> g;
    vector<int> in, low;
    int t;

    dfstree(int N){
        g.resize(N), in.resize(N), low.resize(N), t = 0;
    }

    int dfsTree(int f, int p){
        in[f] = low[f] = t++;

        for(int i:g[f]){
            if(i==p) continue;
            if(!in[i]){
                low[f] = min(low[f], dfs(i, f));
            }
            else{
                low[f] = min(low[f], in[i]);
            }
        }

        if(f!=p && low[f] == in[f]){
            bridge = 1;
        }
        return low[f];
    }
};

struct artpt{
    vector<vector<int>> g;
    vector<int> in;
    vector<bool> art;
    int t;

    artpt(int N){
        in.resize(N), g.resize(N), art.resize(N), t=0;
    }

    function<int(int, int)> dfs = [&](int f, int p){
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
}