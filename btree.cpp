#include "btree.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stack>

btree::btree()
{
  root=NULL;
}//Constructor

btree::~btree()
{
  root = empty(root);
}//Deconstructor

/**
 *Checks to see if the tree is full by attempting to allocate
 *more memory for another node. If that fails, then teh function
 *returns true.
 */
bool btree::isFull() 
{
  node * location;
  try 
    {
      location = new node;
      delete location;
      return false;
    }//try
  catch (std::bad_alloc exception)
    {
      return true;
    }//catch
}//isEmpty

/**
 *Checks to see if the tree is empty or not. Returns true or false based
 *on the results. 
 */
bool btree::isEmpty()
{
  return root == NULL;
} //isEmpty

/**
 *Returns the node that has the specified value of key.
 */
int btree::getItem(int key)
{
  node *item = find(root, key);
  return item->data;
}//getItem

/**
 *Returns the next node within the tree. 
 */
int btree::getNextItem()
{
  return getNext(root);
}

/**
 *Returns the next node that is located within the tree. 
 */
int btree::getNext(node *tree) 
{
  if(tree == NULL)
    return 0;
  else 
    {
      if(tree->right == NULL)
	return tree->data;
      else
	return tree->right->data;
    }
}//getNextItem

/**
 *Removes the node from the tree with the specified value of key.
 */
void btree::deleteItem(int key) 
{
  root = remove(key, root);
}//deleteItem

/**
 *Calls the printTree method to print the contents of the tree.
 */
void btree::print()
{
  printTree(root, 0);
}

/**
 *Prints the contents of the tree in a pretty way. Defaults to stdout, but 
 *can be redirected from the commadn line. 
 */
void btree::printTree(node *tree, int indent=0) 
{
  if(indent)
    std::cout << std::setw(indent) << ' ';
  std::cout << tree->data << '\n';
  if(tree->left)
    printTree(tree->left,indent+4);
  if(tree->right)
    printTree(tree->right,indent+4);
}//print


void btree::reset() 
{
  return;
} //reset

/**
 *Returns the number of nodes that are located wihtin the tree by calling
 * the helper function countNodes.
 */
int btree::getLength() 
{
  return countNodes(root);
} //getLength

/**
 *Places an item within the tree by calling the private insert function.
 */
void btree::putItem(int key)
{
  insert(key, root);
}//putItem

/**
 *Finds a node within the tree with the specified value. If found, it
 *returns a pointer to said node. 
 */
btree::node* btree::find(node * tree, int key)
{
  if (tree == NULL)
    return NULL;
  else if(key < tree->data) 
    return find(tree->left, key);
  else if(key > tree->data)
    return find(tree->right, key);
  else
    return tree;
} //find

/**
 *Finds the smallest value within the tree via recursion.
 */
btree::node* btree::findMin(node * tree)
{
  if(tree == NULL)
    return NULL;
  else if(tree->left == NULL)
    return tree;
  else 
    return findMin(tree->left);
}//findMin

/**
 *Finds the maximum value within the tree in a recursive manner. 
 */
btree::node * btree::findMax(node * tree)
{
  if(tree == NULL)
    return NULL;
  else if(tree->right == NULL)
    return tree;
  else
    return findMax(tree->right);
}//findMax

/**
 *Removes a node from the tree with the specified value of key. Does so recursively
 *and handles if there are nodes connected to the node being deleted/removed. 
 */
btree::node * btree::remove(int key, node * tree)
{
  node * temp;
  if(tree == NULL)
    return NULL;
  else if (key < tree-> data)
    tree->left = remove(key, tree->left);
  else if(key > tree->data)
    tree->right = remove(key, tree->right);
  else if (tree->left && tree->right)
    {
      temp = findMin(tree->right);
      tree->data = temp->data;
      tree->right = remove(tree->data, tree->right);
    }//else if
  else
    {
      temp = tree;
      if (tree->left == NULL)
	tree = tree->right;
      else if (tree->right == NULL)
	tree = tree->left;
      delete temp;
    }//else

  return tree;

} //remove

/**
 *Calls the private function empty to remove all of the nodes within the tree. 
 */
void btree::makeEmpty()
{
  root = empty(root);
}

/**
 *Is the recursive function of makeEmpty that removes all of the 
 *nodes located within the binary tree. Is a private function. 
 */
btree::node * btree::empty(node * tree)
{
  if (tree == NULL)
    return NULL;
  else
    {
      empty(tree->right);
      empty(tree->left);
      delete tree;
    }
  return NULL;
}//makeEmpty

