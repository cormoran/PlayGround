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

ll calc_score(const vector<vector<int>> &g, const vector<vector<int>> &l, const vector<vector<int>> &r, const vector<int> &B, vector<vector<double>> &score, bool use_score) {
    rep(i, score.size()) rep(j, score[i].size()) score[i][j] = 0;
    ll res = 0;
    rep(i, g.size()) {
        rep(j, g[i].size()) {
            int sum = 0;
            repeat(k, j, g[i].size()) {
                sum += g[i][k];
                if(find(all(B), sum) != end(B)) {
                    res += sum;
                    if(use_score) repeat(l, j, k+1) score[i][l] += double(sum) / (k - j);
                }
            }
            sum = 0;
            repeat(k, i, g.size()) {
                sum += g[k][j];
                if(find(all(B), sum) != end(B)) {
                    res += sum;
                    if(use_score) repeat(l, i, k+1) score[l][j] += double(sum) / (k - i);
                }
            }
        }
    }
    return res;
}

random_device rd;

class Solver {
  public:
    bool solve() {
        clock_t start = clock();

        int N; cin >> N;
        vector<int> B(3); cin >> B;
        vector<vector<int>> L(N, vector<int>(N)); cin >> L;
        vector<vector<int>> R(N, vector<int>(N)); cin >> R;

        vector<vector<int>> g(N, vector<int>(N));

        mt19937 mt(rd());

        ll best_point = -1;
        vector<vector<int>> best_g;
        vector<vector<double>> score(N, vector<double>(N));

        // rep(t, 10000) {
        rep(t, 1000) {
            rep(i, N) rep(j, N) g[i][j] = uniform_int_distribution<int>(L[i][j], R[i][j])(mt);
            if(set_max(best_point, calc_score(g, L, R, B, score, false))) best_g = g;
        }
        cerr << "random init: " << calc_score(g, L, R, B, score, true) << endl;
        //
        struct Region {
            int sy, sx, h, w;
        };

        auto calc_sum_score = [&] (const Region &r) {
                      double sum = 0;
                      repeat(y, r.sy, r.sy + r.h) repeat(x, r.sx, r.sx + r.w) sum += score[y][x];
                      return sum;
                  };
        ll t_best_point = best_point;
        auto t_best_g = best_g;
        rep(t, 100000) {
            clock_t epoch_start = clock();
            for(int rect : {6, 5, 4, 3, 2, 1}) {
                rep(ttt, 20) {
                double worst_score = 1e9;
                Region worst_region = Region{0, 0, 1, 1};
                rep(tt, 10) {
                    int sy = uniform_int_distribution<int>(0, N - rect)(mt);
                    int sx = uniform_int_distribution<int>(0, N - rect)(mt);
                    Region r = {sy, sx,  rect,  rect};
                    double tmp = calc_sum_score(r);
                    if(set_min(worst_score, tmp)) worst_region = r;
                }
                rep(tt, 10) {
                    g = t_best_g;
                    repeat(y, worst_region.sy, worst_region.sy + worst_region.h) repeat(x, worst_region.sx, worst_region.sx + worst_region.w) g[y][x] = uniform_int_distribution<int>(L[y][x], R[y][x])(mt);
                    ll tmp = calc_score(g, L, R, B, score, true);
                    // if(uniform_real_distribution<>(0, 1)(mt) > 1.9) {
                    //     t_best_point = tmp;
                    //     t_best_g = g;
                    // }
                    // else
                        if(set_max(t_best_point, tmp)) t_best_g = g;
                    if(set_max(best_point, tmp)) best_g = g;
                }
                }
                // debug(best_point);
            }
            clock_t end = clock();
            double left = (end - start) + (end - epoch_start) * 2;
            // debug(left / CLOCKS_PER_SEC);
            if(left / CLOCKS_PER_SEC >= 2.8) break;
        }
        // rep(i, N) {
        //     rep(j, N) cerr << mask[i][j] << (j + 1 == N ? "\n" : "");
        // }

        debug(best_point);
        //
        rep(i, N) {
            rep(j, N) cout << best_g[i][j] << (j + 1 == N ? "\n" : " ");
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
