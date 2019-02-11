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

const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};

class Solver {
  public:
    bool solve() {
        int N, M; cin >> N >> M;
        vector<vector<int>> A(N, vector<int>(N)); cin >> A;


        set<pii> used;
        set<pii> ignore;

        auto find_min = [&] () {
            int mi, mj, mv = -1;
            rep(i, N) rep(j, N) {
                if(not used.count(pii(i, j)) and not ignore.count(pii(i, j)) and A[i][j] > mv) mv = A[i][j], mi = i, mj = j;
            }
            return make_pair(mi, mj);
        };

        auto try_grow = [&] (int left_m, int i, int j) {
            assert(not used.count(pii(i, j)));

            vector<tuple<int, int, int>> ops;
            set<pii> ok, used2;
            auto comp = [&] (pii a, pii b) {
                return A[i][j] - A[a.first][a.second] > A[i][j] - A[b.first][b.second];
            };
            priority_queue<pii, vector<pii>, decltype(comp)> que(comp);
            que.emplace(i, j);
            used2.emplace(i, j);
            // cerr << "    push init " << i << "," << j << endl;
            while(que.size()) {
                auto p = que.top(); que.pop();
                // cerr << "    pop " << p << endl;

                if(A[i][j] - A[p.first][p.second] < left_m) {
                    left_m -= A[i][j] - A[p.first][p.second];
                    ok.insert(p);
                    rep(foo, A[i][j] - A[p.first][p.second])
                            ops.emplace_back(1, p.first, p.second);

                    rep(dir, 4) {
                        int ny = p.first + dy[dir];
                        int nx = p.second + dx[dir];
                        if(0 <= ny and ny < N and 0 <= nx and nx < N and not used.count(pii(ny, nx)) and not used2.count(pii(ny, nx))) {
                            if(A[i][j] >= A[ny][nx]) {
                                que.emplace(ny, nx);
                                used2.emplace(ny, nx);
                            }
                        }
                    }
                    if(ok.size() >= A[i][j] and (que.size() and A[que.top().first][que.top().second] < A[i][j])) break;
                }
            }
            if(ok.size() >= A[i][j] and left_m > 0) {
                ops.emplace_back(2, i, j);
                left_m--;
            } else {
                ops.clear();
                ok.clear();
            }
            return make_tuple(ops, ok, left_m);
        };

        vector<tuple<int, int, int>> ans_op;
        vector<tuple<int, int, int>> pick_op;
        int left_m = M;
        auto start = chrono::system_clock::now();
        rep(tmp, M) {
            // cerr << "----" << endl;
            // debug(A);
            pii p = find_min();
            // cerr << "found min " << p << " = " << A[p.first][p.second] <<  endl;
            auto res = try_grow(left_m, p.first, p.second);
            if(get<0>(res).size() > 0) {
                for(auto op : get<0>(res)) {
                    ans_op.push_back(op);
                }
                for(auto x : get<1>(res)) {
                    used.insert(x);
                    A[x.first][x.second] = -1;
                }
                left_m = get<2>(res);
            } else {
                ignore.insert(p);
            }
            if(M <= 0) break;
            if(chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now() - start).count() > 1900) break;
        }
        for(auto op : ans_op) {
            cout << get<0>(op) << " " << get<1>(op) << " " << get<2>(op) << endl;
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
