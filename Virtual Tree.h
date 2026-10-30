#include <bits/stdc++.h>
using namespace std;

const int MAX = 2e5;

int in[MAX];
int lca(int a, int b){ return 1;}
int anc(int a, int b){return 1;}

vector<pair<int,int>> virtual_tree(vector<int> v) {
    sort(v.begin(), v.end(), [&](int a, int b) {
        return in[a] < in[b];
    });

    int k = v.size();

    for(int i = 1; i < k; i++)
        v.push_back(lca(v[i-1], v[i]));

    sort(v.begin(), v.end(), [&](int a, int b) {
        return in[a] < in[b];
    });

    v.erase(unique(v.begin(), v.end()), v.end());

    vector<pair<int,int>> edges;
    vector<int> st;

    for(int x : v) {
        while(!st.empty() && !anc(st.back(), x))
            st.pop_back();

        if(!st.empty())
            edges.push_back({st.back(), x});

        st.push_back(x);
    }

    return edges;
}