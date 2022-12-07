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
int n, m, p, q, t, T;


void dijkstra(vector<ll>& d, vector<vector<pll>>& adj, int init, vector<int>& idx){
    priority_queue<pll, vector<pll>, greater<pll>> pq; // first: weight, second: vertex

    for(auto i: idx){
        d[i] = init;
        pq.push({init, i});
    }
    // d[src] = 0;
    while(!pq.empty()){
        pii edge = pq.top();
        pq.pop();
        ll u = edge.second;
        for(auto i: adj[u]){
            ll w = i.X;
            ll v = i.Y;
            ll alt = d[u] + w;
            if(alt < d[v]){
                d[v] = alt;
                pq.push({alt, v});
            }
        }
    }
}

void solve(){
    cin >> n >> m >> p >> q >> t >> T;
    vector<vector<pll>> adj1(n+1); // virus
    vector<vector<pll>> adj2(n+1); // antivirus
    vector<ll> dis1(n+1, INF);
    vector<ll> dis2(n+1, INF);
    
    vector<int> v;
    vector<int> av;
    int a, b, w;
    for(int i=0;i<m;i++){
        cin >> a >> b >> w;
        adj1[a].push_back({w, b});
        adj2[a].push_back({1, b});
    }
    int tmp;
    for(int i=0;i<p;i++){
        cin >> tmp;
        v.push_back(tmp);
    }

    for(int i=0;i<q;i++){
        cin >> tmp;
        av.push_back(tmp);
    }

    dijkstra(dis1, adj1, 0, v);
    dijkstra(dis2, adj2, t, v);

    int ans = 0;
    for(int i=1;i<=n;i++){
        if(dis1[i] <= T and dis2[i] <= T)
            ans += (dis1[i] < dis2[i]);
    }

    cout << ans << endl;

}

/********** Good Luck :) **********/
int main () {
    TIME(main);
    IOS();
    solve();

    return 0;
}

