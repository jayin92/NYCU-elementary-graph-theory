// :80 <enter>
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<int, ll> pil;
typedef pair<ll, int> pli;
typedef pair<double,double> pdd;
#define SQ(i) ((i)*(i))
#define MEM(a, b) memset(a, (b), sizeof(a))
#define SZ(i) int(i.size())
#define FOR(i, j, k, in) for (int i=j ; i<(k) ; i+=in)
#define RFOR(i, j, k, in) for (int i=j ; i>=(k) ; i-=in)
#define REP(i, j) FOR(i, 0, j, 1)
#define REP1(i,j) FOR(i, 1, j+1, 1)
#define RREP(i, j) RFOR(i, j, 0, 1)
#define ALL(_a) _a.begin(),_a.end()
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define X first
#define Y second
#ifdef jayinnn
#define TIME(i) Timer i(#i)
#define debug(...) do{\
    fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);\
    _do(__VA_ARGS__);\
}while(0)
template<typename T>void _do(T &&_x){cerr<<_x<<endl;}
template<typename T,typename ...S> void _do(T &&_x,S &&..._t){cerr<<_x<<", ";_do(_t...);}
template<typename _a,typename _b> ostream& operator << (ostream &_s,const pair<_a,_b> &_p){return _s<<"("<<_p.X<<","<<_p.Y<<")";}
template<typename It> ostream& _OUTC(ostream &_s,It _ita,It _itb)
{
    _s<<"{";
    for(It _it=_ita;_it!=_itb;_it++)
    {
        _s<<(_it==_ita?"":",")<<*_it;
    }
    _s<<"}";
    return _s;
}
template<typename _a> ostream &operator << (ostream &_s,vector<_a> &_c){return _OUTC(_s,ALL(_c));}
template<typename _a> ostream &operator << (ostream &_s,set<_a> &_c){return _OUTC(_s,ALL(_c));}
template<typename _a> ostream &operator << (ostream &_s,deque<_a> &_c){return _OUTC(_s,ALL(_c));}
template<typename _a,typename _b> ostream &operator << (ostream &_s,map<_a,_b> &_c){return _OUTC(_s,ALL(_c));}
template<typename _t> void pary(_t _a,_t _b){_OUTC(cerr,_a,_b);cerr<<endl;}
#define IOS()
class Timer {
private:
    string scope_name;
    chrono::high_resolution_clock::time_point start_time;
public:
    Timer (string name) : scope_name(name) {
        start_time = chrono::high_resolution_clock::now();
    }
    ~Timer () {
        auto stop_time = chrono::high_resolution_clock::now();
        auto length = chrono::duration_cast<chrono::microseconds>(stop_time - start_time).count();
        double mlength = double(length) * 0.001;
        debug(scope_name, mlength);
    }
};
#else
#define TIME(i)
#define debug(...)
#define pary(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif

const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int iNF = 0x3f3f3f3f;
const ll MAXN = 100005;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int n, m;

class Edge{
public:
    int to, rev, flow, cap;
    Edge(int _to, int _rev, int _flow, int _cap): to(_to), rev(_rev), flow(_flow), cap(_cap) {}
};

class Graph{
public:
    int v;
    vector<int> level;
    vector<vector<Edge>> adj;
    vector<bool> vis;
    Graph(int _v){
        v = _v;
        adj = vector<vector<Edge>>(v);
        level = vector<int>(v);
        vis = vector<bool>(v, false);
    }

    void addEdge(int x, int y, int cap){
        Edge forward(y, adj[y].size(), 0, cap);
        Edge backward(x, adj[x].size(), 0, 0);
        adj[x].push_back(forward);
        adj[y].push_back(backward);
    }

    bool bfs(int s, int t){
        fill(level.begin(), level.end(), -1);
        level[s] = 0;
        queue<int> q;
        q.push(s);
        while(!q.empty()){
            int cur = q.front();
            q.pop();
            for(auto &i: adj[cur]){
                if(level[i.to] == -1 && i.flow < i.cap){
                    level[i.to] = level[cur] + 1;
                    q.push(i.to);
                }
            }
        }

        return level[t] != -1;
    }

    int sendFlow(int u, int flow, int t, vector<int>& idx){
        if(u == t) return flow;
        for(; idx[u]<(int)adj[u].size();idx[u]++){
            Edge& e = adj[u][idx[u]];

            if(level[e.to] == level[u]+1 && e.flow < e.cap){
                int cur_flow = min(flow, e.cap - e.flow);
                int tmp_flow = sendFlow(e.to, cur_flow, t, idx);

                if(tmp_flow > 0){
                    e.flow += tmp_flow;
                    adj[e.to][e.rev].flow -= tmp_flow;
                    return tmp_flow;
                }
            }
        }

        return 0;
    }

    int dinic(int s, int t){
        for(int i=0;i<v;i++){
            for(Edge& j: adj[i]){
                j.flow = 0;
            }
        }
        if(s == t) return -1;
        int total = 0;
        while(bfs(s, t)){
            vector<int> idx(v, 0);
            while(int flow = sendFlow(s, iNF, t, idx)){
                total += flow;
            }
        }

        return total;
    }
};

void solve(){
    cin >> n >> m;
    Graph g(2*n+1);
    int u, v;
    // for(int i=1;i<=n;i++){
    //     g.addEdge(i, n+i, 1);
    //     g.addEdge(n+i, i, 1);
    // }
    for(int i=0;i<m;i++){
        cin >> u >> v;
        // g.addEdge(n+u, v, 1);
        g.addEdge(v, u, 1);
        g.addEdge(u, v, 1);
    }
    int ans = iNF;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(i != j)
                ans = min(ans, g.dinic(i, j));
        }
    }

    cout << ans << endl;
}

/********** Good Luck :) **********/
int main () {
    TIME(main);
    IOS();
    int t = 1;
    // cin >> t;
    while(t--){
        solve();
    }

    return 0;
}