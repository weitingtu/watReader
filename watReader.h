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

class WATManager;

class WATReader {
 public:
  WATReader();
  virtual ~WATReader();

  void setWatManager(WATManager* const m) {
    _pWatManager = m;
  }
  void readline(const string& line, const int nb);

 private:
  WATReader(const WATReader& r);
  WATReader& operator=(const WATReader& rhs);
  void parseHeader2(const string& line);
  void parseHeader5(const string& line);
  void parseDataValue(const string& line);
  int parseInt(const string& line, size_t& pos, const size_t& len,
               const size_t& empty);
  double parseDouble(const string& line, size_t& pos, const size_t& len,
                     const size_t& space);
  string parseString(const string& line, size_t& pos, const size_t& len,
                     const size_t& space);

  const WATManager& watManager(void) const {
    return *_pWatManager;
  }
  WATManager& watManager(void) {
    return const_cast<WATManager&>(static_cast<const WATReader*>(this)
        ->watManager());
  }

  WATManager* _pWatManager;
};

#endif

