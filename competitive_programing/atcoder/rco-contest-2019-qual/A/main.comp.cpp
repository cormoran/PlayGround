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

double calc_var(int sum2, double sum, int N) {
    return (double)sum2 / N - sum * sum / N / N;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);



    int N; cin >> N;
    vector<int> X(N), Y(N); rep(i, N) cin >> X[i] >> Y[i];


    vector<vector<int>> dist2(N, vector<int>(N));
    rep(i, N) rep(j, N) dist2[i][j] = (X[i] - X[j]) * (X[i] - X[j]) + (Y[i] - Y[j]) * (Y[i] - Y[j]);

    vector<int> arange;
    double arange_sum = 0;
    int arange_sum2 = 0;
    double last_exp = 0;
    {
        double l = 0, r = 700;

        auto go = [&] (double expect) {
            vector<int> arange;
            double arange_sum = 0;
            int arange_sum2 = 0;
            rep(init, N) {
                vector<int> used(N);
                vector<int> aarange;
                aarange.reserve(N);
                aarange.push_back(init);
                double sum = 0;
                int sum2 = 0;
                used[init] = true;
                rep(i, N - 1) {
                    int a = aarange.back();
                    int min_b = -1;
                    rep(j, N) if(not used[j]) {
                        int b = j;
                        if(min_b < 0 or abs(dist2[a][min_b] - expect * expect) > abs(dist2[a][b] - expect * expect)) {
                            min_b = b;
                        }
                    }
                    used[min_b] = true;
                    aarange.push_back(min_b);
                    sum2 += dist2[a][min_b];
                    sum += sqrt(dist2[a][min_b]);
                }
                sum += sqrt(dist2[aarange.back()][aarange.front()]);
                sum2 += dist2[aarange.back()][aarange.front()];
                if(arange.size() == 0 or calc_var(sum2, sum, N) < calc_var(arange_sum2, arange_sum, N)) {
                    arange = aarange;
                    arange_sum = sum;
                    arange_sum2 = sum2;
                }
            }
            return make_tuple(calc_var(arange_sum2, arange_sum, N), arange, arange_sum, arange_sum2);
        };

        while(abs(r - l) > 0.1) {
            double expect1 = l + (r - l) / 3.0;
            double expect2 = l + (r - l) / 3.0 * 2;
            auto a = go(expect1);
            auto b = go(expect2);
            if(get<0>(a) > get<0>(b)) l = expect1;
            else r = expect2;
            if(arange.size() == 0 or get<0>(a) < calc_var(arange_sum2, arange_sum, N)) {
                tie(ignore, arange, arange_sum, arange_sum2) = a;
            }
            if(get<0>(b) < calc_var(arange_sum2, arange_sum, N)) {
                tie(ignore, arange, arange_sum, arange_sum2) = b;
            }
        }
    }

    vector<int> ans = arange;
    double ans_score = calc_var(arange_sum2, arange_sum, N);

    rep(i, N) cout << ans[i] << endl;
    cerr << "last score = " << 1e6 / (1 + ans_score) << endl;

    return 0;
}
