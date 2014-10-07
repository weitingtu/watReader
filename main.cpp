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
#include "watStruct.h"

int main() {
  int nb = 0;
  string line;
  ifstream infile;
  infile.open("./WAT_report.txt");
  if (!infile.good()) {
    cout << "Open file failed." << endl;
    return 1;
  }

  WATManager manager;
  WATReader reader;
  reader.setWatManager(&manager);

  while (!infile.eof()) {
    nb++;
    getline(infile, line);
    reader.readline(line, nb);
  }
  infile.close();

  manager.calculate();
  manager.dump();
  return 0;
}
