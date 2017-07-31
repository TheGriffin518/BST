#include "btree.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <cstring>
#include <sstream>

using namespace std;

int main()
{
  ifstream inFile;
  ofstream outFile;
  string   inFileName;
  string   outFileName;
  string   outputLabel;
  string   command;

  string orderItem;
  btree tree;
  btree tree2;
  int    numCommands;

  /**
   *Code that is there in case the input file does not work. 
   *
  tree.putItem(23);
  tree.putItem(12);
  tree.putItem(14);
  tree.putItem(64);
  tree.putItem(22);
  tree.print();
  std::cout << '\n';
  std::cout << tree.leafCount() << '\n';
  std::cout << tree.parentCount() << '\n';
  tree.mirrorImage();
  tree.deleteSuccessor();
  

  tree2.putItem(23);
  tree2.putItem(12);
  tree2.putItem(14);
  tree2.putItem(64);  
  tree2.putItem(22);  
  
  if(tree.similiarBST(tree2))
    std::cout << "Similiar" << std::endl;
  else 
    std::cout << "Not Similiar" << std::endl;

  std::cout << tree.count(65) << std::endl;
  */
  cout << "Enter name of input command file; press return" << endl;
  cin >> inFileName;
  inFile.open(inFileName.c_str());

  cout << "Enter name of output file; press return" << endl;
  cin >> outFileName;
  outFile.open(outFileName.c_str());
  
  cout << "Enter name of test run; press return" << endl;
  cin >> outputLabel;
  outFile << outputLabel << endl;

  inFile >> command;

  numCommands = 0;
  while (command != "Quit")
    {
      cout << command;
      if(command == "PutItem")
	{
	  inFile >> command;
	  tree.putItem(stoi(command));
	}

      else if(command == "DeleteItem") 
	{
	  inFile >> command;
	  tree.deleteItem(stoi(command));
	}

      else if (command == "GetItem")
	{
	  inFile >> command;
	  tree.getItem(stoi(command));
	}
      else if (command == "GetNextItem")
	{
	  inFile >> command;
	  outFile << tree.getNextItem() << endl;
	}
      
      else if(command == "GetLength")
	outFile << "Number of node(s) is: " << tree.getLength() << endl;

      else if(command == "isEmpty")
	{
	  if(tree.isEmpty())
	    outFile << "Tree is empty" << endl;
	  else 
	    outFile << "Tree is not empty" << endl;
	}
      else if(command == "isFull")
	{
	  if(tree.isFull())
	    outFile << "Tree is full" << endl;
	  else
	    outFile << "Tree is not full" << endl;
	}
      else if(command == "Print")
	{
	  tree.print();
	  outFile << endl;
	}
      else if(command == "ResetTree")
	{
	  tree.reset();
	}
      else if(command == "MakeEmpty")
	{
	  tree.makeEmpty();
	}

      else if(command == "SimiliarBST")
	{
	  btree tree2;
	  
	  inFile >> command;
	  istringstream ss(command);
	  string token;

	  while(getline(ss,token,','))
	    {
	      tree2.putItem(stoi(token));
	    }
	    
	  if(tree.similiarBST(tree2))
	    outFile << "The two trees are identical" << endl;
	  else
	    outFile << "The two trees are not identical" << endl;
	}

      else if(command == "DeleteSuccessor")
	{
	  tree.deleteSuccessor();
	  outFile << "The smallest node was deleted" << endl;
	}

      else if(command == "MirrorImage")
	{
	  tree.mirrorImage();
	}

      else if(command == "LeafCount")
	{
	  outFile << "Number of leaf nodes: " << tree.leafCount() << endl;
	}

      else if(command == "SingleParentCount")
	{
	  outFile << "Number of single parent nodes: " << tree.parentCount() << endl;
	}

      else if(command == "Count")
	{
	  inFile >> command;
	  outFile << "Number of nodes with value less than " 
		  << command
		  << ", is: " 
		  << tree.count(stoi(command))
		  << endl;
	}

      else 
	cout << "Command not recognized" << endl;
      numCommands++;
      cout << "Command is completed." << endl;
      inFile >> command;
    }//while

  cout << "Testing is completed." << endl;
  inFile.close();
  outFile.close();

  return 0;
}//main
