#pragma once

struct node {
    char letter;
    struct node* left;
    struct node* right;
};
struct node* getLeft(struct node* n);
struct node* getRight(struct node* n);
char getLetter(struct node* n);
struct node populateTree();