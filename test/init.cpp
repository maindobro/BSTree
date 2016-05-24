#include "BSTree.h"
#include "BSTree.cpp"
#include <catch.hpp>
#include <iostream>
#include <fstream>
#include "stdlib.h"
#include <algorithm>
#include <iterator> 
using namespace std;

SCENARIO("BSTree init", "[init]") 
{
  BSTree<int> Tree;
  REQUIRE(Tree.size() == 0);
}
SCENARIO("BSTree list init", "[list init]") 
{
  BSTree<int> Tree {1,2,3};
  REQUIRE(Tree.size() == 3);
}
SCENARIO("BSTree insert element", "[insert]") 
{
	BSTree<int> Tree;
	Tree.insert(1);
	Tree.insert(3);
	REQUIRE(Tree.size() == 2);
}
SCENARIO("BSTree max element", "[max]") 
{
	BSTree<int> Tree{4,3,7,2,1,5,23};
	REQUIRE(Tree.max(Tree.search(4))->key == 23);
}
SCENARIO("BSTree min element", "[min]") 
{
	BSTree<int> Tree{4,3,7,2,1,5,23};
	REQUIRE(Tree.min(Tree.search(4))->key == 1);
}
SCENARIO("BSTree next element", "[next]") 
{
	BSTree<int> Tree{4,3,7,2,1,5,23};
	REQUIRE(Tree.next(Tree.search(5)) == Tree.search(7));
	REQUIRE(Tree.next(Tree.search(7)) == Tree.search(23));
}
SCENARIO("BSTree prev element", "[prev]") 
{
	BSTree<int> Tree{4,3,7,2,1,5,23};
	REQUIRE(Tree.prev(Tree.search(5)) == Tree.search(4));
	REQUIRE(Tree.prev(Tree.search(4)) == Tree.search(3));
}
SCENARIO("BSTree search", "[search]") 
{
	BSTree<int> Tree {1,2,3};
	REQUIRE(Tree.search(1) != nullptr);
	REQUIRE(Tree.search(2) != nullptr);
	REQUIRE(Tree.search(3) != nullptr);
	REQUIRE(Tree.search(404) == nullptr);
}
SCENARIO("BSTree remove", "[remove]") 
{
	BSTree<int> Tree {1,2,3,4,5};
	Tree.remove(4);
	REQUIRE(Tree.size()==4);
}
SCENARIO("BSTree delete root without children", "[delete]") 
{
	BSTree<int> Tree {8};
	Tree.remove(8);
	REQUIRE( Tree.size()==0 );
}
SCENARIO("BST delete root with one child", "[delete]") 
{
	BSTree<int> Tree {8, 4};
	Tree.remove(8);
	REQUIRE( Tree.size()==1 );
	REQUIRE(Tree.search(4) != nullptr);
}
SCENARIO("BST delete root with children", "[delete]") 
{
	BSTree<int> Tree {8, 4, 3, 10, 9, 13, 11, 12};
	Tree.remove(8);
	REQUIRE( Tree.size() == 7 );
}
SCENARIO("BST delete non root without children", "[delete]") 
{
	BSTree<int> Tree {8, 4, 3, 10, 9, 13, 11, 12};
	Tree.remove(3);
	REQUIRE( Tree.size()==7 );
}
SCENARIO("BST delete non root with one child", "[delete]") 
{
	BSTree<int> Tree {8, 4, 3, 10, 9, 13, 11, 12};
	Tree.remove(11);
	REQUIRE( Tree.size() == 7 );
}
SCENARIO("BST delete non root with children", "[delete]") 
{
	BSTree<int> Tree ={8, 4, 3, 10, 9, 13, 11, 12};
	Tree.remove(10);
	REQUIRE( Tree.size() == 7 );
}
SCENARIO("BSTree operator >>", "[file&stream input]") 
{
	BSTree<int> Tree;
	fstream file("Tree.txt");
	file >> Tree;
	file.close();
	REQUIRE(Tree.size() == 5);
	REQUIRE(Tree.search(4) != nullptr);
	REQUIRE(Tree.search(5) != nullptr);
	REQUIRE(Tree.search(2) != nullptr);
	REQUIRE(Tree.search(6) != nullptr);
	REQUIRE(Tree.search(7) != nullptr);
}

SCENARIO("BSTree operator <<", "[file&stream output]") 
{
	BSTree<int> Tree, OutTree;
	fstream file("Tree.txt"), out("out.txt");
	file >> Tree;
	out << Tree;
	out.seekg(0);
	out >> OutTree;
	file.close();
	out.close();
	REQUIRE(OutTree.search(4) != nullptr);
	REQUIRE(OutTree.search(5) != nullptr);
	REQUIRE(OutTree.search(2) != nullptr);
	REQUIRE(OutTree.search(6) != nullptr);
	REQUIRE(OutTree.search(7) != nullptr);
}
/*SCENARIO("BSTree iterator1", "[iterator1]") 
{
	BSTree<int> Tree {1,2,4,6};
	BSTree<int> CopyTree;
	fstream out("out.txt");
	Iterator<int> it(Tree.root());
	std::copy(it.begin(), it.end(), std::ostream_iterator<int>(out, " "));
	out.seekg(0);
	out >> OutTree;
	out.close();
	REQUIRE(CopyTree.search(1) != nullptr);
	REQUIRE(CopyTree.search(2) != nullptr);
	REQUIRE(CopyTree.search(4) != nullptr);
	REQUIRE(CopyTree.search(6) != nullptr);
}*/
SCENARIO("BSTree EmptyException", "[emptyerror]")
{
	bool flagBad=false;
	bool flag=false;
	const char* y;
	BSTree<int> Tree;
	try {
	  Tree.search(404);
	}
	catch (EmptyException &ex) {
		flag = true;
		REQUIRE(ex.what());
		
	}
	catch (BSTreeException &ex) {
		flagBad = true;
	}
	REQUIRE(flag);
	REQUIRE(!flagBad);
}
SCENARIO("Exception fill", "[fillerror]")
{
	bool flagBad=false;
	bool flag=false;
	BSTree<int> Tree;
	try {
		std::ifstream("404.txt") >> Tree;
	}
	catch (InputException &ex) {
		flag = true;
	}
	catch (BSTreeException &ex) {
		flagBad = true;
	}
	REQUIRE(flag);
	REQUIRE(!flagBad);
}
