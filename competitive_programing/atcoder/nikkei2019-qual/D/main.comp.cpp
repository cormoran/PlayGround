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
        int N, M; cin >> N >> M;
        vector<vector<int>> E(N);
        vector<vector<int>> rE(N);
        rep(i, N - 1 + M) {
            int a, b; cin >> a >> b;
            a--; b--;
            E[a].push_back(b);
            rE[b].push_back(a);
        }
        int root = -1;
        {
            rep(i, N) if(rE[i].size() == 0) {
                assert(root == -1);
                root = i;
            }
        }


        vector<int> parent(N, -2);
        vector<int> depth(N, -1);
        set<int> resolved;
        map<int, vector<int>> wait;
        map<int, vector<int>> wait2;

        function<void(int, int)> go = [&] (int now, int prev) {
            if(rE[now].size() > 1 and not resolved.count(now)) {
                wait[now].push_back(prev);
                if(wait[now].size() == rE[now].size()) {
                    wait2[now] = wait[now];
                    wait.erase(now);
                }
                return;
            }
            parent[now] = prev;
            depth[now] = (prev < 0 ? 0 : depth[prev]) + 1;
            for(int nxt : E[now]) {
                go(nxt, now);
            }
        };
        vector<pii> front = { make_pair(root, -1) };
        do {
            for(auto p : wait2) {
                if(p.second.size() < rE[p.first].size()) continue;
                int min_u = p.second[0];
                for(int u : p.second) {
                    if(depth[u] > depth[min_u]) min_u = u;
                }
                resolved.insert(p.first);
                front.emplace_back(p.first, min_u);
                wait2.erase(p.first);
            }
            for(pii p : front) go(p.first, p.second);
            front.clear();
        } while(wait2.size());

        rep(i, N) {
            cout << parent[i] + 1 << endl;
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
