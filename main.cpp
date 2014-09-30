/*
 * main.cpp
 *
 *  Created on: 2014/10/1
 *      Author: weitingtu
 */
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "watReader.h"

int main ()
{
  int nb = 0;
  string line;
  ifstream infile;
  infile.open ("./WAT_report.txt");
  if(!infile.good()) {
    cout << "Open file failed." << endl;
    return 1;
  }

  WATParser parser;

  while(!infile.eof())
  {
    nb ++;
    getline(infile, line);
    parser.parse(line, nb);
  }
  infile.close();

  parser.calculate();
  parser.dump();
  return 0;
}




