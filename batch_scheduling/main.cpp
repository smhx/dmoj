// Credit: https://github.com/alxli/Algorithm-Anthology/blob/master/Section-1-Elementary-Algorithms/1.3.5%20Convex%20Hull%20Trick%20(Fully%20Dynamic).cpp
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

// End of Convex Hull Optimization

#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 10005;

typedef long long ll;

int N;
ll S, T[MAXN], F[MAXN], sumT[MAXN], sumF[MAXN], dp[MAXN];

int main() {
	// freopen("data.txt", "r", stdin);
	scanf("%d %lld", &N, &S);
	for (int i = 1; i <= N; ++i) {
		scanf("%lld %lld", T+i, F+i);
		sumT[i] = T[i]+sumT[i-1];
		sumF[i] = F[i]+sumF[i-1];
	}
	hull_optimizer h;
	for (int i = N; i; --i) {
		h.add_line(-sumT[i], dp[i+1]+sumT[i]*sumF[N]);
		dp[i] = h.query(sumF[i-1]) + (S-sumT[i-1])*(sumF[N]-sumF[i-1]);
	}
	printf("%lld\n", dp[1]);
}