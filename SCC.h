#include <bits/stdc++.h>
using namespace std;

const int MAX = 2e5;

vector<vector<int>> g(MAX);
vector<int> scc(MAX), in(MAX, -1), low(MAX);
vector<bool> stk(MAX);
stack<int> st;
int tmp = 0, t = 0;

void calc(int f){
    low[f] = in[f] = tmp++;
    st.push(f);
    stk[f] = 1;
    for(int i:g[f]){
        if(in[i] == -1){
            calc(i);
            low[f] = min(low[f], low[i]);
        }
        else{
            if(stk[i]) low[f] = min(low[f], in[i]);
        }
    }
    if(low[f] == in[f]){
        while(st.top() != f){
            int i = st.top(); st.pop();
            stk[i]=0;
            scc[i] = t;
        }
        st.pop();
        stk[f] = 0;
        scc[f] = t++;
    }
};

vector<vector<int>> cond(int n){

    for(int i=0; i<n; i++) if(in[i] == -1) calc(i);

    vector<vector<int>> dag(t);
    
    for(int f=0; f<n; f++){
        for(int i:g[f]){
            int a = scc[f], b = scc[i];
            if(a!=b){
                dag[a].push_back(b);
            }
        }
    }
    return dag;
}