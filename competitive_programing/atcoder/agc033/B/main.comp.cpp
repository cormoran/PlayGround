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
        int H, W, N; cin >> H >> W >> N;
        int Sr, Sc; cin >> Sr >> Sc;
        Sr--; Sc--;
        string S, T; cin >> S >> T;

        string SD = "LRUD";
        string TD = "RLDU";
        bool exitable = false;

        rep(c, 4) {
            const char sd = SD[c], td = TD[c];

            vector<int> max_movable(N + 1);
            int movable = 0;
            for(int i = N - 1; i >=0 ;i--) {
                movable += S[i] == td;
                max_movable[i] = max(max_movable[i + 1], movable);
                movable -= T[i] == sd;
            }

            int need;
            if(c == 0) {
                need = Sc + 1;
            } else if (c == 1) {
                need = W - Sc;
            } else if (c == 2) {
                need = Sr + 1;
            } else if (c == 3) {
                need = H - Sr;
            } else assert(0);
            int sup = c < 2 ? W : H;
            rep(i, N) {
                if(S[i] == sd) need--;
                exitable |= need == 0;
                if(T[i] == td and need + max_movable[i] < sup) need++;
            }
        }
        cout << (not exitable ? "YES" : "NO") << endl;

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
