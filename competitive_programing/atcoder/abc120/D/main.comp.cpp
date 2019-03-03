#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, j) for(int i=0; i < (int)(j); i++)

struct UnionFind{
    int n;
    vector<int> p;
    vector<int> group_size;
    ll inconvenience;
    UnionFind(int n) : n(n), inconvenience((ll)n * (n - 1) / 2) {
        p.resize(n);
        group_size.resize(n);
        rep(i, n) p[i] = i;
        rep(i, n) group_size[i] = 1;
    }
    int root(int x){
        if(p[x] == x) return x;
        else return p[x] = root(p[x]);
    }
    void unite(int x,int y){
        x = root(x);
        y = root(y);
        if(x != y) {
            inconvenience -= (ll)group_size[y] * (n - group_size[y]);
            inconvenience -= (ll)group_size[x] * (n - group_size[x]);
            inconvenience += (ll)group_size[y] * group_size[x];

            p[y] = x;
            group_size[x] += group_size[y];
            group_size[y] = 0;
            inconvenience += (ll)group_size[x] * (n - group_size[x]);
        }
    }
    bool query(int x,int y){
        return root(x) == root(y);
    }
};

int main() {
    int N, M; cin >> N >> M;
    vector<int> A(M), B(M);
    rep(i, M) cin >> A[i] >> B[i];

    vector<ll> ans(M);

    {
        UnionFind uf(N);
        for(int i = M - 1; i >= 0; i--) {
            ans[i] = uf.inconvenience;
            uf.unite(A[i] - 1, B[i] - 1);
        }
        cerr << uf.inconvenience << endl;
    }

    rep(i, M) cout << ans[i] << endl;

    return 0;
}
