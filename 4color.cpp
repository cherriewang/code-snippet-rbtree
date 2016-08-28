#include "4color.h"
#include <iostream>
#include <set>

using namespace std;

FourColor::FourColor(int row, int col, int num, std::ifstream& file) {
  

  country = alloc(row, col);
  // might as well just make these data members
  r = row;
  c = col;
  cnum = num;

  // filling up the 2D array
  for(int i = 0; i < r; i++) {
    for(int j = 0; j < c; j++) {

      country[i][j] = file.get();
    }
    file.get();

  }
  cout << endl;

  // char of all alphabet letters
  char alphabet[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z', '\0'};

  // making country color tree
  for(int i = 0; i < cnum; i++){
    countryColor.insert(std::make_pair(alphabet[i], -1));
  }

  // empty sets woohoo
  std::set<char> tmp;
  // making adjacent tree
  for(int i = 0; i < cnum; i++){
    adjacent.insert(std::make_pair(alphabet[i], tmp));
  }

  // make adjacency tree
  for(int i = 0; i < r; i++) {
    for(int j = 0; j < c; j++) {
      // check if the country is different
      
      // left
      if( (j-1 > 0) && (country[i][j] != country[i][j-1]) ) {
        
        map<char, std::set<char> >::iterator it = adjacent.begin();
        it = adjacent.find(country[i][j]);
        //((*it).second).insert(country[i][j-1]);        
        it->second.insert(country[i][j-1]);

      }
      // right
      if( (j+1 < c) && (country[i][j] != country[i][j+1])  ) {
        map<char, std::set<char> >::iterator it = adjacent.begin();
        it = adjacent.find(country[i][j]);
        //((*it).second).insert(country[i][j+1]);
        it->second.insert(country[i][j+1]);

      }
      // down
      if( (i-1 > 0) && (country[i][j] != country[i-1][j]) ) {
        map<char, std::set<char> >::iterator it = adjacent.begin();
        it = adjacent.find(country[i][j]);
        //((*it).second).insert(country[i-1][j]);
        it->second.insert(country[i-1][j]);


      }
      // up
      if( (i+1 < r) && (country[i][j] != country[i+1][j]) ) {
        map<char, std::set<char> >::iterator it = adjacent.begin();
        it = adjacent.find(country[i][j]);
        //((*it).second).insert(country[i+1][j]);
        it->second.insert(country[i+1][j]);

      }

    } 
  }  
}

FourColor::~FourColor() {
  dealloc(country);
}

// allocator (called in constructor)
char** FourColor::alloc(int row, int col){

  //allocate mem for array of elements of column
  char **col_ptr = new char*[row];

  // allocate mem for array of elements of each row
  char *row_ptr = new char [row * col];

  // tidying things up
  for( int i = 0; i < row; ++i) {
    *(col_ptr + i) = row_ptr;
    row_ptr += col;
  }

  return col_ptr;
}

// deallocator (called in destructor)
void FourColor::dealloc(char **array) {
  delete [] *array;
  delete [] array;
}


void FourColor::print() {
  for (int i=0; i<r; i++) {
    
    for (int j=0; j<c; j++) {
      std::cout << country[i][j]; 
    }
    cout << endl;

  }
  cout << endl;
  
  for(map<char,int>::iterator it = countryColor.begin(); it != countryColor.end(); ++it ){
    cout << it->first << " " << it->second << endl;
  }

}


bool FourColor::isValid(int row, int col) {

  char check = country[row][col];

  // loop through
  if( (col-1 > 0) && (check != country[row][col-1])  ) { 
    if( countryColor.find(check)->second == countryColor.find(country[row][col-1])->second ){
      return false;
    }
  }
  if( (col+1 < c) && (check != country[row][col+1])  ) { 
    if( countryColor.find(check)->second == countryColor.find(country[row][col+1])->second ){
      return false;
    }

  }
  if( (row-1 > 0) && (check != country[row-1][col]) ) { 
    if( countryColor.find(check)->second == countryColor.find(country[row-1][col])->second ){
      return false;
    }

  }
  if( (row+1 < r) && (check != country[row+1][col]) ) {
    if( countryColor.find(check)->second == countryColor.find(country[row+1][col])->second ){
      return false;
    }

  }
  

  return true;

}



void FourColor::solve(){
  //cout << countryColor.find('B')->second << endl;
  solveHelper(0, 0);
  // iterate through the set of countrys
  //solveHelper(countryColor.begin()->first);

}


bool FourColor::solveHelper(int row, int col) {

  // if we're at the last row
  if(row == r){
    return 1;
  }

  /*
   * Is this element already set?  If so, we don't want to 
   * change it.  Recur immediately to the next cell.
   */
  //cout << "row: " << row;
  //cout << "col: " << col << " | "<< country[row][col] << endl;
  if (countryColor.find(country[row][col])->second != -1) {
    //cout << "In if" << countryColor.find(country[row][col])->second << endl;
    // we're at the end of the row
    if (col == c-1) {
      if (solveHelper(row+1, 0)) {
        return 1;
      }
    } 
    // otherwise continue down the row
    else {
      if (solveHelper(row, col+1)) {
        return 1;
      }
    }
    return 0;
  }



  for (int nextColor = 1; nextColor<5; nextColor++) {

    countryColor.find(country[row][col])->second = nextColor;
    //cout << "checking this: " << countryColor.find(country[row][col])->second << endl;

    if(isValid(row, col)) { 
      
      if (col == c-1) {
        if (solveHelper(row+1, 0)) {
          return 1;
        }
      } 

      else {
        if (solveHelper(row, col+1)) {
          return 1;
        }
      }
    }
  }

  // no valid answer exists
  //country[row][col] = -1;
  countryColor.find(country[row][col])->second = -1;
  return 0;

} 

