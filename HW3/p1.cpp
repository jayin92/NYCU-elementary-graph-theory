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

const int N = 1e5+5;

vector<int> p(N);
vector<int> sz(N, 1);

void init(){
    for(int i=0;i<N;i++){
        p[i] = i;
        sz[i] = 1;
    }
}

int find(int x){
    if(p[x] == x) return x;
    
    return p[x] = find(p[x]);
}

void merge(int x, int y){
    int fx = find(x);
    int fy = find(y);
    if(fx == fy) return;
    if(sz[fx] < sz[fy]) swap(fx, fy);
    
    p[fy] = fx;
    sz[fx] += sz[fy];
}


void solve(){
    init();
    int n, m;
    cin >> n >> m;
    vector<pll> a(n);
    vector<ll> c(n+1);
    vector<pair<ll, pll>> s;
    int tmp;
    for(int i=1;i<=n;i++){
        cin >> tmp;
        a[i-1] = {tmp, i};
        c[i] = tmp;
    }
    int u, v, w;
    for(int i=0;i<m;i++){
        cin >> u >> v >> w;
        s.push_back({w, {u, v}});
    }
    sort(ALL(s));
    sort(ALL(a));
    ll ans = 0;
    int root = a[0].Y;
    int idx = 0;
    for(int i=1;i<n;i++){
        debug(i);
        if(find(root) == find(a[i].Y)) continue;
        if(idx != m && a[0].X + a[i].X > s[idx].X){
            int x, y;
            x = s[idx].Y.X;
            y = s[idx].Y.Y;
            if(find(x) != find(y)){
                merge(x, y);
                ans += s[idx].X;
            }            
            idx ++;
            i--;
            continue;
        }
        ans += a[0].X + a[i].X;
        debug(a[0].Y, a[i].Y);
        merge(root, a[i].Y);
        
    }

    cout << ans << endl;
    
    
}

/********** Good Luck :) **********/
int main () {
    TIME(main);
    IOS();
    int t = 1;
    cin >> t;
    while(t--){
        solve();
    }

    return 0;
}

