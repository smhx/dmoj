
#include <limits>
#include <set>

class hull_optimizer {
  struct line {
    long long m, b, value;
    double xlo;
    bool is_query, query_max;

    line(long long m, long long b, long long v, bool is_query, bool query_max)
        : m(m), b(b), value(v), xlo(-std::numeric_limits<double>::max()),
          is_query(is_query), query_max(query_max) {}

    double intersect(const line &l) const {
      if (m == l.m) {
        return std::numeric_limits<double>::max();
      }
      return (double)(l.b - b)/(m - l.m);
    }

    bool operator<(const line &l) const {
      if (l.is_query) {
        return query_max ? (xlo < l.value) : (l.value < xlo);
      }
      return m < l.m;
    }
  };

  std::set<line> hull;
  bool query_max;

  typedef std::set<line>::iterator hulliter;

  bool has_prev(hulliter it) const {
    return it != hull.begin();
  }

  bool has_next(hulliter it) const {
    return (it != hull.end()) && (++it != hull.end());
  }

  bool irrelevant(hulliter it) const {
    if (!has_prev(it) || !has_next(it)) {
      return false;
    }
    hulliter prev = it, next = it;
    --prev;
    ++next;
    return query_max ? (prev->intersect(*next) <= prev->intersect(*it))
                     : (next->intersect(*prev) <= next->intersect(*it));
  }

  hulliter update_left_border(hulliter it) {
    if ((query_max && !has_prev(it)) || (!query_max && !has_next(it))) {
      return it;
    }
    hulliter it2 = it;
    double value = it->intersect(query_max ? *--it2 : *++it2);
    line l(*it);
    l.xlo = value;
    hull.erase(it++);
    return hull.insert(it, l);
  }

 public:
  hull_optimizer(bool query_max = false) : query_max(query_max) {}

  bool empty() {return hull.empty();}

  void add_line(long long m, long long b) {
    line l(m, b, 0, false, query_max);
    hulliter it = hull.lower_bound(l);
    if (it != hull.end() && it->m == l.m) {
      if ((query_max && it->b < b) || (!query_max && b < it->b)) {
        hull.erase(it++);
      } else {
        return;
      }
    }
    it = hull.insert(it, l);
    if (irrelevant(it)) {
      hull.erase(it);
      return;
    }
    while (has_prev(it) && irrelevant(--it)) {
      hull.erase(it++);
    }
    while (has_next(it) && irrelevant(++it)) {
      hull.erase(it--);
    }
    it = update_left_border(it);
    if (has_prev(it)) {
      update_left_border(--it);
    }
    if (has_next(++it)) {
      update_left_border(++it);
    }
  }

  long long query(long long x) const {
    line q(0, 0, x, true, query_max);
    hulliter it = hull.lower_bound(q);
    if (query_max) {
      --it;
    }
    return it->m*x + it->b;
  }
};

#include <vector>
#include <cstdio>
#include <algorithm>

typedef std::pair<int,int> ii;
typedef long long ll;
typedef std::pair<ll,ll> pll;

const int MAXN = 3005;
const ll INF = 100000000000000LL;
int N, M, D, tidx[MAXN];
std::vector<ii> adj[MAXN];
std::vector<int> topo;

hull_optimizer hull[MAXN];

bool visit[MAXN];
void dfs(int u) {
  visit[u]=true;
  for (ii e : adj[u]) if (!visit[e.second]) dfs(e.second);
  topo.push_back(u);
}

ll mind[MAXN][MAXN];
void computeHull() {
  for (int i = 0; i < N; ++i)
    for (int n = 0; n < N; ++n) mind[i][n] = INF;
  mind[tidx[1]][0] = 0;
  for (int n = 1; n < N; ++n) {
    for (int i = N-1; i >= 0; --i) {
      int u = topo[i];
      for (ii e : adj[u]) 
        mind[i][n] = std::min(mind[i][n], 1LL*e.first+mind[tidx[e.second]][n-1]);
    }
  }
  for (int i = 0; i < N; ++i) 
    for (ll n = 0; n < N; ++n) 
      if (mind[i][n] != INF) hull[i].add_line(n, mind[i][n]);
}


#ifdef DMOJ
#define getchar() (*_pbuf ? *_pbuf++ : (_buf[fread_unlocked(_pbuf = _buf, 1, 2097152, stdin)] = 0, *_pbuf++))
char _buf[2097153], *_pbuf = _buf;

#endif


int read_signed_int() {
  int c, o = 0, sign=1;
  while (1) {
        c = getchar(); 
        if (c=='-' || c>='0') break;
    }
    if (c=='-') {
        sign=-1;
        c = getchar();
    }
  do {
    o = (o<<3)+(o<<1) + (c - '0');
  } while ((c = getchar()) >= '0');
  return o*sign;
}

int main() {
  freopen("data.txt", "r", stdin);
  N = read_signed_int(); M = read_signed_int(); D = read_signed_int();
  for (int i=0,u,v,t; i < M; ++i) {
    u = read_signed_int(); v = read_signed_int(); t = read_signed_int();
    adj[v].push_back({t,u});
  }
  for (int u = 1; u <= N; ++u) if (!visit[u]) dfs(u);
  std::reverse(topo.begin(), topo.end());
  for (int i = 0; i < topo.size(); ++i) tidx[topo[i]]=i;
  computeHull();
  ll sumC=0;
  for (int i = 1; i <= D; ++i) {
    int c = read_signed_int(); int d = read_signed_int();
    sumC += 1LL*c;
    if (hull[tidx[d]].empty()) printf("Cannot Deliver\n");
    else printf("%lld\n", hull[tidx[d]].query(sumC));
  }
}