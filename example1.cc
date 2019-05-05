/*
 * Usage of CDK Matrix
 *
 * File:   example1.cc
 * Author: Stephen Perkins
 * Email:  stephen.perkins@utdallas.edu
 */

#include <iostream>
#include "cdk.h"
#include <string>
#include <fstream>
#include <stdint.h>
#include <sstream>

#define MATRIX_WIDTH 5
#define MATRIX_HEIGHT 3
#define BOX_WIDTH 25
#define MATRIX_NAME_STRING "Test Matrix"

using namespace std;
class BinaryFileHeader
{
public:
  uint32_t magicNumber; /* Should be 0xFEEDFACE */
  uint32_t versionNumber;
  uint64_t numRecords;
};


int main()
{

  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  const char 		*rowTitles[MATRIX_HEIGHT+1] = {"R0", "a", "b", "c"};
  const char 		*columnTitles[MATRIX_WIDTH+1] = {"C0", "a", "b", "c", "d", "e"};
  int		boxWidths[MATRIX_WIDTH+1] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[MATRIX_WIDTH+1] = {vMIXED, vMIXED, vMIXED, vMIXED};

  /*
   * Initialize the Cdk screen.
   *
   * Make sure the putty terminal is large enough
   */
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
  */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT,
			  MATRIX_NAME_STRING, (char **) columnTitles, (char **) rowTitles, boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  stringstream ss;  //for strings from file
  stringstream s1; // for int from file
 
   drawCDKMatrix(myMatrix, true);

  BinaryFileHeader *myHeader = new BinaryFileHeader(); // create object for header
  ifstream binInfile ("cs3377.bin", ios::in | ios::binary); // read binary file
  binInfile.read((char *) myHeader, sizeof(BinaryFileHeader));
  ss << "Magic: 0x" << std::hex << std::uppercase << myHeader->magicNumber; // use stringstream to  convert to string
  string temp=ss.str();
  setCDKMatrixCell(myMatrix, 1, 1, temp.c_str()); // set matrix cell 
  
  
  s1 <<"Version: "<< myHeader->versionNumber; // get version number
  temp=s1.str();
  setCDKMatrixCell(myMatrix, 1, 2, temp.c_str());

  ss.str(""); // to clear streamstring
  ss<< "NumRecords: " << hex << myHeader->numRecords;
  temp=ss.str();
  setCDKMatrixCell(myMatrix, 1, 3, temp.c_str());

  /*
   * Dipslay a message
   */
  setCDKMatrixCell(myMatrix, 2, 2, "Test Message");
  drawCDKMatrix(myMatrix, true);    /* required  */

  unsigned char x;
  cin >> x;


  // Cleanup screen
  endCDK();
}
