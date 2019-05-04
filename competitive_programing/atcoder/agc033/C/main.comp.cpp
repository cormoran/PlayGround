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
    tuple<int, int> find_farest(int root, const vector<vector<int>> &edge) {
        queue<tuple<int, int, int>> que;
        que.emplace(root, -1, 0);
        int last, prev, dist;
        while(que.size()) {
            auto a = que.front(); que.pop();
            tie(last, prev, dist) = a;
            for(int c : edge[last]) if(c != prev) {
                    que.emplace(c, last, dist + 1);
                }
        }
        return make_tuple(last, dist);
    }
    int calc_depth(int now, int prev, vector<int> &depth, const vector<vector<int>> &edge) {
        depth[now] = 1;
        for(int nxt : edge[now]) {
            if(nxt == prev) continue;
            depth[now] = max(depth[now], calc_depth(nxt, now, depth, edge));
        }
        return depth[now] = 1;
    }
    pii find_center(int now, int prev, int prev_depth, const vector<int> &depth, const vector<vector<int>> &edge) {
        vector<int> depths = { prev_depth };
        for(int nxt : edge[now]) {
            if(nxt == prev) continue;
            depths.push_back(depth[nxt]);
        }
        sort(all(depths)); reverse(all(depths));
        pii res = pii(now, depths[0] + 1);
        for(int nxt : edge[now]) {
            if(nxt == prev) continue;
            pii tmp = find_center(nxt, now, depths[depth[nxt] != depths[0] ? 0 : 1] + 1, depth, edge);
            if(tmp.second < res.second) res = tmp;
        }
        return res;
    }
    bool solve() {
        int N; cin >> N;
        vector<vector<int>> edge(N);
        rep(i, N - 1) {
            int a, b; cin >> a >> b;
            a--; b--;
            edge[a].push_back(b);
            edge[b].push_back(a);
        }
        int max_dist;
        {
            int a, b;
            tie(a, ignore) = find_farest(0, edge);
            tie(b, max_dist) = find_farest(a, edge);
        }
        vector<int> visited(max_dist + 10, INF);
        visited[0] = 0;
        rep(i, max_dist+5) {
            set_min(visited[i + 1], visited[i] == 0 ? 1 : 0);
            set_min(visited[i + 2], visited[i] == 0 ? 1 : 0);
        }
        cout << (visited[max_dist] == 1 ? "Second" : "First") << endl;
        //debug(visited);
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
