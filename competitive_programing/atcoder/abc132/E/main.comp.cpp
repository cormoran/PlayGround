#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define rep(i, j) for(int i=0; i < (int)(j); i++)
#define repeat(i, j, k) for(int i = (j); i < (int)(k); i++)
#define all(v) v.begin(),v.end()
#define debug(x) cerr << #x << " : " << x << endl


const ll INFL = 1LL << 60;

struct Edge{
    int to;
    ll cost;
    int from; // from は使わないことも多い
    Edge(int to, ll cost, int from = -1):to(to), cost(cost), from(from) {}
};

using EdgeList = vector<vector<Edge>>;

struct State {
    int index;
    ll cost;
    int step;
    State(int i, ll c, int step):index(i), cost(c), step(step) {}
    bool operator > (const State &r) const { return cost > r.cost; }
};

// O(ElogV)
ll dijkstra(const EdgeList &G, int start, int end) {
    priority_queue<State, vector<State>, greater<State>> que;
    vector<vector<ll>> dist(G.size(), vector<ll>(3, INFL));
    que.emplace(start, 0, 0);
    dist[start][0] = 0;
    while(not que.empty()){
        State now = que.top(); que.pop();
        int next_step = (now.step + 1) % 3;
        for(Edge e : G[now.index]){
            if(dist[e.to][next_step] > now.cost + e.cost){
                State nxt = State(e.to, now.cost + e.cost, next_step);
                dist[e.to][next_step] = nxt.cost;
                que.push(nxt);
            }
        }
    }
    return dist[end][0];
}


int main() {
    int N, M; cin >> N >> M;
    EdgeList E(N);
    rep(i, M) {
        int a, b; cin >> a >> b;
        a--; b--;
        E[a].emplace_back(b, 1, a);
    }

    int S, T; cin >> S >> T;
    S--; T--;

    ll min_dist = dijkstra(E, S, T);
    assert(min_dist == INFL or min_dist % 3 == 0);
    cout << (min_dist == INFL ? -1 : min_dist / 3) << endl;

    return 0;
}
