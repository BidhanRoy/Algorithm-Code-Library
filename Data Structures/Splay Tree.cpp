template< typename T, typename Comp = std::less< T > >
class SplayTree {

    struct node {
        T *element;
        node *left, *right, *parent;
        node( const T &k ) {
            left = right = parent = NULL;
            element = new T(k);
        }
        ~node () {
            delete left;
            delete right;
            delete parent;
            delete element;
        }
    } *root;

    unsigned p_size;

    public :

    SplayTree() { root = NULL; p_size = 0; }
    ~SplayTree() { delete root; }

    node *find( T k ) { return find( &root , k ); }
    node *find( node **s, T k ) {
        if( *s == NULL ) return NULL;

        node *curr, *pred;

        curr = *s;
        pred = NULL;

        while( curr ) {
            if( k == *( curr -> element ) ) break;
            pred = curr;
            if( k <= *( curr -> element ) ) curr = curr -> left;
            else curr = curr -> right;
        }
        if( curr ) {
            splay( curr );
            return curr ;
        }
        splay( pred );
        return NULL;
    }

    unsigned size() { return p_size; }

    node *insert( T k ) { return insert( &root , k ); }
    node *insert( node **s, T k ) {
        if( *s == NULL ) {
            p_size++;
            return *s = new node ( k );
        }

        node *curr = *s;
        node *anterior = NULL;
        int dir = 0;
        while( curr ) {
            if( k == *( curr -> element ) ) return curr;
            anterior = curr;
            if( k <= *( curr -> element ) ) {
                dir = -1;
                curr = curr -> left;
            }
            else {
                dir = 1;
                curr = curr -> right;
            }
        }
        p_size++;
        curr = new node( k );
        curr -> parent = anterior;
        if( dir == -1 ) anterior -> left = curr ;
        else anterior -> right = curr;
        splay( curr );
        return curr;
    }

    void erase( T k ) { erase( &root , k ); }
    void erase( node **root, T k ) {
        node *sL, *sR;
        if( find( root , k ) ) {
            sL = (*root) -> left;
            if( sL ) sL -> parent = NULL;
            sR = (*root) -> right;
            if( sR ) sR -> parent = NULL;
            *root = join( sL , sR );
        }
    }

    node *join( node *sL , node *sR ) {
        if( sL ) {
            find( &sL , INT_MAX );
            sL -> right = sR;
            if( sR ) sR -> parent = sL;
            return sL;
        }
        else if ( sR ) return sR;
        return NULL;
    }

    pair< node ** , node ** > split( node *root , T div ) {
        if( root ) {
            find( &root , div );
            node **sL, **sR;
            *sL = root;
            *sR = root -> right;
            (*sL) -> right = NULL;
            return make_pair( sL, sR );
        }
        node ** empty;
        empty = NULL;
        return make_pair( empty , empty );
    }

    void splay( node *crt ) { splay( &root , crt ); }
    void splay( node **root , node *crt ) {
        node *father = crt -> parent;
        while( father ) {
            if( father -> parent == NULL ) singleRotate( crt );
            else doubleRotate( crt );
            father = crt -> parent;
        }
        *root = crt;
    }

    void zigLeft( node *x ) {
        node *p, *b;
        p = x -> parent;
        b = x -> right;
        x -> right = p;
        x -> parent = NULL;
        if( b ) b -> parent = p;
        p -> left = b;
        p -> parent = x;
    }

    void zigRight( node *x ) {
        node *p, *b;
        p = x -> parent;
        b = x -> left;
        x -> left = p;
        x -> parent = NULL;
        if( b ) b -> parent = p;
        p -> right = b;
        p -> parent = x;
    }

    void zigZigLeft( node *x ) {
        node *p, *g, *ggp;
        node *b, *c;
        p = x -> parent;
        g = p -> parent;
        b = x -> right;
        c = p -> right;
        ggp = g -> parent;
        x -> right = p;
        p -> parent = x;
        p -> right = g;
        g -> parent = p;
        if( b ) b -> parent = p;
        p -> left = b;
        if( c ) c -> parent = g;
        g -> left = c;
        x -> parent = ggp;
        if( ggp ) {
            if( ggp -> left == g ) ggp -> left = x;
            else ggp -> right = x;
        }
    }

    void zigZigRight ( node *x ) {
        node *p, *g, *ggp;
        node *b, *c;
        p = x -> parent;
        g = p -> parent;
        b = x -> left;
        c = p -> left;
        ggp = g -> parent;
        x -> left = p;
        p -> parent = x;
        p -> left = g;
        g -> parent = p;
        if( b ) b -> parent = p;
        p -> right = b;
        if( c ) c -> parent = g;
        g -> right = c;
        x -> parent = ggp;
        if( ggp ) {
            if( ggp -> left == g )
                ggp -> left = x;
            else ggp -> right = x;
        }
    }

    void zigZagLeft ( node *x ) {
        node *p, *g, *ggp;
        node *a, *b;
        p = x -> parent;
        g = p -> parent;
        ggp = g -> parent;
        a = x -> left;
        b = x -> right;
        x -> left = g;
        g -> parent = x;
        x -> right = p;
        p -> parent = x;
        if( a ) a -> parent = g;
        g -> right = a;
        if( b ) b -> parent = p;
        p -> left = b;
        x -> parent = ggp;
        if( ggp ) {
            if( ggp -> left == g )
                ggp -> left = x;
            else ggp -> right = x;
        }
    }

    void zigZagRight( node *x ) {
        node *p, *g, *ggp;
        node *a, *b;

        p = x -> parent;
        g = p -> parent;
        ggp = g -> parent;
        a = x -> left;
        b = x -> right;
        x -> right = g;
        g -> parent = x;
        x -> left = p;
        p -> parent = x;
        if( a ) a -> parent = p;
        p -> right = a;
        if( b ) b -> parent = g;
        g -> left = b;
        x -> parent = ggp;
        if( ggp ) {
            if( ggp -> left == g ) ggp -> left = x;
            else ggp -> right = x;
        }
    }

    void singleRotate( node *x ) {
        if( x -> parent -> left == x ) zigLeft(x);
        else zigRight(x);
    }

    void doubleRotate( node *x ) {
        if( x -> parent -> left == x && x -> parent -> parent -> left == x -> parent )
            zigZigLeft(x);
        else if( x -> parent -> left == x && x -> parent -> parent -> right == x -> parent )
            zigZagLeft(x);
        else if( x -> parent -> right == x && x -> parent -> parent -> right == x -> parent )
            zigZigRight(x);
        else if( x -> parent -> right == x && x -> parent -> parent -> left == x -> parent )
            zigZagRight(x);
    }
};
