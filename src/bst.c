#include<stdio.h>
#include<stdlib.h>

typedef struct node {
  int data;
  struct node *left;
  struct node *right; 
} node;

node * create_node(int data, node * left, node * right) {
  node *new_node = (node *) malloc(sizeof(node));
  new_node -> data = data;
  new_node -> left = left;
  new_node -> right = right;
  return new_node;
}

/* Returns the node in the tree that contains the searched value, or NULL otherwise.
 * When the node is not found, parent will point to a pointer to the parent of the
 * node where the searched value would live in case it existed in the tree (useful
 * if we want to then insert the value in the tree). */
node *search(node *curr_node, int value, node ** parent) {
  if(curr_node == NULL) {
    return NULL;
  }
  if(curr_node->data == value) {
    return curr_node;
  }
  *parent = curr_node;
  if(curr_node->data > value) {
    return search(curr_node->left, value, parent);
  } else { 
    return search(curr_node->right, value, parent);
  }
}

void insert(node *root, int value) {
  node *parent;
  node *result = search(root, value, &parent);
  if(result == NULL) {
    node *new_node = create_node(value, NULL, NULL);
    if(value >= parent -> data) {
      parent -> right = new_node;
    } else {
      parent -> left = new_node;
    }
  }
}

int main() {
  node *root = create_node(2, NULL, NULL);
  insert(root, 1);
  insert(root, 3);
  insert(root, 3);
  printf("%d\n", root -> right -> data);
  printf("%d\n", root -> left -> data);
  printf("%d\n", root -> data);
}
