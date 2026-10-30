#include <bits/stdc++.h>
using namespace std;

struct aho{
    struct node{
        int cnt, fail, exit, term, id;
        bool vis;
        int nxt[26];
        node(){
            id = -1;
            cnt = term = vis = fail = exit = 0;
            memset(nxt, -1, sizeof(nxt));
        }
    };

    vector<node> g;

    aho(){g.emplace_back();}

    int add(string &s, int n){
        int i=0;
        for(auto ch: s){
            int c = ch-'A';
            if(g[i].nxt[c] == -1){
                int f = g.size();
                g[i].nxt[c] = f;
                g.emplace_back();
            }
            i = g[i].nxt[c];
        }
        g[i].id = n;
        g[i].term++;
        return i;
    }

    void build(){
        queue<int> q;
        for(int c=0; c<26; c++){
            int f = g[0].nxt[c];
            if(f!=-1){
                q.push(f);
                g[f].fail = 0;
            }
            else g[0].nxt[c] = 0;
        }
        while(q.size()){
            int p = q.front(); q.pop();
            for(int c=0; c<26; c++){
                int f = g[p].nxt[c];
                if(f!=-1){
                    g[f].fail = g[g[p].fail].nxt[c];
                    q.push(f);
                    g[f].exit = g[g[f].fail].term 
                                ? g[f].fail 
                                : g[g[f].fail].exit;
                }
                else{
                    g[p].nxt[c] = g[g[p].fail].nxt[c];
                }
            }
        }
    }

    void query(string &s){
        int f = 0;
        int k = s.size();
        for(int i=0; i<k; i++){
            int c = s[i] - 'A';
            f = g[f].nxt[c];
            if(g[f].term){

            }

            for(int u = g[f].exit; u; u = g[u].exit){

            }
        }
    }
};