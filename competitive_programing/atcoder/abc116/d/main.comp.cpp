#include <bits/stdc++.h>
using namespace std;
using pii = pair<int,int>;
using ll = long long;
#define rep(i, j) for(int i=0; i < (int)(j); i++)
#define repeat(i, j, k) for(int i = (j); i < (int)(k); i++)
#define all(v) v.begin(),v.end()
template<class T> bool set_max(T &a, const T &b) { return a < b  ? a = b, true : false; }



int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    int N, K; cin >> N >> K;
    vector<int> T(N), D(N); rep(i, N) cin >> T[i] >> D[i];

    // list
    vector<int> top1_list, other_list;
    {
        map<int, pii> top1;
        rep(i, N) set_max(top1[T[i]], make_pair(D[i], i));

        set<int> top1_indices;
        for(auto &p : top1) top1_indices.insert(p.second.second);

        rep(i, N) (top1_indices.count(i) ? top1_list : other_list).push_back(D[i]);
    }
    while(other_list.size() < N) other_list.push_back(0);

    // sum
    auto make_sum = [] (vector<int> &l) {
        sort(all(l), greater<int>());
        vector<ll> sum(l.size() + 1);
        rep(i, l.size()) sum[i + 1] = sum[i] + l[i];
        return sum;
    };
    auto top1_sum = make_sum(top1_list);
    auto other_sum = make_sum(other_list);

    // go
    ll ans = 0;
    repeat(k, 1, K + 1) {
        ll l = K - k;
        if(k >= top1_sum.size()) continue;
        ll sum = top1_sum[k] + other_sum[l];

        if(l > 0) {
            int m = upper_bound(all(top1_list), other_list[l - 1], greater<int>()) - begin(top1_list) - 1 + 1;

            if(m - k > l) m = k + l;

            if(k < m and m < top1_sum.size()) {
                sum = top1_sum[m] + other_sum[K - m];
            }
        }
        set_max(ans, sum + (ll)k * k);
    }
    cout << ans << endl;

    return 0;
}
