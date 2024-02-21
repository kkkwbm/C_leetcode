#include <stdio.h>
#include <stdlib.h>

struct tree_t {
    struct node_t * root;
};

struct node_t {
    int x;
    struct node_t * left;
    struct node_t * right;
};

int tree_init(struct tree_t* ptree);
int tree_add(struct tree_t* ptree, int value);
int tree_add2(struct tree_t* ptree, int value);
int node_add(struct node_t* node, int value);
int node_add2(struct node_t** node, int value);
void display_tree(struct node_t *ptree); // enter root
int node_minimum(const struct node_t* node, int* poutput);
int node_maximum(const struct node_t* node, int* poutput);
int tree_minimum(const struct tree_t* ptree, int* poutput);
int tree_maximum(const struct tree_t* ptree, int* poutput);

int main() {
    struct tree_t tree;
    tree_init(&tree);
    int tab[] = {8,10,3,6,1,4,7,14,13};
    for (int i=0; i<9; i++)
        tree_add2(&tree, *(tab+i));
    display_tree(tree.root);
    int x;
    int res = tree_minimum(&tree,&x);
    printf("\n%d", x);
    tree_maximum(&tree,&x);
    printf("\n%d", x);
    return 0;
}



int tree_init(struct tree_t* ptree){
    if (ptree == NULL) return 1;
    ptree->root = NULL;
    return 0;
}
int node_add(struct node_t* node, int value){
    if (node == NULL) return 1;
    if (value > node->x)
    {
        if (node->right == NULL)
        {
            node->right = calloc(1,sizeof(struct node_t));
            if (node->right == NULL) return 2;

            node->right->x=value;
        }
        else return node_add(node->right,value);
    }
    else
    {
        if (node->left == NULL)
        {
            node->left = calloc(1,sizeof(struct node_t));
            if (node->left == NULL) return 2;

            node->left->x = value;
        }
        else return node_add(node->left, value);
    }
    return 0;
}
int node_add2(struct node_t ** node, int value){
    if (*node == NULL)
    {
        *node = calloc(1,sizeof(struct node_t));
        (*node)->x = value;
        return 0;
    }
    if (value>(*node)->x) return node_add2(&(*node)->right, value);
    return node_add2(&(*node)->left, value);
}

int tree_add(struct tree_t* ptree, int value){
    if (ptree == NULL) return 1;
    if (ptree->root == NULL)
    {
        struct node_t * node = calloc(1,sizeof(struct node_t));
        if (node == NULL) return 2;

        node->x = value;
        ptree->root = node;
        return 0;
    }
    return node_add(ptree->root, value);
}
int tree_add2(struct tree_t* ptree, int value){
    return node_add2(&ptree->root,value);
}

void display_tree(struct node_t *node){
    if (node == NULL)
    {
        printf("x");
        return;
    }
    printf("%d [", node->x);
    display_tree(node->left);
    display_tree(node->right);
    printf("] ");
}
int node_minimum(const struct node_t* node, int* poutput){
    if (node == NULL || poutput == NULL) return 1;
    if (node->left == NULL)
    {
        *poutput=node->x;
        return 0;
    }
    return node_minimum(node->left, poutput);
}
int node_maximum(const struct node_t* node, int* poutput){
    if (node == NULL || poutput == NULL) return 1;
    if (node->right == NULL)
    {
        *poutput=node->x;
        return 0;
    }
    return node_maximum(node->right, poutput);
}
int tree_minimum(const struct tree_t* ptree, int* poutput){
    if (ptree == NULL) return 1;
    return node_minimum(ptree->root, poutput);
}
int tree_maximum(const struct tree_t* ptree, int* poutput){
    if (ptree == NULL) return 1;
    return node_maximum(ptree->root, poutput);
}