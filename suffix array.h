#include <bits/stdc++.h>
using namespace std;

struct suff_arr{
    string s;
    int n;
    vector<int> p, c, lcp;

    suff_arr(string S){
        s = S, n = S.size(), p.resize(n), c.resize(n), lcp.resize(n);
    }

    void count_sort(vector<int> &p, vector<int> &c){
        vector<int> cnt(n);
        for(int i: c){
            cnt[i]++;
        }
        vector<int> np(n);
        vector<int> pos(n);
        pos[0] = 0;
        for(int i=1; i<n; i++){
            pos[i] = pos[i-1] + cnt[i-1];
        }
        for(auto x: p){
            int i = c[x];
            np[pos[i]] = x;
            pos[i]++;
        }
        p = np;
    }
    
    vector<int> build(){
        iota(p.begin(), p.end(), 0);
        sort(p.begin(), p.end(), [&](int a, int b){
            return s[a] < s[b];
        });
        c[p[0]] = 0;
        for(int i=1; i<n; i++){
            if(s[p[i]] == s[p[i-1]]){
                c[p[i]] = c[p[i-1]];
            }
            else{
                c[p[i]] = c[p[i-1]] + 1;
            }
        }
        
        for(int k=0; (1<<k) < n; k++){
            for(int i=0; i<n; i++){
                int j = (1<<k);
                p[i] = (p[i] - j + n) % n;
            }
            count_sort(p, c);
            vector<int> nc(n);
            nc[p[0]] = 0;

            for(int i=1; i<n; i++){
                int j = (p[i] + (1<<k))%n;
                int l = (p[i-1] + (1<<k))%n;
                pair<int, int> prev = {c[p[i-1]], c[l]};
                pair<int, int> now = {c[p[i]], c[j]};
                if(prev == now){
                    nc[p[i]] = nc[p[i-1]];
                }
                else{
                    nc[p[i]] = nc[p[i-1]] + 1;
                }
            }
            c = nc;
        }
        return p;
    }
    vector<int> calc_lcp(){
        int k = 0;
        for(int i=0; i<n-1; i++){
            int pi = c[i];
            int j = p[pi-1];
            while(i+k < n && j+k < n && s[i+k] == s[j+k]) k++;
            lcp[pi] = k;
            k = max(k-1, 0);
        }
        return lcp;
    }
};