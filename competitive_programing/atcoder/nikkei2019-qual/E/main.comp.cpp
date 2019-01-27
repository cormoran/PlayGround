#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pil = pair<int,ll>;

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

struct Edge {
    int a, b;
    ll w;
    Edge(int a, int b, ll w) : a(a), b(b), w(w) {};
    Edge(ll w) : w(w) {};
};

class Solver {
  public:
    bool solve() {
        int N, M; cin >> N >> M;
        vector<ll> X(N); cin >> X;

        vector<map<int, ll>> E(N);
        rep(i, N) {
            int a, b, x; cin >> a >> b >> x;
            a--; b--;
            E[a][b] = x;
            E[b][a] = x;
        }

        function<void(int, set<int>&, ll*, vector<Edge>*)> go = [&] (int n, set<int> &visited, ll *n_sum, vector<Edge> *es) {
            visited.insert(n);
            *n_sum += X[n];
            for(auto p : E[n]) {
                es->emplace_back(n, p.first, p.second);
                if(not visited.count(p.first)) go(p.first, visited, n_sum, es);
            }
        };

        function<tuple<ll, set<int>>(int)> solve_one = [&] (int n) {
            cerr << n << endl;
            int res = 0;

            set<int> visited;
            ll sum = 0;
            vector<Edge> es;
            go(n, visited, &sum, &es);

            sort(all(es), [](const Edge &a, const Edge &b) { return a.w < b.w; });

            auto p = upper_bound(all(es), sum, [](const Edge &a, const Edge &b) { return a.w < b.w; });
            set<pii> erased;
            while(p != end(es)) {
                if(p->a > p->b) swap(p->a, p->b);
                if(not erased.count(make_pair(p->a, p->b))) {
                    cerr << "erase " << p->a << " " << p->b << endl;
                    E[p->a].erase(p->b);
                    E[p->b].erase(p->a);
                    res++;
                    erased.insert(make_pair(p->a, p->b));
                }
                p++;
            }

            if(res > 0) {

                set<int> visited2;
                for(int x : visited) {
                    if(not visited2.count(x)) {
                        ll sum2;
                        set<int> visited3;
                        tie(sum2, visited3) = solve_one(x);
                        for(int a : visited3) visited2.insert(a);
                        res += sum2;
                    }
                }
            }
            return make_tuple(res, visited);
        };

        cout << get<0>(solve_one(0)) << endl;
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
