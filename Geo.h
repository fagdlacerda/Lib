#include <bits/stdc++.h>
using namespace std;

// Retorna o centroide de um polígono. Os vértices devem estar em ordem anti-horária.
pt centroid(const vector<pt>& v) {
    ld area = 0, cx = 0, cy = 0;
    int n = v.size();
    
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n; // O próximo vértice (circular)
        
        // Produto vetorial da aresta (2x a área do triângulo com a origem)
        ld cross = (v[i].x * v[j].y - v[j].x * v[i].y); 
        
        area += cross;
        cx += (v[i].x + v[j].x) * cross;
        cy += (v[i].y + v[j].y) * cross;
    }
    
    area /= 2.0;
    cx /= (6.0 * area);
    cy /= (6.0 * area);
    
    return pt(cx, cy);
}

struct CentroidQueries {
    int n;
    vector<pt> v;
    vector<__int128_t> pref_area, pref_cx, pref_cy;

    // Função 1: Recebe o polígono (0-based) e pré-calcula os prefixos
    CentroidQueries(const vector<pt>& poly) {
        n = poly.size();
        
        // Ajusta tamanho para 2N + 1 para lidar com queries circulares e ser 1-based
        v.resize(2 * n + 1);
        for (int i = 0; i < n; i++) {
            v[i + 1] = poly[i];
            v[i + n + 1] = poly[i]; // Duplica
        }

        pref_area.assign(2 * n + 1, 0);
        pref_cx.assign(2 * n + 1, 0);
        pref_cy.assign(2 * n + 1, 0);

        // Constrói os prefixos começando de i=2 (primeira aresta válida)
        for (int i = 2; i <= 2 * n; i++) {
            long long cross = sarea2(pt(0, 0), v[i-1], v[i]);
            
            pref_area[i] = pref_area[i-1] + (__int128_t)cross;
            pref_cx[i]   = pref_cx[i-1]   + (__int128_t)(v[i-1].x + v[i].x) * cross;
            pref_cy[i]   = pref_cy[i-1]   + (__int128_t)(v[i-1].y + v[i].y) * cross;
        }
    }

    // Função 2: Responde a query das coordenadas do centroide
    // a e b são os índices dos vértices do corte (1-based, de 1 a N)
    pair<long double, long double> query(int a, int b) {
        if (a > b) b += n;

        // Calcula a aresta de fechamento (de b para a)
        long long cross_corte = sarea2(pt(0, 0), v[b], v[a]);
        __int128_t cx_corte = (__int128_t)(v[b].x + v[a].x) * cross_corte;
        __int128_t cy_corte = (__int128_t)(v[b].y + v[a].y) * cross_corte;

        // Soma as bordas com o corte
        __int128_t area_total = (pref_area[b] - pref_area[a]) + cross_corte;
        __int128_t cx_total = (pref_cx[b] - pref_cx[a]) + cx_corte;
        __int128_t cy_total = (pref_cy[b] - pref_cy[a]) + cy_corte;

        // Calcula as coordenadas finais (dividindo por 3 * area porque cross = 2 * area)
        long double ans_x = (long double)cx_total / (long double)(3 * area_total);
        long double ans_y = (long double)cy_total / (long double)(3 * area_total);

        return {ans_x, ans_y};
    }
};
#define ll long long

struct pt{
	ll x, y;
	pt(ll x_ = 0, ll y_ = 0) : x(x_), y(y_) {}

	pt operator - (const pt p) const { return pt(x-p.x, y-p.y);}
};

ll cross(pt a, pt b){
	return a.x*b.y - a.y*b.x;
}

ll dot(pt a, pt b){
	return a.x*b.x + a.y*b.y;
}

bool inseg(pt a, pt b, pt c){ // Ponto c entre a e b
	pt ca = c-a, cb = c-b;
	return cross(ca, cb) == 0 && dot(ca, cb) <= 0;
}

bool interseg(pt a, pt b, pt c, pt d){ //ab intersecta cd
	pt ab = a-b, ac = a-c, ad = a-d;
	pt cd = c-d, ca = c-a, cb = c-b;
	ll d1 = cross(ab, ac), d2 = cross(ab, ad);
	ll d3 = cross(cd, ca), d4 = cross(cd, cb);

	if(((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) && ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0))) return true;

	if(inseg(a, b, c) || inseg(a, b, d) || inseg(c, d, a) || inseg(c, d, b)) return 1;
	
	return 0;
}
