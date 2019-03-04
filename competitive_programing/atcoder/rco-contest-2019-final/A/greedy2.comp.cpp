#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;
using ll  = long long;
#define rep(i, j) for (int i = 0; i < (int)(j); i++)
#define repeat(i, j, k) for (int i = (j); i < (int)(k); i++)
#define all(v) v.begin(), v.end()
#define debug(x) cerr << #x << " : " << x << endl

template <class T>
bool set_min(T &a, const T &b) {
    return a > b ? a = b, true : false;
}
template <class T>
bool set_max(T &a, const T &b) {
    return a < b ? a = b, true : false;
}
// vector
template <class T>
istream &operator>>(istream &is, vector<T> &v) {
    for (T &a : v) is >> a;
    return is;
}
template <class T>
ostream &operator<<(ostream &os, const vector<T> &v) {
    for (const T &t : v) os << "\t" << t;
    return os << endl;
}
// pair
template <class T, class U>
ostream &operator<<(ostream &os, const pair<T, U> &v) {
    return os << "<" << v.first << ", " << v.second << ">";
}

const int INF = 1 << 30;
const ll INFL = 1LL << 60;

struct Deck {
    int top;
    set<int> removed;
    Deck() : top(-1) {}
    void remove() {
        removed.insert(top);
        top = -1;
    }
};

int query(int p) {
    cout << p << endl; cout.flush();
    int x; cin >> x;
    return x;
}

// now -> {a, b}
int calc_cost(int now, int a, int b) {
    return min(abs(now - a), abs(now - b)) + abs(a - b);
}

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

int main() {
    uniform_real_distribution<> uniform(0, 1);
    cin.tie(0);
    ios::sync_with_stdio(false);

    int N, T;
    cin >> N >> T;

    vector<int> top(N, -1);
    int now = 0;
    int point = 0;

    auto move_to = [&] (int nxt) {
        if(now == nxt) return;
        int cost = abs(now - nxt);
        if(T < cost) {
            cout << -1 << endl; cout.flush();
            cerr << "point: " << point << endl;
            exit(0);
        }
        top[nxt] = query(nxt);
        if(top[now] == top[nxt]) {
            point += top[now];
            top[now] = -1;
            top[nxt] = query(nxt);
        }
        T -= cost;
        now = nxt;
    };

    auto move_to2 = [&] (int nxt) {
        int dir = now == nxt ? 0 : now < nxt ? 1 : -1;
        while(T > 0 and now != nxt) {
            move_to(now + dir);
        }
    };

    top[0] = query(0);
    // repeat(i, 1, N) move_to(i);

    while(T > 0) {
        int mypair = -INF;
        rep(i, N) if(i != now and top[i] == top[now]) {
            if(abs(mypair - now) > abs(i - now)) mypair = i;
        }
        double th =  mypair >= 0 ? (top[mypair] > 3 ? 1 : 0.8) : 1;
        if(mypair >= 0 and uniform(engine) < th) {
            // cerr << "pair" << endl;
            move_to(mypair);
        } else {
            map<int, int> tops;
            rep(i, N) if(top[i] >= 0) tops[top[i]]++;
            vector<int> multi;
            for(auto p : tops) if(p.second >= 2) multi.push_back(p.first);
            sort(all(multi));

            if(multi.size() > 0)  {
                vector<int> indices;
                rep(i, N) if(top[i] == multi.back()) indices.push_back(i);

                int min_a= indices[0], min_b = indices[1];
                rep(i, indices.size()) {
                    repeat(j, i + 1, indices.size()) {
                        if(calc_cost(now, indices[i], indices[j]) > calc_cost(now, min_a, min_b)) {
                            min_a = i;
                            min_b = j;
                        }
                    }
                }
                if(abs(now - min_a) > abs(now - min_b)) swap(min_a, min_b);
                int dir = now < min_a ? 1 : -1;
                // cerr << "go a" << endl;
                // move_to2(min_a);
                move_to(now + dir);
                // cerr << "go b" << endl;
                // move_to(min_b);
            } else {
                // cerr << "go ?" << endl;
                int nxt = -INF;
                rep(i, N) if(i != now and top[i] == -1) {
                    if(abs(now - nxt) > abs(now - i)) nxt = i;
                }
                if(nxt < 0) break;
                move_to(nxt);
            }
        }
    }
    cout << -1 << endl;
    cerr << "point : " << point << endl;

    return 0;
}
