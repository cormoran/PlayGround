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


struct xor_shift_128_engine {
    using result_type = uint32_t;
    static constexpr result_type min() { return numeric_limits<result_type>::min(); }
    static constexpr result_type max() { return numeric_limits<result_type>::max(); }
    result_type x = 123456789, y = 362436069, z = 521288629, w;
    xor_shift_128_engine(result_type w = random_device()()) : w(w) { rep(i, 100) (*this)(); }
    result_type operator()() {
		result_type t = x ^ (x << 11); x = y; y = z; z = w;
		return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
    };
};

xor_shift_128_engine engine;

struct Timer {
    using C=chrono::high_resolution_clock;
    C::time_point start;
    Timer() : start(C::now()) {}
    int elapsed() { return chrono::duration_cast<chrono::milliseconds>(C::now() - start).count(); }
    bool over(int ms) { return elapsed() > ms; }
};

struct Grid {
    int n;
    int g[20][20];
    Grid(int n) : n(n) {}
    vector<tuple<int, int, int>> history;

    void rotate(int sy, int sx, int l) {
        double cy = sy + (l - 1) / 2.0;
        double cx = sx + (l - 1) / 2.0;

        Grid g2 = *this;
        repeat(y, sy, sy + l) {
            repeat(x, sx, sx + l) {
                double dy = (y - cy);
                double dx = (x - cx);
                int ny = dx + cy + 1e-8;
                int nx = -dy + cx + 1e-8;
                g2.g[ny][nx] = g[y][x];
            }
        }
        swap(g, g2.g);
        history.emplace_back(sy, sx, l);
    }
    int calc_point() const {
        int point = 0;
        rep(y, n) {
            rep(x, n) {
                point += y < n / 2 and x < n / 2 and g[y][x] == 0;
                point += y < n / 2 and x >= n / 2 and g[y][x] == 1;
                point += y >= n / 2 and x < n / 2 and g[y][x] == 2;
                point += y >= n / 2 and x >= n / 2 and g[y][x] == 3;
            }
        }
        return point;
    }
    void print() {
        rep(i, n) {
            rep(j, n) cerr << g[i][j] << " ";
            cerr << endl;
        }
        cerr << endl;
    }
    bool operator <(const Grid &r) const {
        return calc_point() < r.calc_point();
    }
};

vector<tuple<int, int, int>> beam_search(Grid init, int N, int M, int max_time) {
    cerr << "start search" << endl;
    vector<priority_queue<Grid>> que(M);
    Grid best = init;
    Timer t;
    while(not t.over(max_time)) {
        que[0].push(init);
        rep(m, M) {
            if(t.over(max_time)) break;
            if(que[m].empty()) break;
            Grid now = que[m].top(); que[m].pop();
            rep(i, 20) {
                Grid now2= now;
                uniform_int_distribution<> uniform(0, N - 2);
                int a = uniform(engine);
                int b = uniform(engine);

                uniform_int_distribution<> uniform2(2, min(N - a, N - b));
                int l = uniform2(engine);
                now2.rotate(a, b, l);
                if(best.calc_point() < now2.calc_point()) {
                    best = now2;
                    // cerr << "update m = " << m << endl;
                }
                if(m < M - 1) que[m + 1].push(now2);
            }
            if(m < M - 1 and que[m + 1].size() > 100) {
                priority_queue<Grid> que2;
                rep(i, 100) que2.push(que[m + 1].top()); que[m + 1].pop();
                swap(que[m + 1], que2);
            }
        }
    }
    cerr << "OK " << best.calc_point() << endl;
    return best.history;
};

int main() {
    int N, M; cin >> N >> M;
    Grid G(N);
    rep(i, N) rep(j, N) cin >> G.g[i][j];

    auto history = beam_search(G, N, M, 1850);

    for(auto t : history) {
        cout << get<0>(t) << " " << get<1>(t) << " " << get<2>(t) << endl;
    }

    return 0;
}
