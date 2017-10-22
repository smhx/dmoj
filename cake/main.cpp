#include <cstdio>
#include <set>
#define MAX 100005
#define INF 1000000000
using namespace std;

typedef pair<int, int> ii;

int R, C;
ii row[MAX], col[MAX], drow[MAX], dcol[MAX];

void create(ii *A, ii* B, int lenA, int lenB) {
	set<int> s;
	for (int i = 1; i <= lenB; ++i) s.insert(i);
	for (int i = 1; i <= lenA; ++i) {
		for (auto it = s.lower_bound(A[i].first); it != s.upper_bound(A[i].second);) {
            B[*it].first = i;
            it = s.erase(it);
        } 
    }	
    for (int i = 1; i <= lenB; ++i) s.insert(i);
	for (int i = lenA; i; --i) {
		for (auto it = s.lower_bound(A[i].first); it!=s.upper_bound(A[i].second);) {
		     B[*it].second = i;
        	 it = s.erase(it);
 		} 	
	}
}
int main() {
    // freopen("data.txt", "r", stdin);
    scanf("%d%d", &R, &C);
    
	for (int i = 1; i <= R; ++i) 
		scanf("%d%d", &row[i].first, &row[i].second);
	for (int i = 1; i <= C; ++i)
        scanf("%d%d", &col[i].first, &col[i].second);
    

    for (int i = 1; i <= R; ++i)
        drow[i].first = INF, drow[i].second = 0;
    
    for (int i = 1; i <= C; ++i)
        dcol[i].first = INF, dcol[i].second = 0;

    create(row, dcol, R, C);
    
    for (int c = 1; c <= C; ++c) {
        if (dcol[c].first != col[c].first) {
            printf("nonsense\n%d %d\n", min(col[c].first, dcol[c].first), c);
            return 0;
        } else if (dcol[c].second != col[c].second) {
            printf("nonsense\n%d %d\n", max(col[c].second, dcol[c].second), c);
            return 0;
        }
    }

    create(col, drow, C, R);
    
    for (int r = 1; r <= R; ++r) {
        if (drow[r].first != row[r].first) {
            printf("nonsense\n%d %d\n", r, min(row[r].first, drow[r].first) );
            return 0;
        } else if (drow[r].second != row[r].second) {
            printf("nonsense\n%d %d\n", r, max(row[r].second, drow[r].second) );
            return 0;
        }
    }

    for (int i = 1; i < R; ++i) {
        if (row[i].second < row[i+1].first || row[i].first > row[i+1].second) {
            printf("nonsense\nunconnected\n");
            return 0;
        }
    }

    for (int i = 1; i < C; ++i) {
        if (col[i].second < col[i+1].first || col[i].first > col[i+1].second) {
            printf("nonsense\nunconnected\n");
            return 0;
        }
    }

    printf("sense\n");
   
}
