#include <cstdio>

const int RED = 1;
const int BLACK = 0;

template <typename T>
struct Node {
    T key;
    int color, size;
    Node<T> *l, *r, *p;
    Node() : color(BLACK), size(1), l(NULL), r(NULL), p(NULL) {}
    Node(T k) : key(k), color(BLACK), size(1), l(NULL), r(NULL), p(NULL) {}
};

template <typename T>
class OST {
    public:
        OST(){
            NIL = new Node<T>();
            root = NIL;
            NIL->size = 0;
        }
        ~OST() {
            clear(root);
            delete NIL;
        }

        Node<T>* insert(T k) {
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
            return z;
        }

        int rank(Node<T>* x) {
            int r = x->l->size+1;
            Node<T>* y = x;
            while (y != root) {
                if (y==y->p->r) r += y->p->l->size+1;
                y = y->p;
            }
            return r;
        }

        void display() {
            displayHelper(root);
        }

    private:
        Node<T> *root, *NIL;

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
        void displayHelper(Node<T>* z) {
            if (z->color==BLACK) {
                printf("BLACK ");
            } else {
                printf("RED ");
            }
            printf("%d: (l, r) = (", z->key);
            if (z->l != NIL) {
                printf("%d, ", z->l->key);
            } else {
                printf("NIL, ");
            }
            if (z->r != NIL) {
                printf("%d)\n", z->r->key); 
            } else {
                printf("NIL)\n");
            }
            if (z->l != NIL) {
                displayHelper(z->l);
            }
            if (z->r != NIL) {
                displayHelper(z->r);
            }
        }
};

int N;
long long cnt=0;
int main() {
    scanf("%d", &N);
    OST<int> ost = OST<int>();
    for (int i = 1, k, r; i <= N; i++) {
        scanf("%d", &k);
        r = ost.rank(ost.insert(k));
        cnt += r-1 < i-r ? r-1 : i-r;
    }
    printf("%lld\n", cnt);
    return 0;
}