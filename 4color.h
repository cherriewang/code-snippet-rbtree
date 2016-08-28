#ifndef FourColor_H
#define FourColor_H

#include <fstream>
#include <set>
#include "rbbst.h"
#include <map>

#include "bst.h"

class FourColor {

public:
	FourColor(int row, int col, int num, std::ifstream& file);
	~FourColor();
	void solve(); // solves the puzzle
	
	// double pointer for a 2D array to be dynamically allocated
	char **country;

	void print();


private:
	bool isValid(int row, int col);
	bool solveHelper(int row, int col);
	//int board[9][9];

	// allocator (called in constructor)
	char **alloc(int row, int col);
	// deallocator (called in destructor)
	void dealloc(char **array);

	// row and col data mems
	int r;
	int c;
	int cnum;

	// tree of all the country colors
	std::map<char,int> countryColor;
	// map of all adjacencies
	std::map<char, std::set<char> > adjacent;




};

#endif