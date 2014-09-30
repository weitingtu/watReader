/*
 * watReader.h
 *
 *  Created on: 2014/10/1
 *      Author: weitingtu
 */
#ifndef __watReader_h
#define __watReader_h

using namespace std;
#include <list>
#include <string>
#include "watStruct.h"

class WAT;

class WATParser {
public:
  WATParser();
  virtual ~WATParser();

  void parse(const string& line, const int nb);
  void print(void) const {watManager().print();}
  void dump(void) const {watManager().dump();}
  void calculate(void) {watManager().calculate();}
private:
  void parseHeader2(const string& line);
  void parseHeader5(const string& line);
  void parseDataValue(const string& line);
  int parseInt(const string& line, size_t& pos, const size_t& len, const size_t& empty);
  double parseDouble(const string& line, size_t& pos, const size_t& len, const size_t& space);
  string parseString(const string& line, size_t& pos, const size_t& len, const size_t& space);

  const WATManager& watManager(void) const {return _watManager;}
  WATManager& watManager(void) {return const_cast<WATManager& >(static_cast<const WATParser*>(this)->watManager());}

  WATManager    _watManager;
};

#endif




