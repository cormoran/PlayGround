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
vector<int> arange(int n) { vector<int> a(n); rep(i, n) a[i] = i; return a; }
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

template<class State>
State SimulatedAnnealing(State initial_state,
                         int time_ms,
                         function<State(State)> next,
                         function<double(State)> score) {
    State state = initial_state, best_state = initial_state;

    Timer timer;
    auto uniform = uniform_real_distribution<>(0, 1);

    auto temperature = [&] () {
        return max(1.0 - (double)timer.elapsed() / time_ms, 1e-9);
    };
    auto probability = [] (double delta, double temp) {
        constexpr double alpha = 1; // larger value encourages more transition
        return exp(alpha * delta / temp); // [0, 1) if delta < 0 and temp > 0
    };
    int itr = 0, num_update = 0, num_best = 0;
    for(itr = 0; not timer.over(time_ms); itr++) {
        State nxt = next(state);
        double delta = score(nxt) - score(state);
        if(probability(delta, temperature()) > uniform(engine)) {
            // cerr << "update! " << score(state) << " -> " << score(nxt) << endl;
            num_update++;
            state = nxt;
            if(score(state) > score(best_state)) {
                best_state = state;
                num_best++;
            }
        }
    }
    cerr << "[SA]" << endl
         << "* elapsed time: " << timer.elapsed() << " ms" << endl
         << "* number of iteration: " << itr << endl
         << "* last score: " << score(best_state) << endl
         << "* num update: " << num_update << endl
         << "* num best update: " << num_best << endl;
    return best_state;
}


struct State {
    vector<int> indices;
    int sum2 = 0;
    double sum = 0;
    int operator[](int i) { return indices[(i + indices.size()) % indices.size()]; }
    double var() {
        return (double)sum2 / indices.size() - sum * sum / indices.size() / indices.size();
    }
};

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    vector<int> X(N), Y(N); rep(i, N) cin >> X[i] >> Y[i];

    auto calc_dist2 = [&] (int i, int j) {
        return pow<int>(X[i] - X[j], 2) + pow<int>(Y[i] - Y[j], 2);
    };

    vector<vector<int>> dist2(N, vector<int>(N));
    vector<vector<double>> dist(N, vector<double>(N));
    rep(i, N) rep(j, N) {
        dist2[i][j] = calc_dist2(i, j);
        dist[i][j] = sqrt(dist2[i][j]);
    }

    State init; init.indices = arange(N);
    rep(i, N) {
        init.sum2 += calc_dist2(init[i], init[i + 1]);
        init.sum += sqrt(calc_dist2(init[i], init[i + 1]));
    }

    function<double(State)> score = [&] (State state) {
        return 1e6 / (1 + state.var());
    };


    // 2-opt:
    //   reverse closed range(a, b)
    //   ... [a, ..., b] ... --> ... [b, ..., a] ...
    function<State(State)> two_opt = [&] (State state) {
        auto uniform = uniform_int_distribution<>(0, N - 1);
        int a = uniform(engine), b = uniform(engine);
        if(a > b) swap(a, b);

        auto update = [&] (int x, int sign) {
            // remove or connect [x] and [x + 1]
            state.sum2 += sign * dist2[state[x]][state[x + 1]];
            state.sum += sign * dist[state[x]][state[x + 1]];
        };

        update(a - 1, -1);
        update(b, -1);

        reverse(begin(state.indices) + a, begin(state.indices) + b + 1);

        update(a - 1, +1);
        update(b, +1);

        return state;
    };

    // or-opt:
    //   insert a after b
    //   ... a, [..., b] ... --> ... [b, ...] a, ...
    function<State(State)> or_opt = [&] (State state) {
        auto uniform = uniform_int_distribution<>(0, N - 1);
        int a = uniform(engine), b = uniform(engine);
        if(a == b) return state;
        if(a > b) swap(a, b);

        auto update = [&] (int x, int sign) {
            // remove or connect [x] and [x + 1]
            state.sum2 += sign * dist2[state[x]][state[x + 1]];
            state.sum += sign * dist[state[x]][state[x + 1]];
        };

        update(a - 1, -1);
        update(a, -1);
        update(b, -1);

        { // insert a after b
            int tmp = state.indices[a];
            repeat(i, a, b) state.indices[i] = state.indices[i + 1];
            state.indices[b] = tmp;
        }

        update(a - 1, +1);
        update(b - 1, +1);
        update(b, +1);

        return state;
    };

    auto res = SimulatedAnnealing(init, 1950, two_opt, score);

    rep(i, N) cout << res[i] << endl;
    // cerr << score(res) << endl;

    return 0;
}
