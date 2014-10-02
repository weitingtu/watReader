/*
 * watStruct.h
 *
 *  Created on: 2014/10/1
 *      Author: weitingtu
 */
#ifndef __watStruct_h
#define __watStruct_h

using namespace std;
#include <list>
#include <string>
#include <vector>
#include <map>

class WAT {
public:
  WAT(const int waferID, const int siteID):
    _waferID(waferID),
    _siteID(siteID)
  {}
  virtual ~WAT() {}
  int waferID(void) const {return _waferID;}
  int siteID(void) const {return _siteID;}
  const list<double>& parameterList(void) const {return _parameterList;}

  void addParameter(const double p) {_parameterList.push_back(p);}
private:
  WAT():
  _waferID(0),
  _siteID(0)
  {}

  int _waferID;
  int _siteID;
  list <double> _parameterList;
};

class WATManager {
public:
  WATManager();
  virtual ~WATManager();
  void addWAT(const WAT& w) {watList().push_back(w);}
  void addField(const string& p) {fieldList().push_back(p);}
  void setLotID(const string& id) {lotID() = id;}
  void dump(void) const;
  void calculate(void);

private:
  void addWATParameter(vector<double>& ave, const WAT& w) const;
  void getAverage(vector<double>& ave, const int nb) const;
  void printAverage(const vector<double>& ave) const;

  void initializeAverageData(void);
  void addAverageData(const WAT& w);

  const string& lotID(void) const {return _lotID;}
  string& lotID(void) {return const_cast<string&>(static_cast<const WATManager*>(this)->lotID());}
  const list<string>& fieldList(void) const {return _fieldList;}
  list<string>& fieldList(void) {return const_cast<list<string>& >(static_cast<const WATManager*>(this)->fieldList());}
  const list<WAT>& watList(void) const {return _watList;}
  list<WAT>& watList(void) {return const_cast<list<WAT>& >(static_cast<const WATManager*>(this)->watList());}
  const map<int, vector<double> >& aveMap(void) const {return _aveMap;}
  map<int, vector<double> >& aveMap(void) {return const_cast<map<int, vector<double> >& >(static_cast<const WATManager*>(this)->aveMap());}
  const map<int, int>& nbMap(void) const {return _nbMap;}
  map<int, int>& nbMap(void) {return const_cast<map<int, int>& >(static_cast<const WATManager*>(this)->nbMap());}

  string        _lotID;
  list <string> _fieldList;
  list <WAT>    _watList;
  map<int, vector<double> > _aveMap;
  map<int, int>             _nbMap;
};

#endif