/**
 *Places a new node within the tree. Can take a supplied node that 
 *already has values in it and place it into the tree. 
 */
void btree::insert(int key, node*& tree)
{
  if(tree == NULL)
    {
      tree = new node;
      tree->data = key;
      tree->left = tree->right = NULL;
    }  
  else if(key < tree->data)
    insert(key,tree->left);
  else if(key > tree->data)
    insert(key, tree->right);

     
}//insert

/**
 *Prints out the order of the tree.
 */
void btree::inOrder(node * tree) 
{
  if(tree == NULL)
    return;
  inOrder(tree->left);
  std::cout << tree->data << " ";
  inOrder(tree->right);
    
}//inOrder

/**
 *Counts the number of nodes within the tree and returns the result. Does so 
 *recursively. 
 */

int btree::countNodes(node * tree) 
{
  if(tree == NULL)
    return 0;
  else 
    return countNodes(tree->right) + countNodes(tree->left) + 1;
}// countNodes

/**
 *Compares the two trees that are supplied to determine if they are identical 
 *or not. Returns true if they are, and false if they are not. 
 */
int btree::similiar(node *a, node *b)
{
  if(a==NULL && b==NULL)
    return 1;
  if(a!=NULL && b!=NULL)
    {
      return
	(
	 a->data == b->data &&
	 similiar(a->left, b->left) &&
	 similiar(a->right, b->right)
	 );
    }
  return 0;
}//similiarBST

int btree::similiarBST(const btree& tree2)
{
  return similiar(root, tree2.root);
}
/**
 *Calls the recursive private function mirror to flip the tree. 
 */
void btree::mirrorImage()
{
  printTree(mirror(root),0);
}

/**
 *Recursively creates a mirror image of the binary tree that is supplied to it.
 */
btree::node* btree::mirror(node *tree)
{
  node *temp = (node*)malloc (sizeof(node));
  if(tree == NULL)
    return tree;
  else
    {
      temp->data = tree->data;
      temp->left = mirror(tree->right);
      temp->right = mirror(tree->left);
      
      return temp;
    }//else



}//mirrorImage

/**
 *Finds the lesser value within the tree and deletes it. It uses the recursive function
 *findMin to help it. 
 */
void btree::deleteSuccessor()
{
  node * temp;
  temp = findMin(root);
  std::cout << temp->data << " was deleted" << std::endl;
  remove(temp->data,root);
}//deleteSuccessor

/**
 *Is the private function that counts the number of nodes witha  value less
 *than the one provided. Uses a stack to help count the number of nodes in an
 *iterative manner. Returns the results as an integer. 
 */
int btree::lessCount(int key, node *tree)
{
  int count = 0;
  node *current = tree;
  bool done = false;
  std::stack<node *> nodeStack;
  
  if(tree == NULL)
    return 0;

  while(!done)
    {
      if(current)
	{
	  nodeStack.push(current);
	  current = current->left;
	}
      else
	{
	  if(nodeStack.empty()) 
	    done = true;
	  else
	    {
	      current = nodeStack.top();
	      nodeStack.pop();
	      if(current->data < key)
		count++;
	      current = current->right;
	    }
	}
    }//while
  return count;
}

/**
 *Calls the iterative function lessCount to count the number of nodes
 *with a value less than the one provided. Returns the results as an integer. 
 */
int btree::count(int key) 
{
  return lessCount(key, root);
}//count

/**
 *Calls the private recursive function of parentCount and returns its results. 
 */
int btree::parentCount()
{
  return parent(root);
}

/**
 *Recursively counts the number of nodes that only have one child. Returns
 *the count as an integer. 
 */
int btree::parent(node *tree)
{
  if(tree == NULL)
    return 0;

  else if(tree->right == NULL && tree->left != NULL)
      return parent(tree->left) + 1;

  else if(tree->right != NULL && tree->left == NULL)
      return parent(tree->right) + 1;

  else
      return parent(tree->right) + parent(tree->left);

}//parentCount

/**
 *Calls the private function of leafCount and returns its results.
 */
int btree::leafCount()
{
  return leaf(root);
}

/**
 *Recursively counts the number of leaf nodes loacted within the binary tree.
 */
int btree::leaf(node *tree)
{
  if(tree == NULL)
    return 0;
  if(tree->right == NULL && tree->left == NULL)
    return 1;
  else
    return leaf(tree->right) + leaf(tree->left);
}//leafCount
