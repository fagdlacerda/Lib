#include <bits/stdc++.h>
using namespace std;

//Dijkstra
struct dk{
    vector<vector<pair<long long, int>>> g;
    vector<long long> d;
    vector<int> pai;
    int n;
    bool ok;

    dk(int N){
        g.resize(N), n = N, d.resize(N, 1e18);
        ok = 0, pai.resize(n, -1);
    }

    void add(int a, int b, long long w){
        g[a].push_back({w, b});
        g[b].push_back({w, a});
    }

    void build(int ini){
        if(ok) return;
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
        d[ini] = 0;
        pai[0] = 0;
        pq.emplace(0, ini);
        while(pq.size()){
            auto [p, f] = pq.top(); pq.pop();
            if(d[f]<p) continue;
            for(auto [w, i]:g[f]){
                if(d[i]>d[f]+w){
                    d[i] = d[f]+w;
                    pq.emplace(d[i], i);
                    pai[i] = f;
                }
            }
        }
        ok = 1;
    }

    void init(int ini){
        build(ini);
    }

    stack<int> path(int ini, int fim){
        build(ini);
        stack<int> s;
        if(d[fim]==1e18) return s;
        int i = fim;
        while(i != ini){
            s.push(i);
            i = pai[i];
        }
        s.push(ini);
        return s;
    }
};