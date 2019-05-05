/*
  * Filename           Makefile
  * Date         05/05/2019
  * Author       Riya Patel
  * Email        rgp170030@utdallas.edu
  * Course       CS 3377.502 Spring 2019
  * Version      0.9
  * Copyright2019, All Rights Reserved
  *
  * Description
  *
  *     This file contains the makefile which complies and links the project # * through the make command. 
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

/*
 * Records in the file have a fixed length buffer
 * that will hold a C-Style string. This is the
 * size of the fixed length buffer.
 */
const int maxRecordStringLength = 25;
class BinaryFileRecord
{
public:
  uint8_t strLength;
  char stringBuffer[maxRecordStringLength];
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

  stringstream ss;  //string
  stringstream s1; //int
  stringstream s2;
  stringstream s3;
  stringstream s4; 
  drawCDKMatrix(myMatrix, true);

  BinaryFileHeader *myHeader = new BinaryFileHeader(); //object for the binary file
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



  
  BinaryFileRecord *myRecord=new BinaryFileRecord(); // create object for records
  binInfile.read((char*)myRecord, sizeof(BinaryFileRecord)); // read inary file for records
  int num=strlen(myRecord->stringBuffer); //to convert to int
  s1 <<"strlen: " <<num;
  temp=s1.str();
  
  setCDKMatrixCell(myMatrix, 2, 1, temp.c_str()); // to output to matrix cell
  setCDKMatrixCell(myMatrix, 2, 2,myRecord->stringBuffer );

  binInfile.read((char*)myRecord, sizeof(BinaryFileRecord)); // read binary file for next line
  num=strlen(myRecord->stringBuffer);
  s2<<"strlen: " <<num;
  temp=s2.str();
  setCDKMatrixCell(myMatrix, 3, 1, temp.c_str()); // set matrix 3,1 and 3,2
  setCDKMatrixCell(myMatrix, 3, 2,myRecord->stringBuffer );    

  binInfile.read((char*)myRecord, sizeof(BinaryFileRecord)); // read binary file for next line
  num=strlen(myRecord->stringBuffer);
  s3<<"strlen: " <<num;
  temp=s3.str();
  setCDKMatrixCell(myMatrix, 4, 1, temp.c_str());
  setCDKMatrixCell(myMatrix, 4, 2,myRecord->stringBuffer );

  binInfile.read((char*)myRecord, sizeof(BinaryFileRecord)); // read binary file for next line
  num=strlen(myRecord->stringBuffer);
  s4<< "strlen: " <<num;
  temp=s4.str();
  setCDKMatrixCell(myMatrix, 5, 1, temp.c_str());    // to set last 2 matrix spots in matrix
  setCDKMatrixCell(myMatrix, 5, 2,myRecord->stringBuffer );



  /*
   * Dipslay a message
   */
  setCDKMatrixCell(myMatrix, 2, 2, "Seed Money");
  drawCDKMatrix(myMatrix, true);    /* required  */

  unsigned char x;
  cin >> x;


  // Cleanup screen
  endCDK();
}
