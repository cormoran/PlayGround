#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, j) for(int i=0; i < (int)(j); i++)
template<class T> istream& operator >> (istream &is , vector<T> &v) { for(T &a : v) is >> a; return is; }


vector<int> simulate(int N, ll left, const vector<ll> &A, int start) {
    map<ll, int> s;
    vector<int> stk;
    for(ll i = start; left > 0; i++, left--) {
        ll a = A[i % N];
        if(s[a] > 0) {
            int sa = s[a];
            while(stk.size() >= sa) {
                s[stk.back()] = 0;
                stk.pop_back();
            }
        } else {
            stk.push_back(a);
            s[a] = stk.size();
        }
    }
    return stk;
}

int main() {
    int N; ll K; cin >> N >> K;
    vector<ll> A(N); cin >> A;

    vector<int> next_index(N);
    {
        map<ll, int> last;
        for(int i = N * 2 - 1; i >= 0; i--) {
            if(i < N) next_index[i] = last[A[i]];
            last[A[i%N]] = i % N;
        }
    }

    ll left = K * N;

    vector<int> visited_index(N, -1);
    vector<ll> diff_sum;
    diff_sum.push_back(0);

    int now = 0;
    while(left) { // O(N)
        if(visited_index[now] >= 0) { // O(1)
            ll sum = diff_sum.back() - diff_sum[visited_index[now] - 1];
            left = left % sum;
        }
        int next = next_index[now];
        ll diff = (next <= now ? next + N - now : next - now) + 1;
        if(diff > left) break;
        left -= diff;
        visited_index[now] = diff_sum.size();
        now = (next + 1) % N;
        diff_sum.push_back(diff + diff_sum.back());
    }

    auto ans = simulate(N, left, A, now);
    rep(i, ans.size()) cout << ans[i] << (i == ans.size() - 1 ? "\n" : " ");

    return 0;
}
