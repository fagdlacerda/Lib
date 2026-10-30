#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> dfa(string const& s){
    int n = s.size();
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i-1];
        while (j > 0 && s[i] != s[j]) j = pi[j-1];
        if (s[i] == s[j]) j++;
        pi[i] = j;
    }
    
    vector<vector<int>> nxt(n+1, vector<int>(26));
    for(int i=0; i<=n; i++){

        for(int c=0; c<26; c++){
            if(i<n && (s[i]-'a') == c) {
                nxt[i][c] = i+1; // A letra bateu certo
            }
            else if(i>0){
                nxt[i][c] = nxt[pi[i-1]][c];
            }
            else nxt[i][c] = 0;
        }
    }
    return nxt;
}