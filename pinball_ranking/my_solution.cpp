#include <cstdio>
using namespace std;

const int RED = 1;
const int BLACK = 0;

template <typename T>
struct Node {
    T key;
    int color, size;
    Node<T> *l, *r, *p;
    Node() : color(0), size(1), l(NULL), r(NULL), p(NULL) {}
    Node(T k) : key(k), color(0), size(1), l(NULL), r(NULL), p(NULL) {}
};

template <typename T>
class OST {
    public:
        OST(){
            NIL = new Node<T>();
            NIL->color = BLACK;
            root = NIL;
            root->p = NIL;
            NIL->size = 0;
        }
        ~OST() {
            clear(root);
            delete NIL;
        }
        void insert(T k) {
            Node<T> *z = new Node<T>(k), *y = NIL, *x=root;
            while (x != NIL) {
                ++x->size;
                y=x;
                x = z->key < x->key ? x->l : x->r;
            }
            z->p = y;
            if (y==NIL) root = z;
            else if (z->key < y->key) y->l = z;
            else y->r = z;
            z->l = NIL;
            z->r = NIL;
            z->color = RED;
            insertFix(z);
        }
        // returns the rank of x
        int rank(Node<T>* x) {
            int r = x->l->size+1;
            Node<T>* y = x;
            while (y != root) {
                if (y==y->p->r) r += y->p->l->size+1;
                y = y->p;
            }
            return r;
        }
        
        int rank(int k) {
            return rank( search(k) );
        }


    private:
        Node<T> *root, *NIL;

        Node<T>* search(T key) {
            return search(root, key);
        }

        Node<T>* search(Node<T>* x, T key) {
            if (x==NIL) return x;
            if (x->key==key) {
                Node<T>* s = search(x->r, key);
                return s==NIL ? x : s;
            }
            if (key < x->key) return search(x->l, key);
            return search(x->r, key);
        }

        void clear(Node<T>* x) {
            if (x->l != NIL) clear(x->l);
            if (x->r != NIL) clear (x->r);
            delete x;
        }   

        void leftRotate(Node<T>* x) {
            Node<T>* y = x->r;
            x->r = y->l;
            if (y->l != NIL) y->l->p = x;
            y->p = x->p;
            if (x->p==NIL) root = y;
            else if (x==x->p->l) x->p->l = y;
            else x->p->r = y;
            y->l = x;
            x->p = y;
            y->size = x->size;
            x->size = x->l->size+x->r->size+1;
        }
        void rightRotate(Node<T>* x) {
            Node<T>* y = x->l;
            x->l = y->r;
            if (y->r != NIL) y->r->p = x;
            y->p = x->p;
            if (x->p==NIL) root = y;
            else if (x==x->p->r) x->p->r = y;
            else x->p->l = y;
            y->r = x;
            x->p = y;
            y->size = x->size;
            x->size = x->r->size+x->l->size+1;
        }
        void insertFix(Node<T>* z) {
            while (z->p->color==RED){
                if (z->p==z->p->p->l) {
                    Node<T>* y = z->p->p->r;
                    if (y->color==RED) {
                        z->p->color = BLACK;
                        y->color = BLACK;
                        z->p->p->color = RED;
                        z = z->p->p;
                    } else {
                        if (z==z->p->r) {
                            z = z->p;
                            leftRotate(z);
                        }
                        z->p->color = BLACK;
                        z->p->p->color = RED;
                        rightRotate(z->p->p);
                    }
                } else {
                    Node<T>* y = z->p->p->l;
                    if (y->color==RED) {
                        z->p->color = BLACK;
                        y->color = BLACK;
                        z->p->p->color = RED;
                        z = z->p->p;
                    } else {
                        if (z==z->p->l) {
                            z = z->p;
                            rightRotate(z);
                        }
                        z->p->color = BLACK;
                        z->p->p->color = RED;
                        leftRotate(z->p->p);
                    }
                }
            }
            root->color = BLACK;
        }
};

int main() {
    int t;
    long long sum=0;
    OST<int> scores = OST<int>();
    scanf("%d", &t);
    for (int i = 1, score; i <= t; i++) {
        scanf("%d", &score);
        scores.insert(score);
        sum += i+1-scores.rank(score);
    }
    int avg = sum*100 / t;
    float f = float(avg) / 100.0f;
    printf("%.2f\n", f);
    return 0;
}
