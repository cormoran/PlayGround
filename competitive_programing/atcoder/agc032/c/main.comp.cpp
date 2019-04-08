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

bool go(const vector<pii> &edges, const vector<vector<pii>> &g, vector<int> &used, vector<int> &visited, int now, int prev, int goal) {
    if(visited[now]) return false;
    visited[now] = true;
    for(auto &e : g[now]) {
        if(used[e.first] or e.second == prev) continue;
        used[e.first] = true;
        if(e.second == goal || go(edges, g, used, visited, e.second, now, goal)) return true;
        used[e.first] = false;
    }
    return false;
};

bool pop_circuit(const vector<pii> &edges, const vector<vector<pii>> &g, vector<int> &used) {
    rep(i, edges.size()) if(!used[i]) {
        used[i] = true;
        vector<int> visited(g.size());
        bool res = go(edges, g, used, visited, edges[i].first, edges[i].second, edges[i].second);
        if(not res) used[i] = false;
        return res;
    }
    return false;
}

int main() {
    int N, M; cin >> N >> M;
    vector<vector<pii>> g(N);
    vector<pii> edges;
    rep(i, M) {
        int a, b; cin >> a >> b;
        a--;
        b--;
        g[a].emplace_back(i, b);
        g[b].emplace_back(i, a);
        edges.emplace_back(a, b);
    }
    vector<int> used(M);
    bool ok = true;
    rep(i, 3) ok &= pop_circuit(edges, g, used);
    while(pop_circuit(edges, g, used));
    rep(i, M) ok &= used[i];
    cout << (ok ? "Yes" : "No") << endl;
    return 0;
}
