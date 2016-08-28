#include "bst.h"
#include "rbbst.h"
#include <string>
#include <iostream>
using namespace std;

int main(){

	BinarySearchTree<double, double> bst_test;
	RedBlackTree<double,double> rbtree_test;



	cout << "Testing the Red Black Tree! " << endl;

	rbtree_test.insert(make_pair(12, 12));
	rbtree_test.insert(make_pair(5, 5));
	rbtree_test.insert(make_pair(15, 15));
	rbtree_test.insert(make_pair(3, 3));
	rbtree_test.insert(make_pair(13, 13));
	rbtree_test.insert(make_pair(10, 10));
	rbtree_test.insert(make_pair(17, 17));
	rbtree_test.insert(make_pair(4, 4));
	rbtree_test.insert(make_pair(14, 14));
	rbtree_test.insert(make_pair(7, 7));
	rbtree_test.insert(make_pair(11, 11));
	rbtree_test.insert(make_pair(6, 6));
	rbtree_test.insert(make_pair(8, 8));
	rbtree_test.insert(make_pair(2, 2));
	// seg faults as soon as we use doubles
	rbtree_test.insert(make_pair(13.8, 13.8));
	rbtree_test.insert(make_pair(14.8, 14.8));
	rbtree_test.insert(make_pair(8.8, 8.8));

	cout << "printing out what we have: " << endl;
	rbtree_test.print();

	cout << endl;

	cout << "Testing the iterator! " << endl;
	
	RedBlackTree<double, double>::iterator it = rbtree_test.begin();
	for(it = rbtree_test.begin() ; it != rbtree_test.end(); ++it) {
        std::cout << it->first << " " << it->second << std::endl;
    }


	return 0;

}