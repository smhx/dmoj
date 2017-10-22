#include <cstdio>
#include <cstdlib>
#include <ctime>

template <typename T>
struct Node {
    T key;
    int color, size;
    Node<T> *l, *r, *p;
    Node() : color(0), size(1), l(0), r(0), p(0) {}
    Node(T k) : key(k), color(0), size(1), l(0), r(0), p(0) {}
};

template <typename T>
class OST {
    public: 
        OST();
        ~OST();
        void insert(T);
        bool del(T);
        void display() const;
        int rank(T);
        T select(int);
    private: 
        static const int RED = 1, BLACK=0;    
        Node<T> *root, *NIL;
        void clear(Node<T>*);
        void leftRotate(Node<T>*);
        void rightRotate(Node<T>*);
        void insertFix(Node<T>*);
        void display(Node<T>*) const;
        void transplant(Node<T>*, Node<T>*);
        void del(Node<T>*);
        void delFix(Node<T>*);
        Node<T>* successor(Node<T>*);
        Node<T>* search(T, Node<T>*) const;
        int rank(Node<T>*);
        Node<T>* select(Node<T>*, int);
};


template <typename T>
inline OST<T>::OST(){
    NIL = new Node<T>();
    root = NIL;
    root->p = NIL;
    NIL->size=0;
}

template <typename T> 
OST<T>::~OST(){
    clear(root);
    delete NIL;
}

