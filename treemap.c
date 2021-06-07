#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;

struct TreeNode {
    void* key;
    void * value;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->key = key;
    new->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
  TreeMap * new = malloc(sizeof(TreeMap));
  new->root = NULL;
  new->current = NULL;
    new->lower_than = lower_than;
    return new;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
  void * aux = searchTreeMap(tree,key);
  if(aux == NULL)
  {
    //printf("Entro]]");
    TreeNode *nuevo = createTreeNode(key, value);
    nuevo->parent = tree->current;
    if(tree->current !=NULL)
    {
      if( tree->lower_than(tree->current->key,key)==1)
      {
        tree->current->right = nuevo;
        tree->current = nuevo;
        //tree->current->key = 
      }
      else
      {
        tree->current->left = nuevo;
        tree->current = nuevo;
      }
    }
    else
    {
      //printf("\nENTRO\n");
      tree->root = nuevo;
      tree->current = tree->root;
    }
  }
  else 
  {
    printf("\n EL MAPA DETECTA QUE LA CLAVE ES IGUAL\n");
  }
}

TreeNode * minimum(TreeNode * x){
  while(x)
  {
    if(!x->left )return x;
    x = x->left;
  }
    return NULL;
}


void removeNode(TreeMap * tree, TreeNode* node) {
  TreeNode *aux ; 
    if(tree->current->left && tree->current->right)
  {
    aux = minimum(tree->current->right);
    tree->current->key = aux->key;
    tree->current->value = aux->value;
    tree->current = aux;
  }
  if(tree->current->left == NULL && tree->current->right == NULL)
  {
    tree->current = tree->current->parent;
    if(tree->current->right)tree->current->right = NULL;
    if(tree->current->left)tree->current->left = NULL;
  }
  if(tree->current->left == NULL || tree->current->right == NULL)
  {
    //tree->current = tree->current->parent;
    if(tree->current->right)
    {
      if(tree->current->parent->right)
      {
        tree->current->parent->right = tree->current->left;
        tree->current->left->parent = tree->current->parent;
        tree->current = NULL;
      }
      if(tree->current)
      if(tree->current->parent->left)
      {
        tree->current->parent->right = tree->current->left;
        tree->current->left->parent = tree->current->parent;
        tree->current = NULL;
      }
    }
    if(tree->current)
    if(tree->current->left)
    {
      if(tree->current->parent->right)
      {
        tree->current->parent->right = tree->current->left;
        tree->current->left->parent = tree->current->parent;
        tree->current = NULL;
      }
      if(tree->current)
      if(tree->current->parent->left != NULL)
      {
        tree->current->parent->left = tree->current->left;
        tree->current->left->parent = tree->current->parent;
        tree->current = NULL;
      }
    }
  }


}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




void * searchTreeMap(TreeMap * tree, void* key) {
  tree->current = tree->root;
  while(tree->current != NULL)
  {
    if(is_equal(tree, tree->current->key, key) == 1)
    {
      return  tree->current->value;
    } 
    if(tree->lower_than(tree->current->key,key)==1)
    {
      if(tree->current->right == NULL)return NULL;
      tree->current = tree->current->right;
      //tree->current->key = 
    }
    else
    {
      if(tree->current->left == NULL)return NULL;
      tree->current = tree->current->left;
    }
  }
    return NULL;
}


void * upperBound(TreeMap * tree, void* key) {
  TreeNode * aux = searchTreeMap(tree, key);
  if(aux)return tree->current->value;
  tree->current = tree->root;
  void*keyaux = tree->current->key;
  while(is_equal(tree, key, tree->current->key)!=1)
  {
    //keyaux = tree->current->key;
    if(tree->lower_than(keyaux,key)==1)
    {
      printf("Entra");
      if(!tree->current->right)
      {
        if(tree->lower_than(tree->current->key,key)==1)return NULL;
        return keyaux;
      }
      else
      {
        tree->current = tree->current->right;

        if(tree->lower_than(key,tree->current->key)==1)keyaux = tree->current->key;
      }
    }
    else
    {
      if(tree->lower_than(key,keyaux)==1)
      {
        printf("entro");
        if(!tree->current->left)
        {
          return keyaux;
        }
        else
        {
          
          tree->current = tree->current->left;
          if(tree->lower_than(key,tree->current->key)==1) keyaux = tree->current->key;
        }
      }
    }
    //keyaux = tree->current->key;
  }
    return NULL;
}

void * firstTreeMap(TreeMap * tree) {
  tree->current = minimum(tree->root);
    return tree->current->value;
}

void * nextTreeMap(TreeMap * tree) {
  TreeNode *x = tree->current;
  if(!tree->current->right)
  {
    //printf("Key : [%p] ",tree->current->key);
    while(tree->current)
    {
      
      if(tree->lower_than(x->key ,tree->current->key)==1)
      { 
        printf("ENTRA");
        return tree->current->value;
      }
      if(tree->current->parent == NULL)
      {
        printf("entro");
        return NULL;
      }
      tree->current = tree->current->parent;
    }
   
    
    
  }
  if(tree->current->right)
  {
    printf("Entra");
    tree->current = tree->current->right;
    tree->current = minimum(tree->current);
    return tree->current->value;
  }
    return NULL;
}
