#include <bits/stdc++.h>
using namespace std;

using pii = pair<int,int>;
using ll = long long;
#define rep(i, j) for(int i=0; i < (int)(j); i++)
#define repeat(i, j, k) for(int i = (j); i < (int)(k); i++)
#define all(v) v.begin(),v.end()
#define debug(x) cerr << #x << " : " << x << endl

template<class T> bool set_min(T &a, const T &b) { return a > b  ? a = b, true : false; }
template<class T> bool set_max(T &a, const T &b) { return a < b  ? a = b, true : false; }
// vector
template<class T> istream& operator >> (istream &is , vector<T> &v) { for(T &a : v) is >> a; return is; }
template<class T> ostream& operator << (ostream &os , const vector<T> &v) { for(const T &t : v) os << "\t" << t; return os << endl; }
// pair
template<class T, class U> ostream& operator << (ostream &os , const pair<T, U> &v) { return os << "<" << v.first << ", " << v.second << ">"; }

const int INF = 1 << 30;
const ll INFL = 1LL << 60;


class Solver {
  public:
    bool solve() {
        constexpr int NT = 10, NX = 20, NY = 20, TT = 3;
        double u[NX+2][100], un[NX+2][100];
        int TY = 5, TX = 5;
        for(int t = 0; t < NT; t+= TT) {
            int nt = (t + TT) > NT ? (NT - t) : TT;
            int ny = NY + nt, nx = NX + nt;
            for(int y = 0; y < ny; y += TY) {
                int t0y = (y + TY) >= NY, t1y = nt;
                for(int x = 0; x < nx; x+= TX) {
                    double **ut = &u, **unt = &un;
                    int t0 = 0, t1 = nt;
                    int t0x = (x + TX) >= NX, t1x = nt;
                    if(t0 < t0y) t0 = t0y; if(t0 < t0x) t0 = t0x;
                    if(t1 > t1y) t1 = t1y; if(t1 > t1x) t0 = t1x;
                    for(int tt = t0; tt < t1; tt++) {
                        double (*uu)[NX+2] = ut, (*uun)[NX+2] = unt;
                        int y0 = y - tt, y1 = y + TY - tt;
                        if(y0 < 0) y0 = 0; if(y1 > NY) y1 = NY;
                        int x0 = x - tt, x1 = x + TX - tt;
                        if(x0 < 0) x0 = 0; if(x1 > NX) x1 = NX;
                        repeat(yy, y0, y1) repeat(xx, x0, x1) {
                            uun[yy][xx] = uu[yy][xx] + dthh * (uu[yy][xx - 1] + uu[yy][xx + 1] + uu[yy - 1][xx] + uu[yy + 1][xx] - 4.0 * uu[yy][xx]);
                        }
                        swap(ut, unt)
                    }
                }
            }
            if(nt & 1) {
                swap(u, un);
            }
        }
        return 0;
    }
};

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    Solver s;
    s.solve();
    return 0;
}
