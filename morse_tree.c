#include "includes/morse_tree.h"

// empty node for top of tree
struct node ROOT; 
// 2nd from top
struct node E, T;
// 2nd from bottom
struct node I, A, N, M;
struct node S, U, R, W, D, K, G, O;
// bottom level of tree
struct node H, V, F, L, P, J, B, X, C, Y, Z, Q;

struct node* getLeft(struct node* n) {
    return n->left;
}
struct node* getRight(struct node* n) {
    return n->right;
}
char getLetter(struct node* n) {
    return n->letter;
}

struct node populateTree() {
// Leaf nodes
    H.letter = 'H';
    V.letter = 'V';
    F.letter = 'F'; 
    L.letter = 'L';
    P.letter = 'P';
    J.letter = 'J';
    B.letter = 'B';
    X.letter = 'X';
    C.letter = 'C';
    Y.letter = 'Y';
    Z.letter = 'Z';
    Q.letter = 'Q';
// 2nd highest level of tree

    S.letter = 'S';
    // Sets the left node pointer of S to H
    S.left = &H;
    // Sets the right node pointer of S to V
    S.right = &V;
    
    U.letter = 'U';
    U.left = &F;

    R.letter = 'R';
    R.left = &L;

    W.letter = 'W';
    W.left = &P;
    W.right = &J;

    D.letter = 'D';
    D.left = &B;
    D.right = &X;

    K.letter = 'K';
    K.left = &C;
    K.right = &Y;

    G.letter = 'G';
    G.left = &Z;
    G.right = &Q;

    O.letter = 'O';
// 3rd highest level of tree
    I.letter = 'I';
    I.left = &S;
    I.right = &U;

    A.letter = 'A';
    A.left = &R;
    A.right = &W;


    N.letter = 'N';
    N.left = &D;
    N.right = &K;


    M.letter = 'M';
    M.left = &G;
    M.right = &O;

// 2nd highest level of the tree

    E.letter = 'E';
    E.left = &I;
    E.right = &A;

    T.letter = 'T';
    T.left = &N;
    T.right = &M;

// node with no character! (start point/ root of the tree)
    ROOT.left = &E;
    ROOT.right = &T;

    return ROOT;
}
