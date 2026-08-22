#include <bits/stdc++.h>
using namespace std;

vector<int> get_pref(string const& s) {
    int n = s.size();
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i-1];
        while (j > 0 && s[i] != s[j]) j = pi[j-1];
        if (s[i] == s[j]) j++;
        pi[i] = j;
    }
    return pi;
}

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
 
vector<int> get_z(string s) {
	int n = s.size();
	vector<int> z(n, 0);
 
	int l = 0, r = 0;
	for (int i = 1; i < n; i++) {
		if (i <= r) z[i] = min(r - i + 1, z[i - l]);
		while (i + z[i] < n and s[z[i]] == s[i + z[i]]) z[i]++;
		if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
	}
 
	return z;
}