template <typename T>
void OST<T>::insert(T k) {
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

template <typename T>
inline void OST<T>::display() const {
    display(root);
}

template <typename T> 
bool OST<T>::del(T k) {
    if (root==NIL) {
        return 0;
    }
    Node<T>* x = search(k, root);
    if (x==NIL) return 0;
    del(x);
    return 1;
}

template <typename T> 
inline int OST<T>::rank(T k) {
    return rank( search(k, root) );
}

template <typename T>
inline T OST<T>::select(int i){
    return select(root, i)->key;
}

template <typename T>
void OST<T>::clear(Node<T>* x) {
    if (x==NIL) return;
    if (x->l != NIL) clear(x->l);
    if (x->r != NIL) clear (x->r);
    delete x;
} 
template <typename T>
void OST<T>::leftRotate(Node<T>* x) {
    if (x==NIL) return;
    Node<T>* y = x->r;
    if (y==NIL)return;
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
template <typename T>
void OST<T>::rightRotate(Node<T>* x) {
    if (x==NIL) return;
    Node<T>* y = x->l;
    if (y==NIL) return;
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

template <typename T>
void OST<T>::insertFix(Node<T>* z) {
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
template <typename T>
void OST<T>::display(Node<T>* z) const {
    if (z==NIL) return;
    display(z->l);
    printf("%d ", z->key);
    display(z->r);
}

template <typename T> 
void OST<T>::transplant(Node<T>* u, Node<T>* v) {
    if (u->p==NIL) root=v;
    else if (u==u->p->l) u->p->l = v;
    else u->p->r=v;
    v->p=u->p;
}

template <typename T>
Node<T>* OST<T>::successor(Node<T>* z) {
    Node<T>* y;
    if (z->r != NIL) {
        y=z->r;
        while (y->l!=NIL) y=y->l;
        return y;
    }
    y=z->p;
    while (y!=NIL && z==y->r){
        z=y;
        y=y->p;
    }
    return y;
}

template <typename T> 
void OST<T>::del(Node<T>* z) {
    Node<T> *x,*y;
    if (z->l==NIL || z->r==NIL) y=z;
    else y=successor(z);
    if (y->l != NIL) x=y->l;
    else x=y->r;
    x->p=y->p;
    if (y->p==NIL) root=x;
    else if (y==y->p->l) y->p->l=x;
    else y->p->r=x;
    if (y!=z) z->key=y->key;
    Node<T>* t=y;
    while (t!=NIL) {
        --t->size;
        t=t->p;
    }
    if (y->color==BLACK) delFix(x);
    delete y;
}

template <typename T> 
void OST<T>::delFix(Node<T>* x) {
    while (x!=root && x->color==BLACK){
        if (x==x->p->l){
            Node<T>* w=x->p->r;
            if (w->color==RED){
                x->p->color=RED;
                leftRotate(x->p);
                w=x->p->r;
            }
            if (w==NIL) return;
            if (w->l->color==BLACK && w->r->color==BLACK){
                w->color=RED;
                x=x->p;
            } else if (w->r->color==BLACK){
                w->l->color=BLACK;
                w->color=RED;
                rightRotate(w);
                w=x->p->r;
            }
            w->color=x->p->color;
            x->p->color=BLACK;
            w->r->color=BLACK;
            leftRotate(x->p);
            x=root;
        } else {
            Node<T>* w=x->p->l;
            if (w->color==RED){
                x->p->color=RED;
                rightRotate(x->p);
                w=x->p->l;
            }
            if (w==NIL) return;
            if (w->l->color==BLACK && w->r->color==BLACK){
                w->color=RED;
                x=x->p;
            } else if (w->l->color==BLACK){
                w->r->color=BLACK;
                w->color=RED;
                leftRotate(w);
                w=x->p->l;
            }
            w->color=x->p->color;
            x->p->color=BLACK;
            w->l->color=BLACK;
            rightRotate(x->p);
            x=root;
        }
    }
    x->color=BLACK;
}

template <typename T> 
Node<T>* OST<T>::search(T k, Node<T>* x) const {
    if (x==NIL) return x;
    if (x->key==k){
        Node<T>* r=search(k, x->l);
        if (r==NIL) return x;
        return r;
    }
    if (k<x->key) return search(k, x->l);
    return search(k, x->r);
}

template <typename T> 
int OST<T>::rank(Node<T>* x) {
    if (x==NIL) return -1;
    int r = x->l->size+1;
    Node<T>* y = x;
    while (y != root) {
        if (y==y->p->r) r += y->p->l->size+1;
        y = y->p;
    }
    return r;
}

template <typename T>
Node<T>* OST<T>::select(Node<T>* x, int i){
    int r=x->l->size+1;
    if (i==r) {
        return x;
    }
    if (i<r) {
        return select(x->l, i);
    }
    return select(x->r, i-r);
}

int N, M, lastAns=0;

int main() {
    // srand(time(NULL));
    OST<int> ost = OST<int>();
    scanf("%d%d", &N, &M);
    for (int i=0, a; i<N;i++){ 
        scanf("%d", &a); 
        // a = rand()%100000+1;
        // printf("Adding %d\n", a);
        ost.insert(a);
        // ost.insert(rand()%20+1);
    }

    // printf("Before queries, ost is:\n");
    // ost.display();
    // printf("\n");
   
    for (int i=0;i<M; i++) {
        // int v, q;
        // q = rand()%4;
        // v = rand()%100000+1;
        // printf("QUERY %d, q=%d and v=%d: ", i+1, q, v);
        // if(q==0){
        //     printf("Inserting %d\n", v);
        //     ost.insert(v);
        //     ++N;
        // } else if (q==1) {
        //     printf("Deleting %d\n", v);
        //     ost.del(v);
        //     --N;
        // } else if (q==2) {
        //     v = v % N;
        //     printf("Selecting %d and returning ", v);
        //     printf("%d\n", ost.select(v));
        // } else {
        //     printf("Ranking %d and returning ", v);
        //     printf("%d\n", ost.rank(v));
        // }
        int v; char c;
        scanf(" %c %d", &c, &v);
        int x=lastAns^v;
        if (c=='I'){
            ost.insert(x);
        } else if (c=='R'){
            ost.del(x);
        } else if (c=='S'){
            lastAns=ost.select(x);
            printf("%d\n", lastAns);
        } else {
            lastAns=ost.rank(x);
            printf("%d\n", lastAns);
        }
    }
    ost.display();
    return 0;
}