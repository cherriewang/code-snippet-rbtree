#include "bst.h"
#include "rbbst.h"
#include "4color.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;


int main(int argc, char* argv[]){ 

	if(argc < 2){
	    cerr << "usage: ./color index_file...Please provide an index file" << endl;
	    return 1;
    }

    string filename(argv[1]); 
    ifstream index(filename.c_str());
    
    // useful data
    int countryNum = 0;
    int row = 0;    
    int col = 0;

    // gets our useful data from the file
    std::string first;
    std::getline(index, first);
    //cout << first << endl;
    std::stringstream ss(first);
    ss >> countryNum >> row >> col;

    FourColor test(row, col, countryNum, index);
    //test.print();
    test.solve();

    cout << "~~~~~~~~~~~~~~~~~~~~~~ SOLVED ~~~~~~~~~~~~~~~~~~~~~~~~~ " << endl;
    test.print();

    // once we're done with it
    index.close();

	return 0;
}