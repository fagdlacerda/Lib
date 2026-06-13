#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll mod = 1e9+7;
const int MAX = 1e6+1;

ll fpow(ll b, ll p, ll m = mod){ // exponenciação rápida
    ll ans = 1;
    while(p){
        if(p&1){
            ans = ans * b % m;
        }
        b = b * b % m;
        p /= 2;
    }
    return ans;
}

ll inv(ll a, ll m = mod){ // inverso modular de a
    return fpow(a, m-2, m);
}

vector<ll> inver(int n, ll m = mod){ // inverso modular de 1 até n
    vector<ll> inv(n+1);
    if(n>0) inv[1] = 1;
    for(int i=2; i<=n; i++){
        inv[i] = m - (m / i) * inv[m % i] % m;
    }
    return inv;
}

vector<ll> fat(int n, int m = mod){// fatorial de 0 a n mod m
    vector<ll> fact(n+1);
    fact[0] = 1;
    for(int i=1; i<=n; i++){
        fact[i] = fact[i-1] * i % m;
    }
    return fact;
}

vector<ll> invfact(int n, ll m = mod){ //inverso fatorial de 0 até n
    vector<ll> fact = fat(n, m), invfat(n+1), inverso = inver(n, m);

    invfat[0] = 1;
    for(int i=1; i<=n; i++){
        invfat[i] = invfat[i-1] * inverso[i] % m;
    }
    return invfat;
}