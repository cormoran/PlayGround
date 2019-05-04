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

const int dy[] = {0, 1, 0, -1};
const int dx[] = {1, 0, -1, 0};

class Solver {
  public:
    bool solve() {
        int H, W; cin >> H >> W;
        vector<string> G(H); cin >> G;

        queue<tuple<int, int, int>> que;
        rep(y, H) rep(x, W) if(G[y][x] == '#') que.emplace(y, x, 0);
        vector<vector<int>> g(H, vector<int>(W, -1));
        int cnt = 0;
        int max_cnt = -1;
        while(que.size()) {
            int y, x, c;
            tie(y, x, c) = que.front(); que.pop();
            if(g[y][x] >= 0) continue;
            g[y][x] = c;
            cnt++;
            max_cnt = max(max_cnt, c);
            rep(i, 4) {
                int ny = y + dy[i];
                int nx = x + dx[i];
                if(0 <= ny and ny < H and 0 <= nx and nx < W and g[ny][nx] < 0) {
                    que.emplace(ny, nx, c + 1);
                }
            }
        }

        assert(cnt == H * W);
        cout << max_cnt << endl;
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
