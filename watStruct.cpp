/*
 * watStruct.cpp
 *
 *  Created on: 2014/10/1
 *      Author: weitingtu
 */
#include "watStruct.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>

WATManager::WATManager():
  _lotID(),
  _fieldList(),
  _watList(),
  _aveMap(),
  _nbMap()
{
}

WATManager::~WATManager()
{
  fieldList().clear();
  watList().clear();
}

void
WATManager::printWATList(const list<WAT>& watList) const
{
  list<WAT>::const_iterator it    = watList.begin();
  list<WAT>::const_iterator itEnd = watList.end();
  for(;it != itEnd; ++it)
  {
    printWAT(*it);
  }
}

void
WATManager::printWAT(const WAT& w) const
{
  cout << w.waferID() << " " << w.siteID();
  list <double>::const_iterator it    = w.parameterList().begin();
  list <double>::const_iterator itEnd = w.parameterList().end();
  for(;it != itEnd; ++it) {
    cout << " " << *it;
  }
  cout << endl;
}

void
WATManager::calculate(void)
{
  initializeAveData();
  map<int, vector<double> >::iterator it    = aveMap().begin();
  map<int, vector<double> >::iterator itEnd = aveMap().end();
  for(;it != itEnd; ++it)
  {
    int waferID = (*it).first;
    vector<double>& ave = (*it).second;
    int& nb = nbMap()[waferID];
    getAverage(ave, nb);
  }
}

void
WATManager::initializeAveData(void)
{
  list<WAT>::const_iterator it    = watList().begin();
  list<WAT>::const_iterator itEnd = watList().end();
  for(;it != itEnd; ++it)
  {
    addAveData(*it);
  }
}

void
WATManager::addAveData(const WAT& w)
{
  map<int, vector<double> >::const_iterator it = aveMap().find(w.waferID());
  bool needInit = aveMap().end() == it;
  vector<double>& ave = aveMap()[w.waferID()];
  int& nb = nbMap()[w.waferID()];
  if(needInit) {
    ave.resize(fieldList().size());
    initializeVector(ave);
    nb = 0;
  }
  addWATParameter(ave, w);
  ++nb;
}

vector<double>
WATManager::calculateWAT(const int waferID) const
{
  vector<double> ave;
  ave.resize(fieldList().size());
  initializeVector(ave);

  int nb = 0;
  list<WAT>::const_iterator it    = watList().begin();
  list<WAT>::const_iterator itEnd = watList().end();
  for(;it != itEnd; ++it)
  {
    if((*it).waferID() != waferID) {
      continue;
    }
    addWATParameter(ave, (*it));
    ++nb;
  }
  getAverage(ave, nb);

  return ave;
}

void
WATManager::initializeVector(vector<double>& v) const
{
  size_t size = v.size();
  for(size_t idx = 0; idx < size; ++idx)
  {
    v[idx] = 0;
  }
}

void
WATManager::addWATParameter(vector<double>& ave, const WAT& w) const
{
  if(w.parameterList().size() != ave.size()) {
    cout << "Parameter size: " << w.parameterList().size() << "ave size: " << ave.size() << " mismatch" << endl;
    return;
  }
  list <double>::const_iterator it    = w.parameterList().begin();
  list <double>::const_iterator itEnd = w.parameterList().end();
  for(int idx = 0;it != itEnd; ++it, ++idx) {
    ave[idx] += (*it);
  }
}

void
WATManager::getAverage(vector<double>& ave, const int nb) const
{
  if(0 == nb) {
    cout << "Divided by zero";
    return;
  }
  size_t size = ave.size();
  for(size_t idx = 0; idx < size; ++idx)
  {
    ave[idx] = ave[idx]/nb;
  }
}

void
WATManager::printAverage(const vector<double>& ave) const
{
  size_t size = ave.size();
  for(size_t idx = 0; idx < size; ++idx)
  {
    cout << "," << ave[idx];
  }
}

void
WATManager::dump(void) const
{
  string fileName = lotID() + ".txt";
  fileName.erase(remove(fileName.begin(), fileName.end(), ' '), fileName.end());
  remove(fileName.c_str());

  ofstream outfile;
  outfile.open (fileName.c_str());

  outfile << "WF#";
  list<string>::const_iterator it    = fieldList().begin();
  list<string>::const_iterator itEnd = fieldList().end();
  for(;it != itEnd; ++it)
  {
    outfile << "," << (*it);
  }
  outfile << endl;

  map<int, vector<double> >::const_iterator mit    = aveMap().begin();
  map<int, vector<double> >::const_iterator mitEnd = aveMap().end();
  for(;mit != mitEnd; ++mit)
  {
    outfile << (*mit).first;
    const vector<double>& ave = (*mit).second;
    size_t size = ave.size();
    for(size_t idx = 0; idx < size; ++idx)
    {
      outfile << "," << ave[idx];
    }
    outfile << endl;
  }

  outfile.close();
}




