#include<stdio.h>
#include<stdlib.h>
#include <check.h>

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

node *search(node *curr_node, int value, node **parent) {
  if(curr_node == NULL) {
    return NULL;
  }
  if(curr_node->data == value) {
    return curr_node;
  }
  if(parent != NULL) {
    *parent = curr_node;
  }
  if(curr_node->data > value) {
    return search(curr_node->left, value, parent);
  } else { 
    return search(curr_node->right, value, parent);
  }
}

node *max(node *curr_node) {
  if(curr_node == NULL) {
    return NULL;
  }
  if(curr_node -> right == NULL) {
    return curr_node;
  } else {
    return max(curr_node -> right);
  }
}

node *min(node *curr_node, node **parent) {
  if(curr_node == NULL) {
    return NULL;
  }
  if(curr_node -> left == NULL) {
    return curr_node;
  } else {
    if(parent != NULL) {
      *parent = curr_node;
    }
    return min(curr_node -> left, parent);
  }
}

void insert(node *root, int value) {
  node *parent = NULL;
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

void delete(node **root, int value) {
  node *parent = NULL;
  node *substitute_parent = NULL;
  node *to_delete = search(*root, value, &parent);
  node *substitute;
  if(to_delete != NULL) {
    if(to_delete -> left != NULL && to_delete -> right != NULL) {
      substitute = min(to_delete -> right, &substitute_parent);
      to_delete -> data = substitute -> data;
      if(substitute_parent -> data >= substitute -> data) {
        substitute_parent -> left = substitute -> right;
      } else {
        substitute_parent -> right = substitute -> right;
      }
      free(substitute);
    } else if(to_delete -> left != NULL) {
      if(parent == NULL) {
        *root = to_delete -> left;
      } else {
        if(parent -> data >= to_delete -> data) {
          parent -> left = to_delete -> left;
        } else {
          parent -> right = to_delete -> left;
        }
      }
      free(to_delete);
    } else if(to_delete -> right != NULL) {
      if(parent == NULL) {
        *root = to_delete -> right;
      } else {
        if(parent -> data >= to_delete -> data) {
          parent -> left = to_delete -> right;
        } else {
          parent -> right = to_delete -> right;
        }
      }
      free(to_delete);
    } else {
      if(parent == NULL) {
        *root = NULL;
      } else {
        if(parent -> data >= to_delete -> data) {
          parent -> left = NULL;
        } else {
          parent -> right = NULL;
        }
      }
      free(to_delete);
    }
  }
}

void pre_order_traversal (node *curr_node, void (*f)(node*)) {
  if(curr_node != NULL) {
    f(curr_node);
    if(curr_node -> left != NULL) {
      pre_order_traversal(curr_node -> left, f);
    }
    if(curr_node -> right != NULL) {
      pre_order_traversal(curr_node -> right, f);
    }
  }
}

void in_order_traversal (node *curr_node, void (*f)(node*)) {
  if(curr_node != NULL) {
    if(curr_node -> left != NULL) {
      in_order_traversal(curr_node -> left, f);
    }
    f(curr_node);
    if(curr_node -> right != NULL) {
      in_order_traversal(curr_node -> right, f);
    }
  }
}

void print_node(node *to_print) {
  printf("%d\n", to_print -> data);
}

int main() {
  node *root = create_node(1, NULL, NULL);
  insert(root, 8);
  insert(root, 4);
  insert(root, 3);
  insert(root, 6);
  insert(root, 12);
  insert(root, 5);
  insert(root, 11);
  insert(root, 9);
  insert(root, 10);
  node * x = search(root, 5, NULL);
  delete(&root, 5);
  printf("%d\n", x -> data);
}
