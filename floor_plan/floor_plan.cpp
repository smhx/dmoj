#include <cstdio>
#include <unordered_map>
#include <queue>
using namespace std;

template <class T>
struct Node {
	Node(T k) {
		rank = 0;
		key = k;
		parent = this;
	}
	~Node() {
		if (parent != this)
			delete parent;
	}
	Node<T>* parent;
	int rank;
	T key;
};

template <class T>
class DisjointSets {
public:
	
	void makeSet(T key) {
		if (nodes.find(key) == nodes.end()) {
			nodes.insert(make_pair(key, new Node<T>(key)));
			
		}
	}

	T findSet(T key) {
		Node<T>* p = nodes[key]->parent;
		while (p->parent != p) {
			p = p->parent;
		}
		return p->key;
	}

	void mergeSets(T a, T b) {
		if (nodes.find(a)==nodes.end() || nodes.find(b)==nodes.end())
			return;
		int x = this->findSet(a);
		int y = this->findSet(b);
		Node<T>* X = nodes[x];
		Node<T>* Y = nodes[y];
		if (X->rank > Y->rank) {
			Y->parent = X;
		} else {
			X->parent = Y;
			if (X->rank == Y->rank) {
				++Y->rank;
			}
		}
	}

	unordered_map<T, Node<T>* > nodes;
};


// true for occupied, false for unoccupied
bool floorPlan[25][25];
int main () {
	int A, r, c;
	DisjointSets<int> ds;
	scanf("%d %d %d", &A, &r, &c);
	char in;
	for (int i = 0; i < r; i++) {
		scanf("%c", &in);
		for (int j = 0; j < c; j++) {
			
			scanf("%c", &in);
			floorPlan[i][j] = in=='I';
			if (!floorPlan[i][j]) ds.makeSet(c*i+j);
		}
	}

	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (floorPlan[i][j]) continue;
			int original = c*i+j;
			if ((i+1)<r) {
				if (!floorPlan[i+1][j]) {
					if (ds.findSet(original) != ds.findSet(original+c)){
						ds.mergeSets(original, original+c);
					}
				}
			}
			if ((j+1)<c) {
				if (!floorPlan[i][j+1]) {
					if (ds.findSet(original) != ds.findSet(original+1)){
						ds.mergeSets(original, original+1);
					}
				}
			}
		}
	}
	unordered_map<int, int> areas;

	for (auto pair : ds.nodes) {
		int s = ds.findSet(pair.first);
		if (areas.find(s)==areas.end()) {
			areas.insert(make_pair(s, 1));
		} else {
			++areas[s];
		}
	}
	priority_queue<int> pq;

	for (auto pair: areas) {
		pq.push(pair.second);
	}
	int count = 0;
	while (A >= pq.top() && !pq.empty()) {
		A -= pq.top();
		pq.pop();
		++count;
	}
	if (count==1)
		printf("1 room, %d square metre(s) left over\n", A);
	else 
		printf("%d rooms, %d square metre(s) left over\n", count, A);
	return 0;
}