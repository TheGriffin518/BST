#ifndef BTREE_H
#define BTREE_H

#include <fstream>
class btree{

  struct node
  {
    int data;
    node* left;
    node* right;
  };

  node * root;

 public:
  btree();
  ~btree();

  bool isFull();
  bool isEmpty();
  int getItem(int key);
  int getNextItem();
  void deleteItem(int key);
  void print();
  void reset();
  void putItem(int key);
  int getLength();
  void makeEmpty();
  int similiarBST(const btree& tree2);
  void mirrorImage();
  void deleteSuccessor();
  int count(int key);
  int parentCount();
  int leafCount();

 private:
  void    printTree(node *tree, int indent);
  int     similiar(node *a, node *b);
  int     parent(node *tree);
  int     leaf(node *tree);
  node*    mirror(node *tree);
  int     lessCount(int key, node *tree);
  int     getNext(node *tree);
  node*   empty(node *tree);
  node*   find(node * tree, int key);
  node*   findMin(node * tree);
  node*   findMax(node * tree);
  node*   remove(int key, node * tree);
  void    insert(int key, node *& tree);
  void    inOrder(node * tree);
  int     countNodes(node * tree);

}; //btree

#endif
